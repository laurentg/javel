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

#ifndef __OPC_JMP_H__
#define __OPC_JMP_H__

#include <iostream>
#include <vector>

#include "util.h"
#include "stacks.h"
#include "opcode.h"

class opc_goto : public opcode {
	public:
		opc_goto(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual void disassemble(ostream&) const;
		virtual void decompile(ostream&) const;
		virtual int length() const { return 3; };
		virtual int nextpc() const { return -1; };
		virtual int gotopc() const { return startpc + offset_pc; };
	private:
		signed short int offset_pc;
};

class opc_goto_w : public opcode {
	public:
		opc_goto_w(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual void disassemble(ostream&) const;
		virtual void decompile(ostream&) const;
		virtual int length() const { return 5; };
		virtual int nextpc() const { return -1; };
		virtual int gotopc() const { return startpc + offset_pc; };
	private:
		signed long int offset_pc;
};

class opc_ificmp_x : public opcode {
	public:
		enum kind_t { EQ, NE, LT, LE, GT, GE };
		opc_ificmp_x(const long int apc, const vector<U1>& code,
				const code_info* aci, const kind_t akind);
		virtual void disassemble(ostream&) const;
		virtual void decompile(ostream&) const;
		virtual sim_t simulate(stack_desc*);
		virtual int length() const { return 3; };
		virtual int gotopc() const { return startpc + offset_pc; };
	private:
		signed short int offset_pc;
		kind_t kind;
};

class opc_if_x : public opcode {
	public:
		enum kind_t { EQ, NE, LT, LE, GT, GE };
		opc_if_x(const long int apc, const vector<U1>& code,
				const code_info* aci, const kind_t akind);
		virtual void disassemble(ostream&) const;
		virtual void decompile(ostream&) const;
		virtual sim_t simulate(stack_desc*);
		virtual int length() const { return 3; };
		virtual int gotopc() const { return startpc + offset_pc; };
	private:
		signed short int offset_pc;
		kind_t kind;
};

class opc_ifnnull : public opcode {
	public:
		enum kind_t { EQ, NE };
		opc_ifnnull(const long int apc, const vector<U1>& code,
				const code_info* aci, const kind_t akind);
		virtual void disassemble(ostream&) const;
		virtual void decompile(ostream&) const;
		virtual sim_t simulate(stack_desc*);
		virtual int length() const { return 3; };
		virtual int gotopc() const { return startpc + offset_pc; };
	private:
		signed short int offset_pc;
		kind_t kind;
};

class opc_ifacmp_x : public opcode {
	public:
		enum kind_t { EQ, NE };
		opc_ifacmp_x(const long int apc, const vector<U1>& code,
				const code_info* aci, const kind_t akind);
		virtual void disassemble(ostream&) const;
		virtual void decompile(ostream&) const;
		virtual sim_t simulate(stack_desc*);
		virtual int length() const { return 3; };
		virtual int gotopc() const { return startpc + offset_pc; };
	private:
		signed short int offset_pc;
		kind_t kind;
};

class opc_athrow : public opcode {
	public:
		opc_athrow(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual void disassemble(ostream&) const;
		virtual void decompile(ostream&) const;
		virtual sim_t simulate(stack_desc*);
		virtual int length() const { return 1; };
		/** For athrow, there is no pc to follow. */
		virtual int nextpc() const { return -1; };
};

class opc_jsr : public opcode {
	public:
		opc_jsr(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual void disassemble(ostream&) const;
		virtual void decompile(ostream&) const;
		virtual sim_t simulate(stack_desc*);
		virtual sim_t simulate_goto(stack_desc*);
		virtual int length() const { return 3; };
		virtual int gotopc() const { return startpc + offset_pc; };
	private:
		signed short int offset_pc;
};

class opc_ret : public opcode {
	public:
		opc_ret(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual void disassemble(ostream&) const;
		virtual void decompile(ostream&) const;
		virtual sim_t simulate(stack_desc*);
		virtual int length() const { return 2; };
		virtual int nextpc() const { return -1; };
	private:
		int index;
};

#endif
