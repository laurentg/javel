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

#include "code_info.h"
#include "class_info.h"

#if 0
typedef struct opcode_s {
	char* name;
	int operands;
} opcode_t;

const unsigned int OPCODE_MAX = 202;

opcode_t opcodes[OPCODE_MAX] = {
 { "nop",		0 },	/* 0   */
 { "aconst_null",	0 },	/* 1   */
 { "iconst_m1",		0 },	/* 2   */
 { "iconst_0",		0 },	/* 3   */
 { "iconst_1",		0 },	/* 4   */
 { "iconst_2",		0 },	/* 5   */
 { "iconst_3",		0 },	/* 6   */
 { "iconst_4",		0 },	/* 7   */
 { "iconst_5",		0 },	/* 8   */
 { "lconst_0",		0 },	/* 9   */
 { "lconst_1",		0 },	/* 10  */
 { "fconst_0",		0 },	/* 11  */
 { "fconst_1",		0 },	/* 12  */
 { "fconst_2",		0 },	/* 13  */
 { "dconst_0",		0 },	/* 14  */
 { "dconst_1",		0 },	/* 15  */
 { "bipush",		1 },	/* .   */
 { "sipush",		2 },	/* .   */
 { "ldc",		1 },	/* .   */
 { "ldc_w",		2 },	/* .   */
 { "ldc2_w",		2 },	/* .   */
 { "iload",		1 },	/* .   */
 { "lload",		1 },	/* .   */
 { "fload",		1 },	/* .   */
 { "dload",		1 },	/* .   */
 { "aload",		1 },	/* .   */
 { "iload_0",		0 },	/* .   */
 { "iload_1",		0 },	/* .   */
 { "iload_2",		0 },	/* .   */
 { "iload_3",		0 },	/* .   */
 { "lload_0",		0 },	/* .   */
 { "lload_1",		0 },	/* .   */
 { "lload_2",		0 },	/* .   */
 { "lload_3",		0 },	/* .   */
 { "fload_0",		0 },	/* .   */
 { "fload_1",		0 },	/* .   */
 { "fload_2",		0 },	/* .   */
 { "fload_3",		0 },	/* .   */
 { "dload_0",		0 },	/* .   */
 { "dload_1",		0 },	/* .   */
 { "dload_2",		0 },	/* .   */
 { "dload_3",		0 },	/* .   */
 { "aload_0",		0 },	/* .   */
 { "aload_1",		0 },	/* .   */
 { "aload_2",		0 },	/* .   */
 { "aload_3",		0 },	/* .   */
 { "iaload",		0 },	/* .   */
 { "laload",		0 },	/* .   */
 { "faload",		0 },	/* .   */
 { "daload",		0 },	/* .   */
 { "aaload",		0 },	/* .   */
 { "baload",		0 },	/* .   */
 { "caload",		0 },	/* .   */
 { "saload",		0 },	/* .   */
 { "istore",		1 },	/* .   */
 { "lstore",		1 },	/* .   */
 { "fstore",		1 },	/* .   */
 { "dstore",		1 },	/* .   */
 { "astore",		1 },	/* .   */
 { "istore_0",		0 },	/* .   */
 { "istore_1",		0 },	/* .   */
 { "istore_2",		0 },	/* .   */
 { "istore_3",		0 },	/* .   */
 { "lstore_0",		0 },	/* .   */
 { "lstore_1",		0 },	/* .   */
 { "lstore_2",		0 },	/* .   */
 { "lstore_3",		0 },	/* .   */
 { "fstore_0",		0 },	/* .   */
 { "fstore_1",		0 },	/* .   */
 { "fstore_2",		0 },	/* .   */
 { "fstore_3",		0 },	/* .   */
 { "dstore_0",		0 },	/* .   */
 { "dstore_1",		0 },	/* .   */
 { "dstore_2",		0 },	/* .   */
 { "dstore_3",		0 },	/* .   */
 { "astore_0",		0 },	/* .   */
 { "astore_1",		0 },	/* .   */
 { "astore_2",		0 },	/* .   */
 { "astore_3",		0 },	/* .   */
 { "iastore",		0 },	/* .   */
 { "lastore",		0 },	/* .   */
 { "fastore",		0 },	/* .   */
 { "dastore",		0 },	/* .   */
 { "aastore",		0 },	/* .   */
 { "bastore",		0 },	/* .   */
 { "castore",		0 },	/* .   */
 { "sastore",		0 },	/* .   */
 { "pop",		0 },	/* .   */
 { "pop2",		0 },	/* .   */
 { "dup",		0 },	/* .   */
 { "dup_x1",		0 },	/* .   */
 { "dup_x2",		0 },	/* .   */
 { "dup2",		0 },	/* .   */
 { "dup2_x1",		0 },	/* .   */
 { "dup2_x2",		0 },	/* .   */
 { "swap",		0 },	/* .   */
 { "iadd",		0 },	/* .   */
 { "ladd",		0 },	/* .   */
 { "fadd",		0 },	/* .   */
 { "dadd",		0 },	/* .   */
 { "isub",		0 },	/* .   */
 { "lsub",		0 },	/* .   */
 { "fsub",		0 },	/* .   */
 { "dsub",		0 },	/* .   */
 { "imul",		0 },	/* .   */
 { "lmul",		0 },	/* .   */
 { "fmul",		0 },	/* .   */
 { "dmul",		0 },	/* .   */
 { "idiv",		0 },	/* .   */
 { "ldiv",		0 },	/* .   */
 { "fdiv",		0 },	/* .   */
 { "ddiv",		0 },	/* .   */
 { "irem",		0 },	/* .   */
 { "lrem",		0 },	/* .   */
 { "frem",		0 },	/* .   */
 { "drem",		0 },	/* .   */
 { "ineg",		0 },	/* .   */
 { "lneg",		0 },	/* .   */
 { "fneg",		0 },	/* .   */
 { "dneg",		0 },	/* .   */
 { "ishl",		0 },	/* .   */
 { "lshl",		0 },	/* .   */
 { "ishr",		0 },	/* .   */
 { "lshr",		0 },	/* .   */
 { "iushr",		0 },	/* .   */
 { "lushr",		0 },	/* .   */
 { "iand",		0 },	/* .   */
 { "land",		0 },	/* .   */
 { "ior",		0 },	/* .   */
 { "lor",		0 },	/* .   */
 { "ixor",		0 },	/* .   */
 { "lxor",		0 },	/* .   */
 { "iinc",		2 },	/* .   */
 { "i2l",		0 },	/* .   */
 { "i2f",		0 },	/* .   */
 { "i2d",		0 },	/* .   */
 { "l2i",		0 },	/* .   */
 { "l2f",		0 },	/* .   */
 { "l2d",		0 },	/* .   */
 { "f2i",		0 },	/* .   */
 { "f2l",		0 },	/* .   */
 { "f2d",		0 },	/* .   */
 { "d2i",		0 },	/* .   */
 { "d2l",		0 },	/* .   */
 { "d2f",		0 },	/* .   */
 { "i2b",		0 },	/* .   */
 { "i2c",		0 },	/* .   */
 { "i2s",		0 },	/* .   */
 { "lcmp",		0 },	/* .   */
 { "fcmpl",		0 },	/* .   */
 { "fcmpg",		0 },	/* .   */
 { "dcmpl",		0 },	/* .   */
 { "dcmpg",		0 },	/* .   */
 { "ifeq",		2 },	/* .   */
 { "ifne",		2 },	/* .   */
 { "iflt",		2 },	/* .   */
 { "ifle",		2 },	/* .   */
 { "ifgt",		2 },	/* .   */
 { "ifge",		2 },	/* .   */
 { "if_icmpeq",		2 },	/* .   */
 { "if_icmpne",		2 },	/* .   */
 { "if_icmplt",		2 },	/* .   */
 { "if_icmpge",		2 },	/* .   */
 { "if_icmpgt",		2 },	/* .   */
 { "if_icmple",		2 },	/* .   */
 { "if_acmpeq",		2 },	/* .   */
 { "if_acmpne",		2 },	/* .   */
 { "goto",		2 },	/* .   */
 { "jsr",		2 },	/* .   */
 { "ret",		1 },	/* .   */
 { "tableswitch",	-1 },	/* .   */
 { "lookupswitch",	-1 },	/* .   */
 { "ireturn",		0 },	/* .   */
 { "lreturn",		0 },	/* .   */
 { "freturn",		0 },	/* .   */
 { "dreturn",		0 },	/* .   */
 { "areturn",		0 },	/* .   */
 { "return",		0 },	/* .   */
 { "getstatic",		2 },	/* .   */
 { "putstatic",		2 },	/* .   */
 { "getfield",		2 },	/* .   */
 { "putfield",		2 },	/* .   */
 { "invokevirtual",	2 },	/* .   */
 { "invokespecial",	2 },	/* .   */
 { "invokestatic",	2 },	/* .   */
 { "invokeinterface",	4 },	/* .   */
 { "???",		0 },	/* .   */
 { "new",		2 },	/* .   */
 { "newarray",		1 },	/* .   */
 { "anewarray",		2 },	/* .   */
 { "arraylength",	0 },	/* .   */
 { "athrow",		0 },	/* .   */
 { "checkcast",		2 },	/* .   */
 { "instanceof",	2 },	/* .   */
 { "monitorenter",	0 },	/* .   */
 { "monitorexit",	0 },	/* .   */
 { "wide",		-1 },	/* .   */
 { "multianewarray",	3 },	/* .   */
 { "ifnull",		2 },	/* .   */
 { "ifnonnull",		2 },	/* .   */
 { "goto_w",		4 },	/* .   */
 { "jsr_w",		4 }};	/* .   */
