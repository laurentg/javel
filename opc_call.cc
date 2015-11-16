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

#include "opc_call.h"
#include "code_info.h"
#include "class_info.h"
#include "type_info.h"

/** generic invoke */

opc_invoke::opc_invoke(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opcode(apc, code, aci) {
	index = code[apc + 1] << 8 | code[apc + 2];
}

opcode::sim_t opc_invoke::simulate(stack_desc* sd) {
	if (stkdsc) return SIM_DONE;
	stkdsc = new stack_desc(*sd);
	// POP: objectref,[arg1,[arg2...]]
	// stack_item si;
	// si = stkdsc->pop();
	return SIM_OK;
}

/** invokespecial */

opc_invokespecial::opc_invokespecial(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opc_invoke(apc, code, aci) { }

opc_invokespecial::~opc_invokespecial() {
	if (f) delete f;
}

void opc_invokespecial::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "invokespecial "
		<< util::slash2point(codeinfo->get_class_info()
		->get_cp_info(index)->str()) << endl;
}

/** @todo invokespecial and invokevirtual are almost the same, derive
    from a common class. */
opcode::sim_t opc_invokespecial::simulate(stack_desc* sd) {
	if (stkdsc) return SIM_DONE;
	stkdsc = new stack_desc(*sd);
	string descriptor = codeinfo->get_class_info()
		->get_cp_info(index)->descriptor();
	vec_type_t params_t = type_info::parse_args_list(descriptor);
	type_info* return_t = type_info::parse_return_type(descriptor);
	/** Pop as much stack items as arguments to function + 1 (object) */
	f = new stk_func(codeinfo->get_class_info()->get_cp_info(index)->str());
	for (int i = 0; i < params_t.size(); ++i) {
		f->rpush_arg(sd->top());
		sd->pop();
		delete params_t[i]; /** We never needed that anyway... */
	}
	/** Object reference on which the call is made */
	f->set_object(sd->top());
	sd->pop();
	/** If the function has a return value, then we transfert the
	    function f ownership to the stack (it's not a real instruction),
	    otherwise we keep it and use it as an instruction that will be
	    decompiled by the opcode. */
	if (return_t->get_basetype() != type_info::BASETYPE_VOID) {
		stack_item si(f);
		f = 0;
		sd->push(si);
	}
	delete return_t;
	return SIM_OK;
}

void opc_invokespecial::decompile(ostream& os) const {
	if (f) {
		os << "\t\t";
		f->decompile(os);
		os << ";" << endl;
}	}

/** invokevirtual */

opc_invokevirtual::opc_invokevirtual(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opc_invoke(apc, code, aci), f(0) { }

opc_invokevirtual::~opc_invokevirtual() {
	if (f) delete f;
}

void opc_invokevirtual::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "invokevirtual "
		<< util::slash2point(codeinfo->get_class_info()
		->get_cp_info(index)->str()) << endl;
}

opcode::sim_t opc_invokevirtual::simulate(stack_desc* sd) {
	if (stkdsc) return SIM_DONE;
	stkdsc = new stack_desc(*sd);
	string descriptor = codeinfo->get_class_info()
		->get_cp_info(index)->descriptor();
	vec_type_t params_t = type_info::parse_args_list(descriptor);
	type_info* return_t = type_info::parse_return_type(descriptor);
	/** Pop as much stack items as arguments to function + 1 (object) */
	f = new stk_func(codeinfo->get_class_info()->get_cp_info(index)->str());
	for (int i = 0; i < params_t.size(); ++i) {
		f->rpush_arg(sd->top());
		sd->pop();
		delete params_t[i]; /** We never needed that anyway... */
	}
	/** Object reference on which the call is made */
	f->set_object(sd->top());
	sd->pop();
	/** If the function has a return value, then we transfert the
	    function f ownership to the stack (it's not a real instruction),
	    otherwise we keep it and use it as an instruction that will be
	    decompiled by the opcode. */
	if (return_t->get_basetype() != type_info::BASETYPE_VOID) {
		stack_item si(f);
		f = 0;
		sd->push(si);
	}
	delete return_t;
	return SIM_OK;
}

void opc_invokevirtual::decompile(ostream& os) const {
	if (f) {
		os << "\t\t";
		f->decompile(os);
		os << ";" << endl;
}	}

/** invokestatic */

opc_invokestatic::opc_invokestatic(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opc_invoke(apc, code, aci), f(0) { }

opc_invokestatic::~opc_invokestatic() {
	if (f) delete f;
}
			
void opc_invokestatic::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "invokestatic "
		<< util::slash2point(codeinfo->get_class_info()
			->get_cp_info(index)->classname()) << "."
		<< util::slash2point(codeinfo->get_class_info()
			->get_cp_info(index)->str()) << endl;
}

opcode::sim_t opc_invokestatic::simulate(stack_desc* sd) {
	if (stkdsc) return SIM_DONE;
	stkdsc = new stack_desc(*sd);
	string descriptor = codeinfo->get_class_info()->get_cp_info(index)
		->descriptor();
	string classname = codeinfo->get_class_info()->get_cp_info(index)
		->classname();
	vec_type_t params_t = type_info::parse_args_list(descriptor);
	type_info* return_t = type_info::parse_return_type(descriptor);
	/** Pop as much stack items as arguments to function + 0 (no obj) */
	f = new stk_func(codeinfo->get_class_info()->get_cp_info(index)->str());
	f->set_classname(util::slash2point(classname));
	for (int i = 0; i < params_t.size(); ++i) {
		f->rpush_arg(sd->top());
		sd->pop();
		delete params_t[i]; /** We never needed that anyway... */
	}
	if (return_t->get_basetype() != type_info::BASETYPE_VOID) {
		stack_item si(f);
		f = 0;
		sd->push(si);
	}
	delete return_t;
	return SIM_OK;
}

void opc_invokestatic::decompile(ostream& os) const {
	if (f) {
		os << "\t\t";
		f->decompile(os);
		os << ";" << endl;
}	}

/** invokeinterface */

opc_invokeinterface::opc_invokeinterface(const long int apc,
		const vector<U1>& code, const code_info* aci)
		: opc_invoke(apc, code, aci), f(0) {
	count = code[apc + 3];
}

opc_invokeinterface::~opc_invokeinterface() {
	if (f) delete f;
}
			
void opc_invokeinterface::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "invokeinterface "
		<< util::slash2point(codeinfo->get_class_info()
		->get_cp_info(index)->str()) << endl;
}

