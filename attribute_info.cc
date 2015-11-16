/* --------------------------------------------------------------
   javel - A java class file disassembler.
   Copyright (C) 2001 Laurent Gregoire (laurent.gregoire@icam.fr)
   --------------------------------------------------------------
   This program is free software; you can  redistribute it and/or
   modify it  under the terms  of the GNU General  Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but without any warranty; without even the implied warranty of
   merchantability or fitness  for a particular purpose.  See the
   GNU General Public License for more details.
   -------------------------------------------------------------- */

#include <sstream>

#include "attribute_info.h"
#include "class_info.h"
#include "code_info.h"

attributes_set::attributes_set(istream& is, const class_info* ci) {
	U2 attributes_count = util::read_U2(is);
	for (int i = 0; i < attributes_count; i++) {
		attribute_info* ai = 0;
		string name = ci->get_cp_info(util::read_U2(is))->str();
		if (name == "Exceptions") {
			ai = new exception_info(is, ci);
		} else if (name == "Code") {
			ai = new code_info(is, ci);
		} else if (name == "ConstantValue") {
			ai = new constantvalue_info(is, ci);
		} else if (name == "SourceFile") {
			ai = new sourcefile_info(is, ci);
		} else if (name == "LineNumberTable") {
			ai = new linenumtbl_info(is, ci);
		} else if (name == "LocalVariableTable") {
			ai = new localvar_info(is, ci);
		} else {
			ai = new generic_attribute_info(is, ci);
		}
		attributes[name] = ai;
	}
}

template<class T> T* attributes_set::get_attribute_info(string tag, T* t) {
	map_attr_t::iterator p = attributes.find(tag);
	if (p == attributes.end())
		return 0;
	else
		return dynamic_cast<T*>(p->second);
}

exception_info* attributes_set::get_exceptions() {
	return get_attribute_info("Exceptions", (exception_info*)0);
}

code_info* attributes_set::get_code() {
	return get_attribute_info("Code", (code_info*)0);
}

constantvalue_info* attributes_set::get_constantvalue() {
	return get_attribute_info("ConstantValue", (constantvalue_info*)0);
}

sourcefile_info* attributes_set::get_sourcefile() {
	return get_attribute_info("SourceFile", (sourcefile_info*)0);
}

linenumtbl_info* attributes_set::get_linenumtbl() {
	return get_attribute_info("LineNumberTable", (linenumtbl_info*)0);
}

localvar_info* attributes_set::get_localvar() {
	return get_attribute_info("LocalVariableTable", (localvar_info*)0);
}

void attributes_set::cleanup() {
	for(map_attr_t::iterator p = attributes.begin();
			p != attributes.end(); p++)
		delete p->second;
}

void attribute_info::disassemble(ostream& os) const {
	os << name;
}

generic_attribute_info::generic_attribute_info(
		istream& is, const class_info* _ci)
		: attribute_info(_ci) {
	length = util::read_U4(is);
	for (long int i = 0; i < length; i++) {
		U1 u = util::read_U1(is);
	}
}

constantvalue_info::constantvalue_info(istream& is, const class_info* _ci)
		: attribute_info(_ci) {
	length = util::read_U4(is);
	U2 index = util::read_U2(is);
	value = ci->get_cp_info(index)->str();
}

void constantvalue_info::disassemble(ostream& os) const {
	os << value;
}

exception_info::exception_info(istream& is, const class_info* _ci)
		: attribute_info(_ci) {
	length = util::read_U4(is);
	U2 num = util::read_U2(is);
	for (int i = 0; i < num; i++) {
		exceptions.push_back(new string(ci->get_cp_info
			(util::read_U2(is))->str()));
	}
}

void exception_info::disassemble(ostream& os) const {
	os << "\t\t" << "throws" << "\t";
	for (int i = 0; i < exceptions.size(); i++) {
		os << util::slash2point(*exceptions[i]);
		if (i < exceptions.size() - 1)
			os << "," << endl << "\t\t\t";
	}
}

void exception_info::makedepend(depend_list& di) const {
	for (vec_excp_t::const_iterator p = exceptions.begin();
			p != exceptions.end(); ++p) {
		di[**p] = true;
}	}

void exception_info::cleanup() {
	for (vec_excp_t::iterator p = exceptions.begin();
			p != exceptions.end(); ++p) {
		delete *p;
}	}

sourcefile_info::sourcefile_info(istream& is, const class_info* _ci)
		: attribute_info(_ci) {
	length = util::read_U4(is);
	U2 nameindex = util::read_U2(is);
	source_filename = ci->get_cp_info(nameindex)->str();
}

void sourcefile_info::disassemble(ostream& os) const {
	os << source_filename;
}

linenumtbl_info::linenumtbl_info(istream& is, const class_info* _ci)
		: attribute_info(_ci) {
	length = util::read_U4(is);
	U2 table_length = util::read_U2(is);
	for (int i = 0; i < table_length; i++) {
		lnt linenumber;
		linenumber.start_pc = util::read_U2(is);
		linenumber.line_number = util::read_U2(is);
		linenums.push_back(linenumber);
	}
}

void linenumtbl_info::check_line(long int old_pc, long int new_pc,
			ostream& os) const {
	for (vec_lnt_t::const_iterator p = linenums.begin();
			p != linenums.end(); ++p) {
		if (old_pc < p->start_pc && new_pc >= p->start_pc) {
			os << "\t\t// L"
				<< p->line_number << ":"
				<< ci->get_source_line(p->line_number - 1)
				<< endl;
			break;
	}	}
}

localvar_info::localvar_info(istream& is, const class_info* _ci) 
		: attribute_info(_ci) {
	length = util::read_U4(is);
	U2 table_length = util::read_U2(is);
	for (int i = 0; i < table_length; i++) {
		lvt lvar;
		lvar.start_pc = util::read_U2(is);
		lvar.length = util::read_U2(is);
		U2 nameindex = util::read_U2(is);
		lvar.name = ci->get_cp_info(nameindex)->str();
		lvar.descr_index = util::read_U2(is);
		lvar.index = util::read_U2(is);
		localvars.push_back(lvar);
		cerr << "Local var '" << lvar.name << "', pc [" << lvar.start_pc
			<< "," << lvar.start_pc + lvar.length << "], index "
			<< lvar.index << endl;
	}
}

/** Since java compiler local table generation seems to be completly
    fucked-up (or I missed something very important and I must then
    stop immediatly javel that should be a piece of crap), if pc range
    does not match, we return one local var at this index, if any. */
string localvar_info::lookup(const long int pc, const int varindex) {
	string best = "";
	for (vec_lvt_t::const_iterator p = localvars.begin();
		       p != localvars.end(); ++p) {
		if (varindex == p->index) {
			if (pc >= p->start_pc &&
			pc <= p->start_pc + p->length)
				return p->name; 
			else best = p->name;
	}	}
	return best;
}	

