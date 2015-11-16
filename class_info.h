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

#ifndef __CLASS_INFO_H__
#define __CLASS_INFO_H__

#include <iostream>
#include <vector>
#include <string>

#include "cp_info.h"
#include "field_info.h"
#include "method_info.h"
#include "format_spec.h"

/** Instances of class_info are describing a single java class.
    For now, no others classes can be linked to it, but in the
    future that can be part of the design. Constructed from an 
    input stream representing the compiled class data.
    Pattern: Facade to all other classes in javel. */
class class_info {
	public:
		class_info(istream& is);
		virtual ~class_info();
		const cp_info* get_cp_info(const int) const;
		const string get_source_line(const int) const;
		string get_class_name() const { return this_class; };
		void disassemble(const format_spec& fs, ostream& os) const;
		void makedepend(const string filename, ostream& os) const;
		
	protected:
	private:
		typedef map<U1,cp_info*> map_cp_info_t;
		typedef vector<cp_info*> vec_cp_info_t;
		typedef vector<U2> vec_interfaces_t;
		typedef vector<field_info*> vec_field_t;
		typedef vector<method_info*> vec_method_t;
		
		virtual void cleanup();
		void load_source(const string&) const;
		cp_info* create_cp_info(U1 tag) const;

		map_cp_info_t cp_tmpl;
		U2 minor_version;
		U2 major_version;
		vec_cp_info_t cp_infos;
		access_info* access_flags;
		string this_class;
		string super_class;
		vec_interfaces_t interfaces;
		vec_field_t fields;
		vec_method_t methods;
		attributes_set* attributes;
		mutable vector<string> sourcelines;
};

#endif

