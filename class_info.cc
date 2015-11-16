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
#include <fstream>
using namespace std;

#include "class_info.h"
#include "version.h"

/** This class is the main entry point to the javel tool.
    It reads a class file and construct a class_info object
    from the specified stream. This object can then be used
    to dump all informations needed from it. */
class_info::class_info(istream& is) {
	/** Init prototype constant pool cp_info templates table. */
	cp_tmpl[CONSTANT_CLASS]			= new cp_class_info(this);
	cp_tmpl[CONSTANT_UTF8]			= new cp_utf8_info(this);
	cp_tmpl[CONSTANT_NAMEANDTYPE]		= new cp_nameandtype_info(this);
	cp_tmpl[CONSTANT_FIELDREF]		= new cp_fieldref_info(this);
	cp_tmpl[CONSTANT_METHODREF]		= new cp_methodref_info(this);
	cp_tmpl[CONSTANT_INTERFACEMETHODREF]
		= new cp_interfacemethodref_info(this);
	cp_tmpl[CONSTANT_STRING]		= new cp_string_info(this);
	cp_tmpl[CONSTANT_INTEGER]		= new cp_integer_info(this);
	cp_tmpl[CONSTANT_FLOAT]			= new cp_float_info(this);
	cp_tmpl[CONSTANT_LONG]			= new cp_long_info(this);
	cp_tmpl[CONSTANT_DOUBLE]		= new cp_double_info(this);

	/** Read header from the stream. */
	U4 magic = util::read_U4(is);
	if (magic != 0xCAFEBABE)
		throw fileformat_exception();
	minor_version = util::read_U2(is);
	major_version = util::read_U2(is);
	/** Read constant pool informations. */
	U2 constant_pool_count = util::read_U2(is);
	for (int i = 1; i < constant_pool_count;) {
		U1 tag = util::read_U1(is);
		cp_info* cpi = create_cp_info(tag);
		if (!cpi)
			throw fileformat_exception();
		cpi->get(is);
		cp_infos.push_back(cpi);
		int di = cpi->get_num_slots();
		i += di;
		for (int j = 0; j < di - 1; j++)
			cp_infos.push_back(0);
	}
	/** Read the whole thing. */
	access_flags = new access_info(is, access_info::ACC_CLASS);
	U2 this_class_index = util::read_U2(is);
	this_class = get_cp_info(this_class_index)->str();
	U2 super_class_index = util::read_U2(is);
	super_class = get_cp_info(super_class_index)->str();
	U2 interfaces_count = util::read_U2(is);
	for (int i = 0; i < interfaces_count; i++)
		interfaces.push_back(util::read_U2(is));
	U2 fields_count = util::read_U2(is);
	for (int i = 0; i < fields_count; i++)
		fields.push_back(new field_info(is, this));
	U2 methods_count = util::read_U2(is);
	for (int i = 0; i < methods_count; i++)
		methods.push_back(new method_info(is, this));
	attributes = new attributes_set(is, this);
}

/** Delete all cp_infos and call cleanup. */
class_info::~class_info() {
	for (map_cp_info_t::iterator p = cp_tmpl.begin();
			p != cp_tmpl.end(); p++)
		delete p->second;
	cp_tmpl.clear();
	cleanup();
}

/** Cleanup and delete all allocated structures, except the
    cp_infos vector. */
void class_info::cleanup() {
	for (vec_cp_info_t::iterator p = cp_infos.begin();
			p != cp_infos.end(); p++)
		delete *p;
	cp_infos.clear();
	for (vec_field_t::iterator p = fields.begin();
			p != fields.end(); p++)
		delete *p;
	fields.clear();
	for (vec_method_t::iterator p = methods.begin();
			p != methods.end(); p++)
		delete *p;
	methods.clear();
	delete attributes;
	delete access_flags;
}

/** @param index The index of the entry in the constant pool table.
    @return The constant pool info (cp_info) entry of the class. */
