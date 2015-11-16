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

#ifndef __OPCODE_H__
#define __OPCODE_H__

#include <iostream>
#include <vector>

#include "util.h"
#include "stacks.h"

class code_info; // Forward

class opcode {
	public:
		enum sim_t { SIM_OK, SIM_DONE };
		opcode(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual ~opcode();
		virtual int length() const = 0;
		virtual void disassemble(ostream&) const = 0;
		virtual void decompile(ostream&) const { };
		virtual sim_t simulate(stack_desc*);
		virtual sim_t simulate_goto(stack_desc*);
		virtual int nextpc() const { return startpc + length(); };
		virtual int gotopc() const { return -1; };
		void target(bool b) { istarget = b; };
		bool target() const { return istarget; };

		const stack_desc* get_stack() const { return stkdsc; };

		static opcode* opcode_factory(const long int apc,
				const vector<U1>& code, const code_info* aci);
	protected:
		long int startpc;
		const code_info* codeinfo;
		/** The stack BEFORE the execution of the opcode on it. */
		stack_desc* stkdsc;
	private:
		bool istarget;
};

class opc_nop : public opcode {
	public:
		opc_nop(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual int length() const { return 1; };
		virtual void disassemble(ostream&) const ;
};

#endif
