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

#include "opc_dup.h"
#include "code_info.h"
#include "class_info.h"

/** dup
    Action: ... [a] -> ... [a] [a] */

opc_dup::opc_dup(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opcode(apc, code, aci) { }

void opc_dup::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "dup" << endl;
}

opcode::sim_t opc_dup::simulate(stack_desc* sd) {
	if (stkdsc) return SIM_DONE;
	stkdsc = new stack_desc(*sd);
	sd->push(sd->top());
	return SIM_OK;
}

/** dup_x1
    Action:  ... [b] [a] -> ... [a] [b] [a] */

opc_dup_x1::opc_dup_x1(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opcode(apc, code, aci) { }

void opc_dup_x1::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "dup_x1" << endl;
}

opcode::sim_t opc_dup_x1::simulate(stack_desc* sd) {
	if (stkdsc) return SIM_DONE;
	stkdsc = new stack_desc(*sd);
	stack_item a = sd->pop();
	stack_item b = sd->pop();
	sd->push(a);
	sd->push(b);
	sd->push(a);
	return SIM_OK;
}

/** dup_x2
    Action: ... [c] [b] [a] -> ... [a] [c] [b] [a] */

opc_dup_x2::opc_dup_x2(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opcode(apc, code, aci) { }

void opc_dup_x2::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "dup_x2" << endl;
}

opcode::sim_t opc_dup_x2::simulate(stack_desc* sd) {
	if (stkdsc) return SIM_DONE;
	stkdsc = new stack_desc(*sd);
	stack_item a = sd->pop();
	stack_item b = sd->pop();
	stack_item c = sd->pop();
	sd->push(a);
	sd->push(c);
	sd->push(b);
	sd->push(a);
	return SIM_OK;
}

/** dup2
    Action: ... [a] -> ... [a] [a] */

opc_dup2::opc_dup2(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opcode(apc, code, aci) { }

void opc_dup2::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "dup2" << endl;
}

/** @todo When stack items are category 1 items, dup2 will pop 2 items
    and duplicate two items. NEVER seen this instruction used for that,
    but Sun specifications are clear on that, it's theorically possible. */

opcode::sim_t opc_dup2::simulate(stack_desc* sd) {
	if (stkdsc) return SIM_DONE;
	stkdsc = new stack_desc(*sd);
	sd->push(sd->top());
	return SIM_OK;
}

/** dup2_x1
    Action:  ... [b] [a] -> ... [a] [b] [a] */

opc_dup2_x1::opc_dup2_x1(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opcode(apc, code, aci) { }

void opc_dup2_x1::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "dup2_x1" << endl;
}

opcode::sim_t opc_dup2_x1::simulate(stack_desc* sd) {
	if (stkdsc) return SIM_DONE;
	stkdsc = new stack_desc(*sd);
	stack_item a = sd->pop();
	stack_item b = sd->pop();
	sd->push(a);
	sd->push(b);
	sd->push(a);
	return SIM_OK;
}

/** dup2_x2
    Action: ... [c] [b] [a] -> ... [a] [c] [b] [a] */

opc_dup2_x2::opc_dup2_x2(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opcode(apc, code, aci) { }

void opc_dup2_x2::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "dup2_x2" << endl;
}

opcode::sim_t opc_dup2_x2::simulate(stack_desc* sd) {
	if (stkdsc) return SIM_DONE;
	stkdsc = new stack_desc(*sd);
	stack_item a = sd->pop();
	stack_item b = sd->pop();
	stack_item c = sd->pop();
	sd->push(a);
	sd->push(c);
	sd->push(b);
	sd->push(a);
	return SIM_OK;
}

/** swap - Swap the two topmost items on the stack. Only for cat1.
    Action: ... [b] [a] -> ... [a] [b] */

opc_swap::opc_swap(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opcode(apc, code, aci) { }

void opc_swap::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "swap" << endl;
}

opcode::sim_t opc_swap::simulate(stack_desc* sd) {
	if (stkdsc) return SIM_DONE;
	stkdsc = new stack_desc(*sd);
	stack_item a = sd->pop();
	stack_item b = sd->pop();
	sd->push(a);
	sd->push(b);
	return SIM_OK;
}

/** pop - Pop the top item on the stack and forget about it. Only for cat1.
    Action: ... [a] -> ... */

opc_pop::opc_pop(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opcode(apc, code, aci) { }

void opc_pop::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "pop" << endl;
}

opcode::sim_t opc_pop::simulate(stack_desc* sd) {
	if (stkdsc) return SIM_DONE;
	stkdsc = new stack_desc(*sd);
	sd->pop();
	return SIM_OK;
}

/** pop2 - Pop one (cat2) or two (cat1) top item(s) on the stack.
    Action:	... [b] [a] -> ...
		... [A] -> ...   */

opc_pop2::opc_pop2(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opcode(apc, code, aci) { }

void opc_pop2::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "pop2" << endl;
}

/** @todo When the topmost stack item is of category 1 computational type,
    pop2 should pop 2 items. Never seen that on the code but this time
    clever compilers can issue that instruction for forgetting on two
    consecutive functions cat1 return values, the second one being
    without arguments AND static. Eg:
    
    class Foo {
    	int f1(int) { ... };
    	static int f2() { ... };  // Note: Should have no arguments!
    	...
	{
    		f1(1);
    		f2();
    }	}

    Can (but did not seen that on kjc and jikes) be compiled that way:
    	aload this
    	dup
    	iconst_1
    	invokevirtual f1
    	invokestatic Foo.f2
    	pop2
*/

opcode::sim_t opc_pop2::simulate(stack_desc* sd) {
	if (stkdsc) return SIM_DONE;
	stkdsc = new stack_desc(*sd);
	sd->pop();
	return SIM_OK;
}

/* EOF */