#endif

code_info::code_info(istream& is, const class_info* _ci)
		: attribute_info(_ci), method(0) {
	length = util::read_U4(is);
	max_stack = util::read_U2(is);
	max_locals = util::read_U2(is);
	U4 code_length = util::read_U4(is);
	for(U4 i = 0; i < code_length; i++)
		code.push_back(util::read_U1(is));
	U2 excp_num = util::read_U2(is);
	for(U2 i = 0; i < excp_num; i++) {
		exception_t e;
		e.start_pc = util::read_U2(is);
		e.end_pc = util::read_U2(is);
		e.handler_pc = util::read_U2(is);
		U2 catch_index = util::read_U2(is);
		if (catch_index)
			e.catch_type = ci->get_cp_info(catch_index)->str();
		else
			e.catch_type = "";
		exceptions_table.push_back(e);
	}
	attributes = new attributes_set(is, ci);
}

void code_info::check_excp(
		const long int old_pc,
		const long int new_pc, ostream& os) const {
	for (vector<exception_t>::const_iterator p = exceptions_table.begin();
			p != exceptions_table.end(); p++) {
		/** Note: adress ranges are inclusive for start_pc,
		    exclusive for end_pc: [start_pc, end_pc) */
		if (old_pc < p->start_pc && new_pc >= p->start_pc)
			os << "\t\t\t" << "start_excp_hnd(" <<
				p->handler_pc << ", " << util::slash2point
					(p->catch_type) << ")" << endl;
		if (old_pc <= p->end_pc && new_pc > p->end_pc)
			os << "\t\t\t" << "end_excp_hnd(" <<
				p->handler_pc << ", " << util::slash2point
					(p->catch_type) << ")" << endl;
	}
}

