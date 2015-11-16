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

#ifndef __TYPE_INFO_H__
#define __TYPE_INFO_H__

#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "util.h"

class type_info;
typedef vector<type_info*> vec_type_t;

class type_info {
	public:
		static const int BASETYPE_VOID		= 0;
		static const int BASETYPE_BYTE		= 1;
		static const int BASETYPE_CHAR		= 2;
		static const int BASETYPE_DOUBLE	= 3;
		static const int BASETYPE_FLOAT		= 4;
		static const int BASETYPE_INT		= 5;
		static const int BASETYPE_LONG		= 6;
		static const int BASETYPE_SHORT		= 7;
		static const int BASETYPE_BOOLEAN	= 8;
		static const int BASETYPE_CLASS		= 9;
		type_info(const string&);
		virtual ~type_info() { };
		virtual void disassemble(ostream&) const;
		virtual void makedepend(depend_list& di) const;
		string str_type() const;
		static vec_type_t parse_type_list(const string&);
		static type_info* parse_return_type(const string&);
		static vec_type_t parse_args_list(const string&);
		int get_basetype() const { return base_type; };
	private:
		int base_type;
		string class_name;
		int dimension;
		int parsed;
};

#endif

