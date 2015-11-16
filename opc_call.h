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

#ifndef __OPC_CALL_H__
#define __OPC_CALL_H__

#include <iostream>
#include <vector>

#include "util.h"
#include "stacks.h"
#include "opcode.h"


class opc_invoke : public opcode {
	public:
		opc_invoke(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual sim_t simulate(stack_desc*);
		virtual int length() const { return 3; };
	protected:
		int index;
};

class opc_invokespecial : public opc_invoke {
	public:
		opc_invokespecial(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual ~opc_invokespecial();
		virtual void disassemble(ostream&) const;
		virtual void decompile(ostream&) const;
		opcode::sim_t simulate(stack_desc*);
	private:
		stk_func* f;
};

class opc_invokevirtual : public opc_invoke {
	public:
		opc_invokevirtual(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual ~opc_invokevirtual();
		virtual void disassemble(ostream&) const;
		virtual void decompile(ostream&) const;
		opcode::sim_t simulate(stack_desc*);
	private:
		stk_func* f;
};

class opc_invokestatic : public opc_invoke {
	public:
		opc_invokestatic(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual ~opc_invokestatic();
		virtual void disassemble(ostream&) const;
		virtual void decompile(ostream&) const;
		opcode::sim_t simulate(stack_desc*);
	private:
		stk_func* f;
};

class opc_invokeinterface : public opc_invoke {
	public:
		opc_invokeinterface(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual ~opc_invokeinterface();
		virtual void disassemble(ostream&) const;
		virtual void decompile(ostream&) const;
		opcode::sim_t simulate(stack_desc*);
		virtual int length() const { return 5; };
	private:
		stk_func* f;
		int count;
};

class opc_new : public opcode {
	public:
		opc_new(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual void disassemble(ostream&) const;
		opcode::sim_t simulate(stack_desc*);
		virtual int length() const { return 3; };
	private:
		int index;
};

#endif
