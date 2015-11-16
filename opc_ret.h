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

#ifndef __OPC_RET_H__
#define __OPC_RET_H__

#include <iostream>
#include <vector>

#include "util.h"
#include "stacks.h"
#include "opcode.h"

class opc_ireturn : public opcode {
	public:
		opc_ireturn(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual void disassemble(ostream&) const;
		virtual void decompile(ostream&) const;
		virtual sim_t simulate(stack_desc*);
		virtual int length() const { return 1; };
		virtual int nextpc() const { return -1; };
};

class opc_return : public opcode {
	public:
		opc_return(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual void disassemble(ostream&) const;
		virtual void decompile(ostream&) const;
		virtual int length() const { return 1; };
		virtual int nextpc() const { return -1; };
};

#endif
