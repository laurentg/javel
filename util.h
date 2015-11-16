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

#ifndef __UTIL_H__
#define __UTIL_H__

#include <iostream>
#include <vector>
#include <map>
#include <string>

/* Machine dependant declarations */

typedef unsigned long int	U4;
typedef unsigned short int	U2;
typedef unsigned char		U1;

typedef map<string, bool>	depend_list;

class javel_exception {
	public:
		friend ostream& operator<<(ostream& os, javel_exception& je) {
			je.put(os);
			return os;
		};
	private:
		virtual void put(ostream& os)
			{ os << "exception"; };
};

class fileformat_exception : public javel_exception {
	private:
		virtual void put(ostream& os)
			{ os << "file format exception"; };
};

class io_exception : public javel_exception {
	private:
		virtual void put(ostream& os)
			{ os << "IO exception"; };
};

class util {
	public:
		static U1 read_U1(istream&);
		static U2 read_U2(istream&);
		static U4 read_U4(istream&);
		static string slash2point(string);
		static string point2slash(string);
};

#endif

