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

#ifndef __ATTRIBUTE_INFO_H__
#define __ATTRIBUTE_INFO_H__

#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "util.h"

class class_info;
class code_info;

class attribute_info {
	public:
		attribute_info(const class_info* ci_) : ci(ci_) { };
		virtual ~attribute_info() { cleanup(); };
		virtual void disassemble(ostream&) const;
		const class_info* get_class_info() const { return ci; };
	protected:
		const class_info* ci;
		string name;
		U4 length;
	private:
		virtual void cleanup() {};
};

class generic_attribute_info : public attribute_info {
	public:
		generic_attribute_info(istream&, const class_info*);
		virtual void disassemble(ostream& os) const {};
	private:
};

class constantvalue_info : public attribute_info {
	public:
		constantvalue_info(istream&, const class_info*);
		virtual void disassemble(ostream&) const;
	private:
		string value;
};

class sourcefile_info : public attribute_info {
	public:
		sourcefile_info(istream&, const class_info*);
		virtual void disassemble(ostream&) const;
	private:
		string source_filename;
};

class linenumtbl_info : public attribute_info {
	public:
		linenumtbl_info(istream&, const class_info*);
		void check_line(long int, long int, ostream&) const;
	private:
		struct lnt {
			U2 start_pc;
			U2 line_number;
		};
		typedef vector<lnt> vec_lnt_t;
		vec_lnt_t linenums;
};

class localvar_info : public attribute_info {
	public:
		localvar_info(istream&, const class_info*);
		string lookup(const long int, const int);
	private:
		struct lvt {
			U2 start_pc, length;
			string name;
			U2 descr_index;
			U2 index;
		};
		typedef vector<lvt> vec_lvt_t;
		vec_lvt_t localvars;
};

class exception_info : public attribute_info {
	public:
		exception_info(istream&, const class_info*);
		virtual void disassemble(ostream&) const;
		virtual void makedepend(depend_list&) const;
	private:
		typedef vector<string*> vec_excp_t;
		virtual void cleanup();
		vec_excp_t exceptions;
};

typedef vector<attribute_info*> vec_attr_t;
typedef map<string, attribute_info*> map_attr_t;

class attributes_set {
	public:
		attributes_set(istream&, const class_info*);
		virtual ~attributes_set() { cleanup(); };
		exception_info* get_exceptions();
		code_info* get_code();
		constantvalue_info* get_constantvalue();
		sourcefile_info* get_sourcefile();
		linenumtbl_info* get_linenumtbl();
		localvar_info* get_localvar();
	private:
		template<class T> T* get_attribute_info(string tag, T* t);
		map_attr_t attributes;
		virtual void cleanup();
};

#endif

