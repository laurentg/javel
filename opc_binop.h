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

#ifndef __OPC_BINOP_H__
#define __OPC_BINOP_H__

#include <iostream>
#include <vector>

#include "util.h"
#include "stacks.h"
#include "opcode.h"

/** int operators */

class opc_iadd : public opcode {
	public:
		opc_iadd(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual void disassemble(ostream&) const;
		virtual int length() const { return 1; };
		virtual sim_t simulate(stack_desc*);
};

class opc_imul : public opcode {
	public:
		opc_imul(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual void disassemble(ostream&) const;
		virtual int length() const { return 1; };
		virtual sim_t simulate(stack_desc*);
};

/** long operators */

class opc_lcmp : public opcode {
	public:
		opc_lcmp(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual void disassemble(ostream&) const;
		virtual int length() const { return 1; };
		virtual sim_t simulate(stack_desc*);
};

/** conversion operators (i2l, i2f...) */

class opc_conv : public opcode {
	public:
		enum kind_t { I2L, L2I };
		opc_conv(const long int apc, const vector<U1>& code,
				const code_info* aci, const kind_t akind);
		virtual void disassemble(ostream&) const;
		virtual int length() const { return 1; };
		virtual sim_t simulate(stack_desc*);
	private:
		kind_t kind;
};

#endif
