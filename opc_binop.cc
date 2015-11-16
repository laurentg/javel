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

#include "opc_binop.h"
#include "code_info.h"
#include "class_info.h"

/** iadd */

opc_iadd::opc_iadd(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opcode(apc, code, aci) { };
		
void opc_iadd::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "iadd" << endl;
}

opcode::sim_t opc_iadd::simulate(stack_desc* sd) {
	if (stkdsc) return SIM_DONE;
	stkdsc = new stack_desc(*sd);
	stack_item si1, si2;
	si2 = sd->pop();
	si1 = sd->pop();
	stack_item si3(new stk_binop(si1, si2, stk_binop::ADD));
	sd->push(si3);
	return SIM_OK;
}

/** imul */

opc_imul::opc_imul(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opcode(apc, code, aci) { };
		
void opc_imul::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "imul" << endl;
}

opcode::sim_t opc_imul::simulate(stack_desc* sd) {
	if (stkdsc) return SIM_DONE;
	stkdsc = new stack_desc(*sd);
	stack_item si1, si2;
	si2 = sd->pop();
	si1 = sd->pop();
	stack_item si3(new stk_binop(si1, si2, stk_binop::MUL));
	sd->push(si3);
	return SIM_OK;
}

/** lcmp - Compare two longs and push the result (-1, 0, 1) onto the stack. */

opc_lcmp::opc_lcmp(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opcode(apc, code, aci) { };
		
void opc_lcmp::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "lcmp" << endl;
}

opcode::sim_t opc_lcmp::simulate(stack_desc* sd) {
	if (stkdsc) return SIM_DONE;
	stkdsc = new stack_desc(*sd);
	stack_item si1, si2;
	si2 = sd->pop();
	si1 = sd->pop();
	stack_item si3(new stk_binop(si1, si2, stk_binop::LCMP));
	sd->push(si3);
	return SIM_OK;
}

/** conv - Convert one basetype to another (cast). */

opc_conv::opc_conv(const long int apc, const vector<U1>& code,
		const code_info* aci, const kind_t akind)
		: opcode(apc, code, aci), kind(akind) { };
		
void opc_conv::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t";
	switch (kind) {
		case I2L : os << "i2l"; break;
		case L2I : os << "l2i"; break;
	}
	os << endl;
}

opcode::sim_t opc_conv::simulate(stack_desc* sd) {
	if (stkdsc) return SIM_DONE;
	stkdsc = new stack_desc(*sd);
	stk_conv::kind_t akind;
	switch (kind) {
		case I2L : akind = stk_conv::I2L; break;
		case L2I : akind = stk_conv::L2I; break;
	}
	sd->push(new stk_conv(sd->pop(), akind));
	return SIM_OK;
}


/* EOF */