opcode::sim_t opc_invokeinterface::simulate(stack_desc* sd) {
	if (stkdsc) return SIM_DONE;
	stkdsc = new stack_desc(*sd);
	string descriptor = codeinfo->get_class_info()->get_cp_info(index)
		->descriptor();
	vec_type_t params_t = type_info::parse_args_list(descriptor);
	type_info* return_t = type_info::parse_return_type(descriptor);
	/** Pop as much stack items as arguments to function + 1 (object) */
	f = new stk_func(codeinfo->get_class_info()->get_cp_info(index)->str());
	for (int i = 0; i < params_t.size(); ++i) {
		f->rpush_arg(sd->top());
		sd->pop();
		delete params_t[i]; /** We never needed that anyway... */
	}
	/** Object reference on which the call is made */
	f->set_object(sd->top());
	sd->pop();
	/** Same remark as invokevirtual */
	if (return_t->get_basetype() != type_info::BASETYPE_VOID) {
		stack_item si(f);
		f = 0;
		sd->push(si);
	}
	delete return_t;
	return SIM_OK;
}

void opc_invokeinterface::decompile(ostream& os) const {
	if (f) {
		os << "\t\t";
		f->decompile(os);
		os << ";" << endl;
}	}

/** new */

opc_new::opc_new(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opcode(apc, code, aci) {
	index = code[apc + 1] << 8 | code[apc + 2];
}

void opc_new::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "new "
		<< util::slash2point(codeinfo->get_class_info()
		->get_cp_info(index)->str()) << endl;
}

opcode::sim_t opc_new::simulate(stack_desc* sd) {
	if (stkdsc) return SIM_DONE;
	stkdsc = new stack_desc(*sd);
	stk_new* f = new stk_new(util::slash2point(codeinfo->get_class_info()
		->get_cp_info(index)->str()));
	/** Note: Foo f = new Foo(a, b, c); is translated into:
	    new Foo
	    dup
	    load a
	    load b
	    load c
	    invokespecial <init>
	    astore [f]
	    So we do not have any arguments in a 'new' call. */
#if 0
	for (int i = 0; i < params_t.size(); ++i) {
		f->rpush_arg(sd->top());
		sd->pop();
		delete params_t[i]; /** We never needed that anyway... */
	}
#endif
	stack_item si(f);
	sd->push(si);
	return SIM_OK;
}

/* EOF */