void code_info::check_line(
		const long int old_pc,
		const long int new_pc, ostream& os) const {
	linenumtbl_info* lnti = attributes->get_linenumtbl();
	if (!lnti)
		return;
	lnti->check_line(old_pc, new_pc, os);
}

string code_info::get_localname(
		const long int pc, const int varindex) const {
	localvar_info* lvi = attributes->get_localvar();
	if (lvi) {
		string ret = lvi->lookup(pc, varindex);
		if (ret.compare("")) return ret;
	}
	if (method && !method->isstatic() && varindex == 0) return "this";
	ostringstream oss;
	oss << "v" << varindex;
	return oss.str();
}

string code_info::get_paramname(const int varindex) const {
	localvar_info* lvi = attributes->get_localvar();
	if (lvi) {
		string ret = lvi->lookup(0, varindex);
		if (ret.compare("")) return ret;
	}
	if (method && !method->isstatic() && varindex == 0) return "this";
	ostringstream oss;
	oss << "v" << varindex;
	return oss.str();
}

opcode* code_info::getopcode(const int pc) {

	opcset_t::iterator p = opcodes.find(pc);
	if (p == opcodes.end()) return (opcode*)0;
	return p->second;
}
#if 0
void code_info::simulate(const int pc, stack_desc* astack) {

	opcode::sim_t ret;
	int cpc = pc;
	while (cpc != -1) {
		//cerr << "Simulating pc=" << cpc << endl;
		opcode* opc = getopcode(cpc);
		if (!opc) return;
		ret = opc->simulate(astack);
		if (ret == opcode::SIM_DONE) return;
		int gotopc = opc->gotopc();
		/** @todo We can optimize here by swapping gotopc and nextpc
		    if nextpc is -1 and gotopc is not (here, NOT in opcode) */
		if (gotopc != -1) {
			getopcode(gotopc)->target(true);
			simulate(gotopc, astack);
		}
		cpc = opc->nextpc();
	}
}
#endif

