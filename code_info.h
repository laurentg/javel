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

#ifndef __CODE_INFO_H__
#define __CODE_INFO_H__

#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "util.h"
#include "attribute_info.h"
#include "format_spec.h"
#include "opcode.h"

class method_info;

class code_info : public attribute_info {
	public:
		code_info(istream&, const class_info*);
		virtual void disassemble(const format_spec&, ostream&) const;
		virtual void simulate();
		string get_localname(const long int, const int) const;
		string get_paramname(const int) const;
		void set_method(method_info* mi) { method = mi; };
		
	private:
		class exception_t {
			public:
				U2 start_pc;
				U2 end_pc;
				U2 handler_pc;
				string catch_type;
		};
		void check_excp(const long int, const long int,
			ostream&) const;
		void check_line(const long int, const long int,
			ostream&) const;
		opcode* getopcode(const int);
		virtual void simulate(const int, stack_desc*);
		virtual void cleanup();
		U2 max_stack;
		U2 max_locals;
		vector<U1> code;
		typedef map<int, opcode*> opcset_t;
		mutable opcset_t opcodes;
		vector<exception_t> exceptions_table;
		attributes_set* attributes;
		method_info* method;
};

#endif

