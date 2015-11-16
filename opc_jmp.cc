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

#include <sstream>

#include "opc_jmp.h"
#include "code_info.h"
#include "class_info.h"

/** goto - Branch always. */

opc_goto::opc_goto(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opcode(apc, code, aci) {
	offset_pc = code[apc + 1] << 8 | code[apc + 2];
}

void opc_goto::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "goto label_" << offset_pc + startpc
		<< endl;
}

void opc_goto::decompile(ostream& os) const {
	os << "\t\t" << "goto label_" << offset_pc + startpc << ";" << endl;
}

/** goto_w - Branch always, wide version (32 bits).
    Note: This instruction will probably never be encountered in java
    source code since some others factors limit the size of the code in each
    method to 65535 bytes long. */

opc_goto_w::opc_goto_w(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opcode(apc, code, aci) {
	offset_pc = code[apc + 1] << 24 | code[apc + 2] << 16 |
		code[apc + 3] << 8 | code[apc + 4];
}

void opc_goto_w::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "goto_w label_"
		<< offset_pc + startpc << endl;
}

void opc_goto_w::decompile(ostream& os) const {
	os << "\t\t" << "goto_w label_" << offset_pc + startpc << ";" << endl;
}

/** if_icmp_x */

opc_ificmp_x::opc_ificmp_x(const long int apc, const vector<U1>& code,
		const code_info* aci, const kind_t akind)
		: opcode(apc, code, aci), kind(akind) {
	offset_pc = code[apc + 1] << 8 | code[apc + 2];
}

void opc_ificmp_x::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "if_icmp";
	switch (kind) {
		case EQ: os << "eq"; break;
		case NE: os << "ne"; break;
		case LT: os << "lt"; break;
		case LE: os << "le"; break;
		case GT: os << "gt"; break;
		case GE: os << "ge"; break;
	}
	os << " " << offset_pc + startpc << endl;
}

void opc_ificmp_x::decompile(ostream& os) const {
	os << "\t\t" << "if (";
	if (!stkdsc->top(1).empty())
		stkdsc->top(1)->decompile(os);
       	switch (kind) {
		case EQ: os << " == "; break;
		case NE: os << " != "; break;
		case LT: os << " < "; break;
		case LE: os << " <= "; break;
		case GT: os << " > "; break;
		case GE: os << " >= "; break;
	}
	if (!stkdsc->top().empty())
		stkdsc->top()->decompile(os);
	os << ") goto label_" << offset_pc + startpc << ";" << endl;
}

opcode::sim_t opc_ificmp_x::simulate(stack_desc* sd) {
	if (stkdsc) return SIM_DONE;
	stkdsc = new stack_desc(*sd);
	stack_item si1, si2;
	si1 = sd->pop();
	si2 = sd->pop();
	return SIM_OK;
}

/** if_x */

opc_if_x::opc_if_x(const long int apc, const vector<U1>& code,
		const code_info* aci, const kind_t akind)
		: opcode(apc, code, aci), kind(akind) {
	offset_pc = code[apc + 1] << 8 | code[apc + 2];
}

void opc_if_x::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "if";
	switch (kind) {
		case EQ: os << "eq"; break;
		case NE: os << "ne"; break;
		case LT: os << "lt"; break;
		case LE: os << "le"; break;
		case GT: os << "gt"; break;
		case GE: os << "ge"; break;
	}
	os << " " << offset_pc + startpc << endl;
}

void opc_if_x::decompile(ostream& os) const {
	os << "\t\t" << "if (";
	stkdsc->top()->decompile(os);
       	switch (kind) {
		case EQ: os << " == "; break;
		case NE: os << " != "; break;
		case LT: os << " < "; break;
		case LE: os << " <= "; break;
		case GT: os << " > "; break;
		case GE: os << " >= "; break;
	}
	os << "0) goto label_" << offset_pc + startpc << ";" << endl;
}

opcode::sim_t opc_if_x::simulate(stack_desc* sd) {
	if (stkdsc) return SIM_DONE;
	stkdsc = new stack_desc(*sd);
	stack_item si;
	si = sd->pop();
	return SIM_OK;
}

/** ifnull, ifnonnull */

