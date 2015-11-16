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

#include "opc_poush.h"
#include "code_info.h"
#include "class_info.h"

/** generic iload */

opc_giload::opc_giload(const long apc, const vector<U1>& code,
		const code_info* aci)
		: opcode(apc, code, aci), index(0) { }
		
void opc_giload::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "iload ["
		<< codeinfo->get_localname(startpc + length(), index)
		<< "]" << endl;
}

opcode::sim_t opc_giload::simulate(stack_desc* sd) {
	if (stkdsc) return SIM_DONE;
	stkdsc = new stack_desc(*sd);
	stack_item si(new stk_local_var(codeinfo->get_localname(
		startpc + length(), index)));
	sd->push(si);
	return SIM_OK;
}

/** iload */
	
opc_iload::opc_iload(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opc_giload(apc, code, aci) {
	index = code[apc + 1];
}

/** iload_<n> */

opc_iload_n::opc_iload_n(const long int apc, const vector<U1>& code,
		const code_info* aci, const int n)
		: opc_giload(apc, code, aci) {
	index = n;
}

/** generic lload */

opc_glload::opc_glload(const long apc, const vector<U1>& code,
		const code_info* aci)
		: opc_giload(apc, code, aci) { }
		
void opc_glload::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "lload ["
		<< codeinfo->get_localname(startpc + length(), index)
		<< "]" << endl;
}

/** lload_<n> */

opc_lload_n::opc_lload_n(const long int apc, const vector<U1>& code,
		const code_info* aci, const int n)
		: opc_glload(apc, code, aci) {
	index = n;
}

/** lload */
	
opc_lload::opc_lload(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opc_glload(apc, code, aci) {
	index = code[apc + 1];
}

/** generic aload */

opc_gaload::opc_gaload(const long apc, const vector<U1>& code,
		const code_info* aci)
		: opcode(apc, code, aci), index(0) { }
		
void opc_gaload::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "aload ["
		<< codeinfo->get_localname(startpc + length(), index)
		<< "]" << endl;
}

opcode::sim_t opc_gaload::simulate(stack_desc* sd) {
	if (stkdsc) return SIM_DONE;
	stkdsc = new stack_desc(*sd);
	stack_item si(new stk_local_var(codeinfo->get_localname(
		startpc + length(), index)));
	sd->push(si);
	return SIM_OK;
}

/** aload */
		
opc_aload::opc_aload(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opc_gaload(apc, code, aci) {
	index = code[apc + 1];
}

/** aload_<n> */

opc_aload_n::opc_aload_n(const long int apc, const vector<U1>& code,
		const code_info* aci, const int n)
		: opc_gaload(apc, code, aci) {
	index = n;
}

/** aconst_null */

opc_aconst_null::opc_aconst_null(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opcode(apc, code, aci) { }

void opc_aconst_null::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "aconst_null" << endl;
}

opcode::sim_t opc_aconst_null::simulate(stack_desc* sd) {
	if (stkdsc) return SIM_DONE;
	stkdsc = new stack_desc(*sd);
	stack_item si(new stk_const("null"));
	sd->push(si);
	return SIM_OK;
}

/** generic ipush (iconst_<n>, bipush, sipush, lconst_<n>) */

opc_gpush::opc_gpush(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opcode(apc, code, aci), constant(0) { }

void opc_gpush::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "ipush " << constant << endl;
}

opcode::sim_t opc_gpush::simulate(stack_desc* sd) {
	if (stkdsc) return SIM_DONE;
	stkdsc = new stack_desc(*sd);
	stack_item si(new stk_int_const(constant));
	sd->push(si);
	return SIM_OK;
}

/** iconst_<n>
    Action: push int constant <n> onto the stack. */

opc_iconst_n::opc_iconst_n(const long int apc, const vector<U1>& code,
		const code_info* aci, const int n)
		: opc_gpush(apc, code, aci) {
	constant = n;
}

/** lconst_<n>
    Action: push long constant <n> onto the stack. */

opc_lconst_n::opc_lconst_n(const long int apc, const vector<U1>& code,
		const code_info* aci, const int n)
		: opc_gpush(apc, code, aci) {
	constant = n;
}

void opc_lconst_n::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "lpush " << constant << endl;
}