void code_info::simulate(const int pc, stack_desc* astack) {

	opcode::sim_t ret;
	int cpc = pc;
	while (cpc != -1) {
		opcode* opc = getopcode(cpc);
		if (!opc) return;
		int gotopc = opc->gotopc();
		if (gotopc != -1) {
			stack_desc* newstack = new stack_desc(*astack);
			ret = opc->simulate_goto(newstack);
			if (ret == opcode::SIM_DONE) return;
			getopcode(gotopc)->target(true);
			simulate(gotopc, newstack);
			delete newstack;
		}
		ret = opc->simulate(astack);
		// if (ret == opcode::SIM_DONE) return;
		cpc = opc->nextpc();
	}
}

void code_info::simulate() {

	/** Simulate normal code flow, include finally blocks, starting at 0 */
	stack_desc* astack = new stack_desc();
	simulate(0, astack);
	delete astack;

	/** Simulate catch blocks from each handler pc in the exception tbl */
	for (vector<exception_t>::const_iterator p = exceptions_table.begin();
			p != exceptions_table.end(); p++) {
		stack_desc* astack = new stack_desc();
		astack->push(new stk_const("e"));
		simulate(p->handler_pc, astack);
		delete astack;
	}
}

void code_info::disassemble(const format_spec& fs, ostream& os) const {
	if (fs.stacklocals()) {
		os << "\t\t" << "// Code  : " << code.size() << endl;
		os << "\t\t" << "// Stack : " << max_stack << endl;
		os << "\t\t" << "// Locals: " << max_locals << endl;
	}
	if (!fs.bytecode()) return;

	for (opcset_t::const_iterator p = opcodes.begin();
			p != opcodes.end(); ++p) {
		delete p->second;
	}
	opcodes.clear();

	long int pc = 0;
	while (pc < code.size()) {
		opcode* opc = opcode::opcode_factory(pc, code, this);
		if (!opc) break;
		opcodes[pc] = opc;
		pc += opc->length();
	}

	((code_info*)this)->simulate();

	/** We assume here that an iterator on a map created
	    with indexes in growing order will iterate on the
	    same order. */
	for (opcset_t::const_iterator p = opcodes.begin();
			p != opcodes.end(); ++p) {
		if (p->second->get_stack())
			p->second->get_stack()->disassemble(os);
		else	os << "\t\t\t" << "-" << endl;
		p->second->disassemble(os);
	}
	os << "\t\t" << "-----------------" << endl;
	for (opcset_t::const_iterator p = opcodes.begin();
			p != opcodes.end(); ++p) {
		if (p->second->target())
			os << "\t\t" << "label_" << p->first << ":" << endl;
		p->second->decompile(os);
	}
}

/** @todo This should be implemented as a vector of opcode objects,
    which implements all abstract methods such as "disassemble()",
    "loadfromstream()"... Perhaps as one or several class template(s).
    @todo Implement the tableswitch and lookupswitch opcode. */
