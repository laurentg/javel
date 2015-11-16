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

#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "access_info.h"

access_info::access_info(istream& is, int _type = 0) {
	type = _type;
	flag = util::read_U2(is);
}

void access_info::disassemble(ostream& os) const {
	string s = "";
	if (flag & ACC_PUBLIC)			s += "public ";
	if (flag & ACC_PRIVATE)			s += "private ";
	if (flag & ACC_PROTECTED)		s += "protected ";
	if (flag & ACC_STATIC)			s += "static ";
	if (flag & ACC_FINAL)			s += "final ";
	if (type != ACC_CLASS)
		if (flag & ACC_SYNCHRONIZED)	s += "synchronized ";
	if (flag & ACC_VOLATILE)		s += "volatile ";
	if (flag & ACC_TRANSIENT)		s += "transient ";
	if (flag & ACC_ABSTRACT)		s += "abstract ";
	if (type == ACC_CLASS)
		if (flag & ACC_INTERFACE) {	s += "interface ";
		} else {			s += "class ";
		}
	if (s.length())
		s.resize(s.length() - 1);
	os << s;
}

bool access_info::check(const format_spec& fs) const {
	switch (fs.visibility()) {
		case format_spec::PRT_PRIVATE:
			return (flag &
				(ACC_PRIVATE | ACC_PROTECTED | ACC_PUBLIC));
			break;
		case format_spec::PRT_PACKAGE: // No package type in JVM specs?
		case format_spec::PRT_PROTECTED:
			return (flag & (ACC_PROTECTED | ACC_PUBLIC));
			break;
		default:
		case format_spec::PRT_PUBLIC:
			return (flag & (ACC_PUBLIC));
			break;
}	}
	