/** bipush */

opc_bipush::opc_bipush(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opc_gpush(apc, code, aci) {
	signed char temp = code[apc + 1];
	constant = temp;
}

/** sipush */

opc_sipush::opc_sipush(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opc_gpush(apc, code, aci) {
	signed short temp = code[apc + 1] << 8 | code[apc + 2];
	constant = temp;
}

/** generic getfield & getstatic */

opc_ggetfield::opc_ggetfield(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opcode(apc, code, aci) {
	index = code[apc + 1] << 8 | code[apc + 2];
}

/** getfield */

opc_getfield::opc_getfield(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opc_ggetfield(apc, code, aci) { }

void opc_getfield::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "getfield "
		<< util::slash2point(codeinfo->get_class_info()
		->get_cp_info(index)->str()) << endl;
}

opcode::sim_t opc_getfield::simulate(stack_desc* sd) {
	if (stkdsc) return SIM_DONE;
	stkdsc = new stack_desc(*sd);
	string fieldname = util::slash2point(codeinfo->get_class_info()
		->get_cp_info(index)->str());
	stack_item si(new stk_field(sd->pop(), fieldname));
	sd->push(si);
	return SIM_OK;
}

/** getstatic */

opc_getstatic::opc_getstatic(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opc_ggetfield(apc, code, aci) { }

void opc_getstatic::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "getstatic "
		<< util::slash2point(codeinfo->get_class_info()
		->get_cp_info(index)->str()) << endl;
}

opcode::sim_t opc_getstatic::simulate(stack_desc* sd) {
	if (stkdsc) return SIM_DONE;
	stkdsc = new stack_desc(*sd);
	string classname = codeinfo->get_class_info()
		->get_cp_info(index)->classname();
	string fieldname = util::slash2point(codeinfo->get_class_info()
		->get_cp_info(index)->str());
	stack_item si(new stk_staticfield(classname, fieldname));
	sd->push(si);
	return SIM_OK;
}

/** generic putfield & putstatic */

opc_gputfield::opc_gputfield(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opcode(apc, code, aci) {
	index = code[apc + 1] << 8 | code[apc + 2];
}

/** putfield */

opc_putfield::opc_putfield(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opc_gputfield(apc, code, aci) { }

void opc_putfield::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "putfield "
		<< util::slash2point(codeinfo->get_class_info()
		->get_cp_info(index)->str()) << endl;
}

void opc_putfield::decompile(ostream& os) const {
	os << "\t\t";
	stkdsc->top(1)->decompile(os);
	os << "." << util::slash2point(codeinfo->get_class_info()
		->get_cp_info(index)->str()) << " = ";
	stkdsc->top()->decompile(os);
	os << ";" << endl;
}

opcode::sim_t opc_putfield::simulate(stack_desc* sd) {
	if (stkdsc) return SIM_DONE;
	stkdsc = new stack_desc(*sd);
	sd->pop();
	sd->pop();
	return SIM_OK;
}

/** putstatic */

opc_putstatic::opc_putstatic(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opc_gputfield(apc, code, aci) { }

void opc_putstatic::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "putstatic "
		<< util::slash2point(codeinfo->get_class_info()
		->get_cp_info(index)->str()) << endl;
}

void opc_putstatic::decompile(ostream& os) const {
	string classname = codeinfo->get_class_info()
		->get_cp_info(index)->classname();
	os << "\t\t";
	os << classname << "." << util::slash2point(codeinfo->get_class_info()
		->get_cp_info(index)->str()) << " = ";
	stkdsc->top()->decompile(os);
	os << ";" << endl;
}

opcode::sim_t opc_putstatic::simulate(stack_desc* sd) {
	if (stkdsc) return SIM_DONE;
	stkdsc = new stack_desc(*sd);
	sd->pop();
	return SIM_OK;
}

/** generic istore (istore & istore_<n> */

opc_gistore::opc_gistore(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opcode(apc, code, aci), index(0) { };

void opc_gistore::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "istore ["
		<< codeinfo->get_localname(startpc + length(), index)
		<< "]" << endl;
}

void opc_gistore::decompile(ostream& os) const {
	os << "\t\t" << codeinfo->get_localname(startpc + length(), index)
		<< " = ";
	stkdsc->top()->decompile(os);
	os << ";" << endl;
}

opcode::sim_t opc_gistore::simulate(stack_desc* sd) {
	if (stkdsc) return SIM_DONE;
	stkdsc = new stack_desc(*sd);
	stack_item si;
	si = sd->pop();
	return SIM_OK;
}

/** istore */

opc_istore::opc_istore(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opc_gistore(apc, code, aci) {
	index = code[apc + 1];
}

/** istore_<n> */

opc_istore_n::opc_istore_n(const long int apc, const vector<U1>& code,
		const code_info* aci, const int n)
		: opc_gistore(apc, code, aci) {
	index = n;
}

/** generic lstore (lstore & lstore_<n> */

opc_glstore::opc_glstore(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opc_gistore(apc, code, aci) { };

void opc_glstore::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "lstore ["
		<< codeinfo->get_localname(startpc + length(), index)
		<< "]" << endl;
}

/** lstore */

opc_lstore::opc_lstore(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opc_glstore(apc, code, aci) {
	index = code[apc + 1];
}

/** lstore_<n> */

opc_lstore_n::opc_lstore_n(const long int apc, const vector<U1>& code,
		const code_info* aci, const int n)
		: opc_glstore(apc, code, aci) {
	index = n;
}


/** generic astore (astore & astore_<n>) */

opc_gastore::opc_gastore(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opcode(apc, code, aci), index(0) { };

void opc_gastore::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "astore ["
		<< codeinfo->get_localname(startpc + length(), index)
		<< "]" << endl;
}

void opc_gastore::decompile(ostream& os) const {
	os << "\t\t" << codeinfo->get_localname(startpc + length(), index)
		<< " = ";
	stkdsc->top()->decompile(os);
	os << ";" << endl;
}

opcode::sim_t opc_gastore::simulate(stack_desc* sd) {
	if (stkdsc) return SIM_DONE;
	stkdsc = new stack_desc(*sd);
	stack_item si;
	si = sd->pop();
	return SIM_OK;
}

/** astore */

opc_astore::opc_astore(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opc_gastore(apc, code, aci) {
	index = code[apc + 1];
}

/** astore_<n> */

opc_astore_n::opc_astore_n(const long int apc, const vector<U1>& code,
		const code_info* aci, const int n)
		: opc_gastore(apc, code, aci) {
	index = n;
}

/** generic ldc (ldc, ldc_w, ldc2_w) */

opc_gldc::opc_gldc(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opcode(apc, code, aci), index(0) { }

opcode::sim_t opc_gldc::simulate(stack_desc* sd) {
	if (stkdsc) return SIM_DONE;
	stkdsc = new stack_desc(*sd);
	stack_item si(new stk_const(util::slash2point(codeinfo
		->get_class_info()->get_cp_info(index)->str())));
	sd->push(si);
	return SIM_OK;
}

/** ldc */

opc_ldc::opc_ldc(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opc_gldc(apc, code, aci) {
	index = code[apc + 1];
}

void opc_ldc::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "ldc "
		<< util::slash2point(codeinfo->get_class_info()
		->get_cp_info(index)->str()) << endl;
}

/** ldc_w */

opc_ldc_w::opc_ldc_w(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opc_gldc(apc, code, aci) {
	index = code[apc + 1] << 8 | code[apc + 2];
}

void opc_ldc_w::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "ldc_w "
		<< util::slash2point(codeinfo->get_class_info()
		->get_cp_info(index)->str()) << endl;
}

/** ldc2_w */

opc_ldc2_w::opc_ldc2_w(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opc_gldc(apc, code, aci) {
	index = code[apc + 1] << 8 | code[apc + 2];
}

void opc_ldc2_w::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "ldc2_w "
		<< util::slash2point(codeinfo->get_class_info()
		->get_cp_info(index)->str()) << endl;
}

/* EOF */
