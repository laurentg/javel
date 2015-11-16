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

static const char CVS_ID[] =
	"$Id: type_info.cc,v 1.2 2002/05/27 17:18:29 laurent Exp $";

#ifdef _HAVE_CONFIG_H
#include <config.h>
#endif // _HAVE_CONFIG_H

#include "type_info.h"

type_info::type_info(const string& s) {
	dimension = 0;
	parsed = 0;
	base_type = -1;
	while (base_type == -1) {
		switch (s[parsed]) {
			case 'V' : base_type = BASETYPE_VOID; break;
			case 'B' : base_type = BASETYPE_BYTE; break;
			case 'C' : base_type = BASETYPE_CHAR; break;
			case 'D' : base_type = BASETYPE_DOUBLE; break;
			case 'F' : base_type = BASETYPE_FLOAT; break;
			case 'I' : base_type = BASETYPE_INT; break;
			case 'J' : base_type = BASETYPE_LONG; break;
			case 'S' : base_type = BASETYPE_SHORT; break;
			case 'Z' : base_type = BASETYPE_BOOLEAN; break;
			case '[' : dimension++; parsed++; break;
			case 'L' : base_type = BASETYPE_CLASS;
				   int j = s.find(";", 0);
				   class_name = util::slash2point(
					s.substr(parsed + 1, j - parsed - 1));
				   parsed = j;
				   break;
	}	}
	parsed += 1;
}

void type_info::disassemble(ostream& os) const {
	os << str_type();
	for (int i = 0; i < dimension; i++)
		os << "[]";
}

string type_info::str_type() const {
	switch (base_type) {
		case BASETYPE_VOID:	return "void";
		case BASETYPE_BYTE:	return "byte";
		case BASETYPE_CHAR:	return "char";
		case BASETYPE_DOUBLE:	return "double";
		case BASETYPE_FLOAT:	return "float";
		case BASETYPE_INT:	return "int";
		case BASETYPE_LONG:	return "long";
		case BASETYPE_SHORT:	return "short";
		case BASETYPE_BOOLEAN:	return "boolean";
		case BASETYPE_CLASS:	return class_name;
		default:		return "?";
	}
}

void type_info::makedepend(depend_list& di) const {
	if (base_type == BASETYPE_CLASS) {
		di[util::point2slash(class_name)] = true;
}	}
	
vec_type_t type_info::parse_type_list(const string& s) {
	vec_type_t vec;
	if (s == "")
		return vec;
	unsigned int index = 0;
	do {
		type_info* ti = new type_info(s.substr(index));
		index += ti->parsed;
		vec.push_back(ti);
	} while (index < s.length());
	return vec;
}

type_info* type_info::parse_return_type(const string& s) {
	type_info* ti = new type_info(s.substr(s.find(")") + 1));
	return ti;
}

vec_type_t type_info::parse_args_list(const string& s) {
	int begin = s.find("(");
	int end = s.find(")");	
	return parse_type_list(s.substr(begin + 1, end - begin - 1));
}

