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

#include "opc_array.h"
#include "code_info.h"
#include "class_info.h"

/** generic aload (iaload, aaload, ...) */

opc_garrload::opc_garrload(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opcode(apc, code, aci) { }

opcode::sim_t opc_garrload::simulate(stack_desc* sd) {
	if (stkdsc) return SIM_DONE;
	stkdsc = new stack_desc(*sd);
	stack_item array, index;
	index = sd->pop();
	array = sd->pop();
	stack_item si(new stk_arref(array, index));
	sd->push(si);
	return SIM_OK;
}

/** iaload */

opc_iaload::opc_iaload(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opc_garrload(apc, code, aci) { }
		
void opc_iaload::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "iaload" << endl;
}

/** laload */

opc_laload::opc_laload(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opc_garrload(apc, code, aci) { }
		
void opc_laload::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "laload" << endl;
}

/** aaload */

/** aaload */

opc_aaload::opc_aaload(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opc_garrload(apc, code, aci) { }

void opc_aaload::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "aaload" << endl;
}

/** arraylength */

opc_alength::opc_alength(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opcode(apc, code, aci) { }

void opc_alength::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "arraylength" << endl;
}

opcode::sim_t opc_alength::simulate(stack_desc* sd) {
	if (stkdsc) return SIM_DONE;
	stkdsc = new stack_desc(*sd);
	sd->push(new stk_arrlen(sd->pop()));
	return SIM_OK;
}

/** newarray */

opc_newarr::opc_newarr(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opcode(apc, code, aci) {
	type = code[apc + 1];
}

void opc_newarr::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "newarray " << str_type() << endl;
}

string opc_newarr::str_type() const {
	switch(type) {
		case 4:  return "boolean";
		case 5:  return "char";
		case 6:  return "float";
		case 7:  return "double";
		case 8:  return "byte";
		case 9:  return "short";
		case 10: return "int";
		case 11: return "long";
		default: return "?";
}	}

opcode::sim_t opc_newarr::simulate(stack_desc* sd) {
	if (stkdsc) return SIM_DONE;
	stkdsc = new stack_desc(*sd);
	stk_newarr* a = new stk_newarr(str_type());
	a->push_size(sd->pop());
	sd->push(a);
	return SIM_OK;
}

/** anewarray */

opc_anewarr::opc_anewarr(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opcode(apc, code, aci) {
	index = code[apc + 1] << 8 | code[apc + 2];
}

void opc_anewarr::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "anewarray " << str_type() << endl;
}

string opc_anewarr::str_type() const {
	return util::slash2point(codeinfo->get_class_info()
		->get_cp_info(index)->str());
}

opcode::sim_t opc_anewarr::simulate(stack_desc* sd) {
	if (stkdsc) return SIM_DONE;
	stkdsc = new stack_desc(*sd);
	stk_newarr* a = new stk_newarr(str_type());
	a->push_size(sd->pop());
	sd->push(a);
	return SIM_OK;
}

/** multianewarray */

opc_manewarr::opc_manewarr(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opcode(apc, code, aci) {
	index = code[apc + 1] << 8 | code[apc + 2];
	dimension = code[apc + 3];
}

void opc_manewarr::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "multianewarray "
		<< str_type() << " " << dimension << endl;
}

string opc_manewarr::str_type() const {
	type_info ti(util::slash2point(codeinfo
		->get_class_info()->get_cp_info(index)->str()));
	return ti.str_type();
}

opcode::sim_t opc_manewarr::simulate(stack_desc* sd) {
	if (stkdsc) return SIM_DONE;
	stkdsc = new stack_desc(*sd);
	stk_newarr* a = new stk_newarr(str_type());
	for (int i = 0; i < dimension; ++i) {
		a->rpush_size(sd->pop());
	}
	sd->push(a);
	return SIM_OK;
}

/* EOF */
