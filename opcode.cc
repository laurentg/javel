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

#include "opcode.h"
#include "opc_ret.h"
#include "opc_call.h"
#include "opc_binop.h"
#include "opc_poush.h"
#include "opc_array.h"
#include "opc_jmp.h"
#include "opc_dup.h"
#include "opc_misc.h"
#include "code_info.h"
#include "class_info.h"

/** opcode abstract base */

opcode::opcode(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: startpc(apc), codeinfo(aci), stkdsc(0), istarget(false) {
}

opcode::~opcode() {
	if (stkdsc) delete stkdsc;
}

opcode::sim_t opcode::simulate(stack_desc* sd) {
	if (stkdsc) return SIM_DONE;
	stkdsc = new stack_desc(*sd);
	return SIM_OK;
}

/** By default, stack simulation is identical for the next instruction
    and the goto instruction. But this can be overriden by jsr which is
    not symetrical regarding stack. */
opcode::sim_t opcode::simulate_goto(stack_desc* sd) {
	return simulate(sd);
}

opcode* opcode::opcode_factory(const long int apc,
		const vector<U1>& code, const code_info* aci) {

	// cerr << "pc=" << apc << ", opcode=" << (int)(code[apc]) << endl;
	switch (code[apc]) {
		case 0:   return new opc_nop(apc, code, aci); break;
		case 1:   return new opc_aconst_null(apc, code, aci); break;
		case 2:   return new opc_iconst_n(apc, code, aci, -1); break;
		case 3:   return new opc_iconst_n(apc, code, aci, 0); break;
		case 4:   return new opc_iconst_n(apc, code, aci, 1); break;
		case 5:   return new opc_iconst_n(apc, code, aci, 2); break;
		case 6:   return new opc_iconst_n(apc, code, aci, 3); break;
		case 7:   return new opc_iconst_n(apc, code, aci, 4); break;
		case 8:   return new opc_iconst_n(apc, code, aci, 5); break;
		case 9:   return new opc_lconst_n(apc, code, aci, 0); break;
		case 10:  return new opc_lconst_n(apc, code, aci, 1); break;
		case 16:  return new opc_bipush(apc, code, aci); break;
		case 17:  return new opc_sipush(apc, code, aci); break;
		case 18:  return new opc_ldc(apc, code, aci); break;
		case 19:  return new opc_ldc_w(apc, code, aci); break;
		case 20:  return new opc_ldc2_w(apc, code, aci); break;
		case 21:  return new opc_iload(apc, code, aci); break;
		case 22:  return new opc_lload(apc, code, aci); break;
		case 25:  return new opc_aload(apc, code, aci); break;
		case 26:  return new opc_iload_n(apc, code, aci, 0); break;
		case 27:  return new opc_iload_n(apc, code, aci, 1); break;
		case 28:  return new opc_iload_n(apc, code, aci, 2); break;
		case 29:  return new opc_iload_n(apc, code, aci, 3); break;
		case 30:  return new opc_lload_n(apc, code, aci, 0); break;
		case 31:  return new opc_lload_n(apc, code, aci, 1); break;
		case 32:  return new opc_lload_n(apc, code, aci, 2); break;
		case 33:  return new opc_lload_n(apc, code, aci, 3); break;
		case 42:  return new opc_aload_n(apc, code, aci, 0); break;
		case 43:  return new opc_aload_n(apc, code, aci, 1); break;
		case 44:  return new opc_aload_n(apc, code, aci, 2); break;
		case 45:  return new opc_aload_n(apc, code, aci, 3); break;
		case 46:  return new opc_iaload(apc, code, aci); break;
		case 47:  return new opc_laload(apc, code, aci); break;
		case 50:  return new opc_aaload(apc, code, aci); break;
		case 54:  return new opc_istore(apc, code, aci); break;
		case 55:  return new opc_lstore(apc, code, aci); break;
		case 58:  return new opc_astore(apc, code, aci); break;
		case 59:  return new opc_istore_n(apc, code, aci, 0); break;
		case 60:  return new opc_istore_n(apc, code, aci, 1); break;
		case 61:  return new opc_istore_n(apc, code, aci, 2); break;
		case 62:  return new opc_istore_n(apc, code, aci, 3); break;
		case 63:  return new opc_lstore_n(apc, code, aci, 0); break;
		case 64:  return new opc_lstore_n(apc, code, aci, 1); break;
		case 65:  return new opc_lstore_n(apc, code, aci, 2); break;
		case 66:  return new opc_lstore_n(apc, code, aci, 3); break;
		case 75:  return new opc_astore_n(apc, code, aci, 0); break;
		case 76:  return new opc_astore_n(apc, code, aci, 1); break;
		case 77:  return new opc_astore_n(apc, code, aci, 2); break;
		case 78:  return new opc_astore_n(apc, code, aci, 3); break;
		case 87:  return new opc_pop(apc, code, aci); break;
		case 88:  return new opc_pop2(apc, code, aci); break;
		case 89:  return new opc_dup(apc, code, aci); break;
		case 90:  return new opc_dup_x1(apc, code, aci); break;
		case 91:  return new opc_dup_x2(apc, code, aci); break;
		case 92:  return new opc_dup2(apc, code, aci); break;
		case 93:  return new opc_dup2_x1(apc, code, aci); break;
		case 94:  return new opc_dup2_x2(apc, code, aci); break;
		case 95:  return new opc_swap(apc, code, aci); break;
		case 96:  return new opc_iadd(apc, code, aci); break;
		case 104: return new opc_imul(apc, code, aci); break;
		case 132: return new opc_iinc(apc, code, aci); break;
		case 133: return new opc_conv(apc, code, aci,
				opc_conv::I2L); break;
		case 136: return new opc_conv(apc, code, aci,
				opc_conv::L2I); break;
		case 148: return new opc_lcmp(apc, code, aci); break;
		case 153: return new opc_if_x(apc, code, aci,
				opc_if_x::EQ); break;
		case 154: return new opc_if_x(apc, code, aci,
				opc_if_x::NE); break;
		case 155: return new opc_if_x(apc, code, aci,
				opc_if_x::LT); break;
		case 156: return new opc_if_x(apc, code, aci,
				opc_if_x::GE); break;
		case 157: return new opc_if_x(apc, code, aci,
				opc_if_x::GT); break;
		case 158: return new opc_if_x(apc, code, aci,
				opc_if_x::LE); break;
		case 159: return new opc_ificmp_x(apc, code, aci,
				opc_ificmp_x::EQ); break;
		case 160: return new opc_ificmp_x(apc, code, aci,
				opc_ificmp_x::NE); break;
		case 161: return new opc_ificmp_x(apc, code, aci,
				opc_ificmp_x::LT); break;
		case 162: return new opc_ificmp_x(apc, code, aci,
				opc_ificmp_x::GE); break;
		case 163: return new opc_ificmp_x(apc, code, aci,
				opc_ificmp_x::GT); break;
		case 164: return new opc_ificmp_x(apc, code, aci,
				opc_ificmp_x::LE); break;
		case 165: return new opc_ifacmp_x(apc, code, aci,
				opc_ifacmp_x::EQ); break;
		case 166: return new opc_ifacmp_x(apc, code, aci,
				opc_ifacmp_x::NE); break;
		case 167: return new opc_goto(apc, code, aci); break;
		case 168: return new opc_jsr(apc, code, aci); break;
		case 169: return new opc_ret(apc, code, aci); break;
		case 172: return new opc_ireturn(apc, code, aci); break;
		case 177: return new opc_return(apc, code, aci); break;
		case 178: return new opc_getstatic(apc, code, aci); break;
		case 179: return new opc_putstatic(apc, code, aci); break;
		case 180: return new opc_getfield(apc, code, aci); break;
		case 181: return new opc_putfield(apc, code, aci); break;
		case 182: return new opc_invokevirtual(apc, code, aci); break;
		case 183: return new opc_invokespecial(apc, code, aci); break;
		case 184: return new opc_invokestatic(apc, code, aci); break;
		case 185: return new opc_invokeinterface(apc, code, aci); break;
		case 187: return new opc_new(apc, code, aci); break;
		case 188: return new opc_newarr(apc, code, aci); break;
		case 189: return new opc_anewarr(apc, code, aci); break;
		case 190: return new opc_alength(apc, code, aci); break;
		case 191: return new opc_athrow(apc, code, aci); break;
		case 192: return new opc_checkcast(apc, code, aci); break;
		case 193: return new opc_instanceof(apc, code, aci); break;
		case 194: return new opc_monitorenter(apc, code, aci); break;
		case 195: return new opc_monitorexit(apc, code, aci); break;
		case 197: return new opc_manewarr(apc, code, aci); break;
		case 198: return new opc_ifnnull(apc, code, aci,
				opc_ifnnull::EQ); break;
		case 199: return new opc_ifnnull(apc, code, aci,
				opc_ifnnull::NE); break;
		case 200: return new opc_goto_w(apc, code, aci); break;
		default: return (opcode*)0;
	}
}

/** nop */

opc_nop::opc_nop(const long int apc, const vector<U1>& code,
		const code_info* aci)
		: opcode(apc, code, aci) { }

void opc_nop::disassemble(ostream& os) const {
	os << "\t\t" << startpc << ":\t" << "nop" << endl;
}

/* EOF */
