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

#include "util.h"

U1 util::read_U1(istream& is) {
	U1 retval;
	is.get(retval);
	return retval;
}

U2 util::read_U2(istream& is) {
	U2 retval;
	unsigned char* p = (unsigned char*)&retval + 1;
	is.get(*p--);
	is.get(*p--);
	return retval;
}

U4 util::read_U4(istream& is) {
	U4 retval;
	unsigned char* p = (unsigned char*)&retval + 3;
	is.get(*p--);
	is.get(*p--);
	is.get(*p--);
	is.get(*p--);
	return retval;
}

string util::slash2point(string s) {
	for (string::iterator p = s.begin(); p != s.end(); p++)
		if (*p == '/') *p = '.';
	return s;
}

string util::point2slash(string s) {
	for (string::iterator p = s.begin(); p != s.end(); p++)
		if (*p == '.') *p = '/';
	return s;
}