const cp_info* class_info::get_cp_info(const int index) const {
	return cp_infos[index-1];
}

/** Gets a source line in the source code, if any.
    @param linenum The line number in the source.
    @return The string of the corresponding source code. */
const string class_info::get_source_line(const int linenum) const {
	if (linenum < 0 || linenum >= sourcelines.size())
		return "<no source>";
	return sourcelines[linenum];
}

/** Load the source code.
    @param The filename of the source code file to load. */
void class_info::load_source(const string& filename) const {
	ifstream in(filename.c_str());
	sourcelines.clear();
	if (!in) return; /** Ignore the error, not important. */
	while (in) {
		string line;
		getline(in, line);
		sourcelines.push_back(line);
	}
}

/** Disassemble the class to the output stream specified.
    @param fs The format specifier to modify the kind of output.
    @param os The output stream where to dump informations. */
void class_info::disassemble(const format_spec& fs, ostream& os) const {
	/** Load source file if we specified options and source file
	    information is present. We cannot do it before because we
	    need to have a format_spec to see if we specified the source
	    information disassembled. */
	sourcefile_info* sfi = attributes->get_sourcefile();
	if (sfi && fs.linenumber()) {
		ostringstream oss;
		sfi->disassemble(oss);
		load_source(oss.str());
	}
	/** Disassemble. */
	os << dec << endl;
	os << "/* Java header file automatically disassembled" << endl;
	os << "   by Javel version : " << VERSION << endl;
	os << "   Class file version : " << major_version << "." <<
		minor_version << endl;
	if (sfi) {
		os << "   Source file : ";
		sfi->disassemble(os);
		os << endl;
	}
	os << "*/" << endl << endl;
	access_flags->disassemble(os);
	os << " " << util::slash2point(this_class);
	os << endl << "\t" << "extends " << util::slash2point(super_class);
	if (interfaces.size()) {
		os << endl << "\t" << "implements ";
		for (int i = 0; i < interfaces.size(); i++) {
			os << util::slash2point(
					get_cp_info(interfaces[i])->str());
			if (i < interfaces.size() - 1)
				os << "," << endl << "\t\t\t";
	}	}
	os << " {" << endl << endl;
	for (int i = 0; i < fields.size(); i++)
		fields[i]->disassemble(fs, os);
	os << endl;
	for (int i = 0; i < methods.size(); i++)
		methods[i]->disassemble(fs, os);
	os << "}" << endl << "/* EOF */" << endl;
}

/** Output dependencies of the class to the output stream specified.
    @param os The output stream where to dump informations. */
void class_info::makedepend(const string filename, ostream& os) const {
	depend_list di;
	for (vec_cp_info_t::const_iterator p = cp_infos.begin();
			p != cp_infos.end(); ++p) {
		if (*p) {
			(*p)->makedepend(di);
	}	}
	/** Remove all classes which begins with "java/" and "sun/",
	    and/or ends with "$n" (which are inner classes). */
	for (depend_list::iterator p = di.begin(); p != di.end(); ++p) {
		if (!p->first.substr(0, 5).compare("java/") ||
		    !p->first.substr(0, 4).compare("sun/"))
			p->second = false;
		if ((signed int)(p->first.find("$")) >= 0)
			p->second = false;
	}
	os << filename << ":";
	for (depend_list::const_iterator p = di.begin(); p != di.end(); ++p) {
		if (p->second) {
			os << " \\" << endl << "\t" << p->first + ".java";
	}	}
	os << endl;
}

/** @return A new constant pool info object corresponding to the
    index which is really a 'tag' as defined in the jvm specs.
    The prototype instances are created in the class_info constructor.
    Pattern: Prototype */
cp_info* class_info::create_cp_info(const U1 tag) const {
	map_cp_info_t::const_iterator p = cp_tmpl.find(tag);
	if (p == cp_tmpl.end())
		return 0;
	return (p->second->clone());
}

