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

#include "opc_ret.h"
#include "code_info.h"
#include "class_info.h"


/** ireturn */

opc_ireturn::opc_ireturn(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opcode(apc, code, aci) { }

void opc_ireturn::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "ireturn" << endl;
}

void opc_ireturn::decompile(ostream& os) const {
	os << "\t\t" << "return ";
	if (!stkdsc->top().empty())
		stkdsc->top()->decompile(os);
	os << ";" << endl;
}

opcode::sim_t opc_ireturn::simulate(stack_desc* sd) {
	if (stkdsc) return SIM_DONE;
	stkdsc = new stack_desc(*sd);
	stack_item si;
	si = sd->pop();
	return SIM_OK;
}

/** return */

opc_return::opc_return(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opcode(apc, code, aci) { }

void opc_return::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "return" << endl;
}

void opc_return::decompile(ostream& os) const {
	os << "\t\t" << "return;" << endl;
}

/* EOF */