#if 0
void code_info::disassemble(const format_spec& fs, ostream& os) const {
	if (fs.stacklocals()) {
		os << "\t\t" << "// Code size:  " <<
			code.size() << " bytes" << endl;
		os << "\t\t" << "// Stack size: " <<
			max_stack << " bytes" << endl;
		os << "\t\t" << "// Locals:     " <<
			max_locals << endl;
	}
	if (!fs.bytecode())
		return;
	long int old_i, i;
	for (old_i = -1, i = 0; i < code.size(); i++) {
		check_excp(old_i, i, os);
		if (fs.linenumber())
			check_line(old_i, i, os);
		os << "\t\t";
		U1 wopcode, opcode = code[i];
		os << i << "\t" << opcodes[opcode].name;
		int ndx, cst, oper_count = opcodes[opcode].operands;
		signed short int offset; /* goto */
		signed long int loffset; /* goto_w */
		signed long pad, dfltoffset, npairs, key; /* lookup_switch */
		signed long low, high;
		long int opers = 0;
		switch (oper_count) {
			case 1: opers = code[i + 1]; break;
			case 2: opers = (code[i + 1] << 8) | code[i + 2]; break;
			case 4: opers = (code[i + 1] << 24) | 
					(code[i + 2] << 16) |
					(code[i + 3] << 8) | 
					(code[i + 4]); break;
		}
		switch (opcode) {
			case 18 : /* ldc */
			case 19 : /* ldc_w */
			case 20 : /* ldc2_w */
			case 178: /* getstatic */
			case 179: /* putstatic */
			case 180: /* getfield */
			case 181: /* putfield */
			case 182: /* invokevirtual */
			case 183: /* invokespecial */
			case 184: /* invoke static */
			case 187: /* new */
			case 189: /* anewarray */
			case 192: /* checkcast */
			case 193: /* instanceof */
				if (opers)
					os << " " << util::slash2point
						(ci->get_cp_info(opers)->str());
				break;
			case 185: /* invokeinterface */
			case 197: /* multianewarray */
				os << " " << (int)code[i + 3];
				ndx = (code[i + 1] << 8) | code[i + 2];
				if (ndx)
					os << " " << util::slash2point
						(ci->get_cp_info(ndx)->str());
				break;
			case 153: case 154: case 155: case 156:
			case 157: case 158: /* if<cond> */
			case 159: case 160: case 161: case 162:
			case 163: case 164: /* if_icmp<cond> */
			case 165: case 166: /* if_acmp<cond> */
			case 198: case 199: /* if<non>null */
			case 167: /* goto */
				offset = (code[i + 1] << 8) | code[i + 2];
				os << " " << i + offset;
				break;
			case 200: /* goto_w */
				loffset = (code[i + 1] << 24) |
					(code[i + 2] << 16) |
					(code[i + 3] << 8) | code[i + 4];
				os << " " << i + loffset;
				break;
			case 170: /* tableswitch */
				pad = 4 - (i % 4);
				dfltoffset = (code[i + pad] << 24) |
					(code[i + pad + 1] << 16) |
					(code[i + pad + 2] << 8) |
					(code[i + pad + 3]);
				low = (code[i + pad + 4] << 24) |
					(code[i + pad + 5] << 16) |
					(code[i + pad + 6] << 8) |
					(code[i + pad + 7]);
				high = (code[i + pad + 8] << 24) |
					(code[i + pad + 9] << 16) |
					(code[i + pad + 10] << 8) |
					(code[i + pad + 11]);
				os << endl;
				for (int j = 0; j < high - low + 1; ++j) {
					loffset =
					(code[i + j * 4 + pad + 12] << 24) |
					(code[i + j * 4 + pad + 13] << 16) |
					(code[i + j * 4 + pad + 14] << 8) |
					(code[i + j * 4 + pad + 15]);
					os << "\t\t\t" << low + j << ":\t"
					<< i + loffset << endl;
				}
				os << "\t\t\tdflt:\t"
				<< i + dfltoffset;
				oper_count = pad + (high - low + 1) * 4 + 11;
				break;
			case 171: /* lookupswitch */
				pad = 4 - (i % 4);
				dfltoffset = (code[i + pad] << 24) |
					(code[i + pad + 1] << 16) |
					(code[i + pad + 2] << 8) |
					(code[i + pad + 3]);
				npairs = (code[i + pad + 4] << 24) |
					(code[i + pad + 5] << 16) |
					(code[i + pad + 6] << 8) |
					(code[i + pad + 7]);
				os << endl;
				for (int j = 0; j < npairs; ++j) {
					key =
					(code[i + j * 8 + pad + 8] << 24) |
					(code[i + j * 8 + pad + 9] << 16) |
					(code[i + j * 8 + pad + 10] << 8) |
					(code[i + j * 8 + pad + 11]);
					loffset =
					(code[i + j * 8 + pad + 12] << 24) |
					(code[i + j * 8 + pad + 13] << 16) |
					(code[i + j * 8 + pad + 14] << 8) |
					(code[i + j * 8 + pad + 15]);
					os << "\t\t\t" << key << ":\t"
					<< i + loffset << endl;
				}
				os << "\t\t\tdflt:\t"
				<< i + dfltoffset;
				oper_count = pad + npairs * 8 + 7;
				break;
			case 196: /* wide */
				wopcode = code[i + 1];
				os << " " << opcodes[wopcode].name;
				switch (wopcode) {
					case 132: /* iinc */
						ndx = (code[i + 2] << 8)
							| code[i + 3];
						cst = (code[i + 4] << 8)
							| code[i + 5];
						os << " ["
						<< get_localname(i, ndx)
						<< "] " << cst;
						break;
					case 169: /* ret */
						ndx = (code[i + 2] << 8) |
							code[i + 3];
						os << " ["
						<< get_localname(i, ndx)
						<< "]";
					default: /* <x>load, <x>store */
						ndx = (code[i + 2] << 8) |
							code[i + 3];
						os << " ["
						<< get_localname(i, ndx)
						<< "]";
						break;
				}
				break;
			case 132: /* iinc */
				ndx = code[i + 1];
				cst = code[i + 2];
				os << " [" << get_localname(i, ndx)
					<< "] " << cst;
				break;
			case 21: case 22: case 23:
			case 24: case 25: /* <x>load */
			case 54: case 55: case 56:
			case 57: case 58: /* <x>store */
			case 169: /* ret */
				os << " [" << get_localname(i, opers) << "]";
				break;
			case 26: case 27: case 28: case 29: /* iload_<n> */
				os << " [" << get_localname(i, opcode - 26)
					<< "]";
				break;
			case 30: case 31: case 32: case 33: /* lload_<n> */
				os << " [" << get_localname(i, opcode - 30)
					<< "]";
				break;
			case 34: case 35: case 36: case 37: /* fload_<n> */
				os << " [" << get_localname(i, opcode - 34)
					<< "]";
				break;
			case 38: case 39: case 40: case 41: /* dload_<n> */
				os << " [" << get_localname(i, opcode - 38)
					<< "]";
				break;
			case 42: case 43: case 44: case 45: /* aload_<n> */
				os << " [" << get_localname(i, opcode - 42)
					<< "]";
				break;
			case 59: case 60: case 61: case 62: /* istore_<n> */
				os << " [" << get_localname(i, opcode - 59)
					<< "]";
				break;
			case 63: case 64: case 65: case 66: /* lstore_<n> */
				os << " [" << get_localname(i, opcode - 63)
					<< "]";
				break;
			case 67: case 68: case 69: case 70: /* fstore_<n> */
				os << " [" << get_localname(i, opcode - 67)
					<< "]";
				break;
			case 71: case 72: case 73: case 74: /* dstore_<n> */
				os << " [" << get_localname(i, opcode - 71)
					<< "]";
				break;
			case 75: case 76: case 77: case 78: /* astore_<n> */	
				os << " [" << get_localname(i, opcode - 75)
					<< "]";
				break;
			case 16: /* bipush */
				ndx = (int)((signed char)code[i + 1]);
				os << " " << ndx;
				break;
			default:
				if (oper_count)
					os << " " << opers;
				break;
		}
		os << endl;
		old_i = i;
		i += oper_count;
	}
	check_excp(old_i, i, os);
}
#endif

void code_info::cleanup() {
	delete attributes;
}

