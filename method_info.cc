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

#include "method_info.h"
#include "class_info.h"
#include "code_info.h"

method_info::method_info(istream& is, const class_info* _ci) {
	ci = _ci;
	access_flags = new access_info(is);
	U2 name_index = util::read_U2(is);
	name = ci->get_cp_info(name_index)->str();
	if (name == "<init>") {
		type = MT_CONSTRUCTOR;
		name = util::slash2point(ci->get_class_name());
	} else if (name == "finalize") {
		type = MT_FINALIZER;
	} else {
		type = MT_METHOD;
	}
	U2 descriptor_index = util::read_U2(is);
	string descriptor = ci->get_cp_info(descriptor_index)->str();
	return_type = type_info::parse_return_type(descriptor);
	param_types = type_info::parse_args_list(descriptor);
	attributes = new attributes_set(is, ci);
	code_info* code = attributes->get_code();
	if (code) code->set_method(this);
}

void method_info::cleanup() {
	for (vec_type_t::iterator p = param_types.begin();
			p != param_types.end(); p++)
		delete *p;
	delete access_flags;
	delete return_type;	
	delete attributes;
}

bool method_info::isstatic() const {

	return (access_flags->get_flag() & access_info::ACC_STATIC);
}

void method_info::disassemble(const format_spec& fs, ostream& os) const {
	if (!access_flags->check(fs))
		return;
	code_info* code = attributes->get_code();
	os << "\t";
	access_flags->disassemble(os);
	if (access_flags->get_flag())
		os << " ";
	if (type != MT_CONSTRUCTOR) {
		return_type->disassemble(os);
		os << " ";
	}
	os << name;
	os << "(";
	/** We use i + 1 due to the hidden 'this' 0th param.,
	    except for static methods. We increment index by 2 for long and
	    double variables (two slots taken). */
	int index = isstatic() ? 0 : 1;
	for (int i = 0; i < param_types.size(); i++) {
		param_types[i]->disassemble(os);
		/** Output the param name, if any. */
		if (code) {
			string paramname = code->get_paramname(index);
			if (paramname != "")
				os << " " << paramname;
		}
		if (i < param_types.size() - 1)
			os << ", ";
		int btype = param_types[i]->get_basetype();
		if (btype == type_info::BASETYPE_LONG ||
		    btype == type_info::BASETYPE_DOUBLE) index += 2;
		else index += 1;
	}
	os << ")";
	exception_info* excp = attributes->get_exceptions();
	if (excp) {
		os << endl;
		excp->disassemble(os);
	}
	os << " {" << endl;
	if (code) {
		code->disassemble(fs, os);
	}
	os << "\t" << "}" << endl;
}

void method_info::makedepend(depend_list& di) const {
	if (type != MT_CONSTRUCTOR) {
		return_type->makedepend(di);
	}
	for (vec_type_t::const_iterator p = param_types.begin();
			p != param_types.end(); ++p) {
		(*p)->makedepend(di);
	}
	exception_info* excp = attributes->get_exceptions();
	if (excp) {
		excp->makedepend(di);
	}
}
