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

#ifndef __ACCESS_INFO_H__
#define __ACCESS_INFO_H__

#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "util.h"
#include "format_spec.h"

class access_info {
	public:
		static const int ACC_PUBLIC		= 0x0001;
		static const int ACC_PRIVATE		= 0x0002;
		static const int ACC_PROTECTED		= 0x0004;
		static const int ACC_STATIC		= 0x0008;
		static const int ACC_FINAL		= 0x0010;
		static const int ACC_SUPER		= 0x0020;
		static const int ACC_SYNCHRONIZED	= 0x0020; /* Same! */
		static const int ACC_VOLATILE		= 0x0040;
		static const int ACC_TRANSIENT		= 0x0080;
		static const int ACC_INTERFACE		= 0x0200;
		static const int ACC_ABSTRACT		= 0x0400;
		static const int ACC_STRICT		= 0x0800;
		static const int ACC_CLASS 		= 1;
		
		access_info(istream& is, int _type = 0);
		virtual ~access_info() {};
		virtual void disassemble(ostream&) const;
		const U2 get_flag() const { return flag; };
		bool check(const format_spec& fs) const;
	private:
		U2 flag;
		int type;
};

#endif

