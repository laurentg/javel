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

#ifndef __FIELD_INFO_H__
#define __FIELD_INFO_H__

#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "access_info.h"
#include "attribute_info.h"
#include "format_spec.h"

class field_info {
	public:
		field_info(istream&, const class_info*);
		virtual ~field_info() { cleanup(); };
		virtual void disassemble(const format_spec&, ostream&) const;
		virtual void makedepend(depend_list& di) const;
	protected:
		const class_info* ci;
	private:
		virtual void cleanup();
		access_info* access_flags;
		type_info* type;
		string name;
		attributes_set* attributes;
};

#endif

