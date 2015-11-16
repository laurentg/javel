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

#include "field_info.h"
#include "class_info.h"

field_info::field_info(istream& is, const class_info* _ci) {
	ci = _ci;
	access_flags = new access_info(is);
	U2 name_index = util::read_U2(is);
	name = ci->get_cp_info(name_index)->str();
	U2 descriptor_index = util::read_U2(is);
	type = new type_info(ci->get_cp_info(descriptor_index)->str());
	attributes = new attributes_set(is, ci);
}

void field_info::cleanup() {
	delete type;
	delete access_flags;
	delete attributes;
}	

void field_info::disassemble(const format_spec& fs, ostream& os) const {
	if (!access_flags->check(fs))
		return;
	os << "\t";
	access_flags->disassemble(os);
	if (access_flags->get_flag())
		os << " ";
	type->disassemble(os);
	os << " " << name;
	constantvalue_info* cval = attributes->get_constantvalue();
	if (cval) {
		os << " = ";
		cval->disassemble(os);
	}
	os << ";" << endl;
}

void field_info::makedepend(depend_list& di) const {
	type->makedepend(di);
}

