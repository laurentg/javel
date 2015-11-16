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

#include "opc_misc.h"
#include "code_info.h"
#include "class_info.h"

/** iinc */

opc_iinc::opc_iinc(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opcode(apc, code, aci) {
	index = code[apc + 1];
	constant = code[apc + 2];
}

void opc_iinc::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "iinc ["
		<< codeinfo->get_localname(startpc + length(), index) << "] "
		<< constant << endl;
}

/** instanceof */

opc_instanceof::opc_instanceof(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opcode(apc, code, aci) {
	index = code[apc + 1] << 8 | code[apc + 2];
}

void opc_instanceof::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "instanceof "
		<< util::slash2point(codeinfo->get_class_info()
		->get_cp_info(index)->str()) << endl;
}

opcode::sim_t opc_instanceof::simulate(stack_desc* sd) {
	if (stkdsc) return SIM_DONE;
	stkdsc = new stack_desc(*sd);
	sd->push(new stk_instance(sd->pop(),
		util::slash2point(codeinfo->get_class_info()
		->get_cp_info(index)->str())));
	return SIM_OK;
}

/** checkcast */

opc_checkcast::opc_checkcast(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opcode(apc, code, aci) {
	index = code[apc + 1] << 8 | code[apc + 2];
}

void opc_checkcast::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "checkcast "
		<< util::slash2point(codeinfo->get_class_info()
		->get_cp_info(index)->str()) << endl;
}

opcode::sim_t opc_checkcast::simulate(stack_desc* sd) {
	if (stkdsc) return SIM_DONE;
	stkdsc = new stack_desc(*sd);
	sd->push(new stk_clcast(sd->pop(),
		util::slash2point(codeinfo->get_class_info()
		->get_cp_info(index)->str())));
	return SIM_OK;
}

/** monitorenter */

opc_monitorenter::opc_monitorenter(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opcode(apc, code, aci) { }

void opc_monitorenter::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "monitorenter" << endl;
}

opcode::sim_t opc_monitorenter::simulate(stack_desc* sd) {
	if (stkdsc) return SIM_DONE;
	stkdsc = new stack_desc(*sd);
	sd->pop();
	return SIM_OK;
}

void opc_monitorenter::decompile(ostream& os) const {
	os << "\t\t" << "monitorenter (";
	stkdsc->top()->decompile(os);
	os << ");" << endl;
}

/** monitorexit */

opc_monitorexit::opc_monitorexit(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opcode(apc, code, aci) { }

void opc_monitorexit::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "monitorexit" << endl;
}

opcode::sim_t opc_monitorexit::simulate(stack_desc* sd) {
	if (stkdsc) return SIM_DONE;
	stkdsc = new stack_desc(*sd);
	sd->pop();
	return SIM_OK;
}

void opc_monitorexit::decompile(ostream& os) const {
	os << "\t\t" << "monitorexit (";
	stkdsc->top()->decompile(os);
	os << ");" << endl;
}


/* EOF */
