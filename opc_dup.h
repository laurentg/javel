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

#ifndef __OPC_DUP_H__
#define __OPC_DUP_H__

#include <iostream>
#include <vector>

#include "util.h"
#include "stacks.h"
#include "opcode.h"


class opc_dup : public opcode {
	public:
		opc_dup(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual void disassemble(ostream&) const;
		virtual sim_t simulate(stack_desc*);
		virtual int length() const { return 1; };
};

class opc_dup_x1 : public opcode {
	public:
		opc_dup_x1(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual void disassemble(ostream&) const;
		virtual sim_t simulate(stack_desc*);
		virtual int length() const { return 1; };
};

class opc_dup_x2 : public opcode {
	public:
		opc_dup_x2(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual void disassemble(ostream&) const;
		virtual sim_t simulate(stack_desc*);
		virtual int length() const { return 1; };
};

class opc_dup2 : public opcode {
	public:
		opc_dup2(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual void disassemble(ostream&) const;
		virtual sim_t simulate(stack_desc*);
		virtual int length() const { return 1; };
};

class opc_dup2_x1 : public opcode {
	public:
		opc_dup2_x1(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual void disassemble(ostream&) const;
		virtual sim_t simulate(stack_desc*);
		virtual int length() const { return 1; };
};

class opc_dup2_x2 : public opcode {
	public:
		opc_dup2_x2(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual void disassemble(ostream&) const;
		virtual sim_t simulate(stack_desc*);
		virtual int length() const { return 1; };
};

class opc_swap : public opcode {
	public:
		opc_swap(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual void disassemble(ostream&) const;
		virtual sim_t simulate(stack_desc*);
		virtual int length() const { return 1; };
};

class opc_pop : public opcode {
	public:
		opc_pop(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual void disassemble(ostream&) const;
		virtual sim_t simulate(stack_desc*);
		virtual int length() const { return 1; };
};

class opc_pop2 : public opcode {
	public:
		opc_pop2(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual void disassemble(ostream&) const;
		virtual sim_t simulate(stack_desc*);
		virtual int length() const { return 1; };
};

#endif