opc_ifnnull::opc_ifnnull(const long int apc, const vector<U1>& code,
		const code_info* aci, const kind_t akind)
		: opcode(apc, code, aci), kind(akind) {
	offset_pc = code[apc + 1] << 8 | code[apc + 2];
}

void opc_ifnnull::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "if";
	switch (kind) {
		case EQ: os << "null"; break;
		case NE: os << "nonnull"; break;
	}
	os << " " << offset_pc + startpc << endl;
}

void opc_ifnnull::decompile(ostream& os) const {
	os << "\t\t" << "if (";
	stkdsc->top()->decompile(os);
       	switch (kind) {
		case EQ: os << " == "; break;
		case NE: os << " != "; break;
	}
	os << "null) goto label_" << offset_pc + startpc << ";" << endl;
}

opcode::sim_t opc_ifnnull::simulate(stack_desc* sd) {
	if (stkdsc) return SIM_DONE;
	stkdsc = new stack_desc(*sd);
	stack_item si;
	si = sd->pop();
	return SIM_OK;
}

/** if_acmpeq, if_acmpne */

opc_ifacmp_x::opc_ifacmp_x(const long int apc, const vector<U1>& code,
		const code_info* aci, const kind_t akind)
		: opcode(apc, code, aci), kind(akind) {
	offset_pc = code[apc + 1] << 8 | code[apc + 2];
}

void opc_ifacmp_x::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "if_acmp";
	switch (kind) {
		case EQ: os << "eq"; break;
		case NE: os << "ne"; break;
	}
	os << " " << offset_pc + startpc << endl;
}

void opc_ifacmp_x::decompile(ostream& os) const {
	os << "\t\t" << "if (";
	stkdsc->top(1)->decompile(os);
       	switch (kind) {
		case EQ: os << " == "; break;
		case NE: os << " != "; break;
	}
	stkdsc->top()->decompile(os);
	os << ") goto label_" << offset_pc + startpc << ";" << endl;
}

opcode::sim_t opc_ifacmp_x::simulate(stack_desc* sd) {
	if (stkdsc) return SIM_DONE;
	stkdsc = new stack_desc(*sd);
	stack_item si;
	si = sd->pop();
	si = sd->pop();
	return SIM_OK;
}

/** athrow */

opc_athrow::opc_athrow(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opcode(apc, code, aci) { }

void opc_athrow::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "athrow" << endl;
}

void opc_athrow::decompile(ostream& os) const {
	os << "\t\t" << "throw ";
	stkdsc->top()->decompile(os);
	os << ";" << endl;
}

opcode::sim_t opc_athrow::simulate(stack_desc* sd) {
	if (stkdsc) return SIM_DONE;
	stkdsc = new stack_desc(*sd);
	stack_item si;
	si = sd->pop();
	return SIM_OK;
}

/** jsr - Jump to subroutine (finally block). */

opc_jsr::opc_jsr(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opcode(apc, code, aci) {
	offset_pc = code[apc + 1] << 8 | code[apc + 2];
}

void opc_jsr::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "jsr label_" << offset_pc + startpc
		<< endl;
}

void opc_jsr::decompile(ostream& os) const {
	os << "\t\t" << "jsr label_" << offset_pc + startpc << ";" << endl;
}

opcode::sim_t opc_jsr::simulate(stack_desc* sd) {
	if (stkdsc) return SIM_DONE;
	stkdsc = new stack_desc(*sd);
	return SIM_OK;
}

opcode::sim_t opc_jsr::simulate_goto(stack_desc* sd) {
	if (stkdsc) return SIM_DONE;
	stkdsc = new stack_desc(*sd);
	/** TEMPORARY */
	ostringstream oss;
	sd->push(new stk_const("<PC>"));
	return SIM_OK;
}

/** ret - Return from subroutine (finally block). */

opc_ret::opc_ret(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opcode(apc, code, aci) {
	index = code[apc + 1];
}

void opc_ret::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "ret [" <<
		codeinfo->get_localname(startpc + length(), index)
		<< "]" << endl;
}

void opc_ret::decompile(ostream& os) const {
	os << "\t\t" << "ret" <<
		codeinfo->get_localname(startpc + length(), index) << endl;
}

opcode::sim_t opc_ret::simulate(stack_desc* sd) {
	if (stkdsc) return SIM_DONE;
	stkdsc = new stack_desc(*sd);
	return SIM_OK;
}

/* EOF */
