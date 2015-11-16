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

#ifndef __OPC_ARRAY_H__
#define __OPC_ARRAY_H__

#include <iostream>
#include <vector>

#include "util.h"
#include "stacks.h"
#include "opcode.h"

/** generic operations */

class opc_garrload : public opcode {
	public:
		opc_garrload(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual int length() const { return 1; };
		virtual sim_t simulate(stack_desc*);
};

/** int operations */

class opc_iaload : public opc_garrload {
	public:
		opc_iaload(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual void disassemble(ostream&) const;
};

/** long operations */

class opc_laload : public opc_garrload {
	public:
		opc_laload(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual void disassemble(ostream&) const;
};

/** reference operations */

class opc_aaload : public opc_garrload {
	public:
		opc_aaload(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual void disassemble(ostream&) const;
};

/** length operation */

class opc_alength : public opcode {
	public:
		opc_alength(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual void disassemble(ostream&) const;
		virtual int length() const { return 1; };
		virtual sim_t simulate(stack_desc*);
};

/** newarray, anewarray and multianewarray */

class opc_newarr : public opcode {
	public:
		opc_newarr(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual void disassemble(ostream&) const;
		virtual int length() const { return 2; };
		virtual sim_t simulate(stack_desc*);
	private:
		int type;
		string str_type() const;
};

class opc_anewarr : public opcode {
	public:
		opc_anewarr(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual void disassemble(ostream&) const;
		virtual int length() const { return 3; };
		virtual sim_t simulate(stack_desc*);
	private:
		int index;
		string str_type() const;
};

class opc_manewarr : public opcode {
	public:
		opc_manewarr(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual void disassemble(ostream&) const;
		virtual int length() const { return 4; };
		virtual sim_t simulate(stack_desc*);
	private:
		int index;
		int dimension;
		string str_type() const;
};

#endif
