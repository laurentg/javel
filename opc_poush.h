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

#ifndef __OPC_POUSH_H__
#define __OPC_POUSH_H__

#include <iostream>
#include <vector>

#include "util.h"
#include "stacks.h"
#include "opcode.h"

class opc_giload : public opcode {
	public:
		opc_giload(const long apc, const vector<U1>& code,
				const code_info* aci);
		virtual void disassemble(ostream&) const;
		virtual sim_t simulate(stack_desc*);
	protected:
		int index;
};

class opc_iload : public opc_giload {
	public:
		opc_iload(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual int length() const { return 2; };
};

class opc_iload_n : public opc_giload {
	public:
		opc_iload_n(const long int apc, const vector<U1>& code,
				const code_info* aci, const int n);
		virtual int length() const { return 1; };
};

class opc_glload : public opc_giload {
	public:
		opc_glload(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual void disassemble(ostream&) const;
};

class opc_lload : public opc_glload {
	public:
		opc_lload(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual int length() const { return 2; };
};

class opc_lload_n : public opc_glload {
	public:
		opc_lload_n(const long int apc, const vector<U1>& code,
				const code_info* aci, const int n);
		virtual int length() const { return 1; };
};

class opc_gaload : public opcode {
	public:
		opc_gaload(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual void disassemble(ostream&) const;
		virtual sim_t simulate(stack_desc*);
	protected:
		int index;
};

class opc_aload : public opc_gaload {
	public:
		opc_aload(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual int length() const { return 2; };
};

class opc_aload_n : public opc_gaload {
	public:
		opc_aload_n(const long int apc, const vector<U1>& code,
				const code_info* aci, const int n);
		virtual int length() const { return 1; };
};

class opc_aconst_null : public opcode {
	public:
		opc_aconst_null(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual void disassemble(ostream&) const;
		virtual sim_t simulate(stack_desc*);
		virtual int length() const { return 1; };
};

class opc_gpush : public opcode {
	public:
		opc_gpush(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual void disassemble(ostream&) const;
		virtual sim_t simulate(stack_desc*);
	protected:
		int constant;
};

class opc_iconst_n : public opc_gpush {
	public:
		opc_iconst_n(const long int apc, const vector<U1>& code,
				const code_info* aci, const int n);
		virtual int length() const { return 1; };
};

class opc_lconst_n : public opc_gpush {
	public:
		opc_lconst_n(const long int apc, const vector<U1>& code,
				const code_info* aci, const int n);
		virtual void disassemble(ostream&) const;
		virtual int length() const { return 1; };
};

class opc_bipush : public opc_gpush {
	public:
		opc_bipush(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual int length() const { return 2; };
};

class opc_sipush : public opc_gpush {
	public:
		opc_sipush(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual int length() const { return 3; };
};

class opc_ggetfield : public opcode {
	public:
		opc_ggetfield(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual int length() const { return 3; };
	protected:
		int index;
};

class opc_getfield : public opc_ggetfield {
	public:
		opc_getfield(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual void disassemble(ostream&) const;
		virtual sim_t simulate(stack_desc*);
};

class opc_getstatic : public opc_ggetfield {
	public:
		opc_getstatic(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual void disassemble(ostream&) const;
		virtual sim_t simulate(stack_desc*);
};

class opc_gputfield : public opcode {
	public:
		opc_gputfield(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual int length() const { return 3; };
	protected:
		int index;
};

class opc_putfield : public opc_gputfield {
	public:
		opc_putfield(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual void disassemble(ostream&) const;
		virtual void decompile(ostream&) const;
		virtual sim_t simulate(stack_desc*);
};

class opc_putstatic : public opc_gputfield {
	public:
		opc_putstatic(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual void disassemble(ostream&) const;
		virtual void decompile(ostream&) const;
		virtual sim_t simulate(stack_desc*);
};

class opc_gistore : public opcode {
	public:
		opc_gistore(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual void disassemble(ostream&) const;
		virtual void decompile(ostream&) const;
		virtual sim_t simulate(stack_desc*);
	protected:
		int index;
};

class opc_istore : public opc_gistore {
	public:
		opc_istore(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual int length() const { return 2; };
};

class opc_istore_n : public opc_gistore {
	public:
		opc_istore_n(const long int apc, const vector<U1>& code,
				const code_info* aci, const int n);
		virtual int length() const { return 1; };
};

class opc_glstore : public opc_gistore {
	public:
		opc_glstore(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual void disassemble(ostream&) const;
};

class opc_lstore : public opc_glstore {
	public:
		opc_lstore(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual int length() const { return 2; };
};

class opc_lstore_n : public opc_glstore {
	public:
		opc_lstore_n(const long int apc, const vector<U1>& code,
				const code_info* aci, const int n);
		virtual int length() const { return 1; };
};

class opc_gastore : public opcode {
	public:
		opc_gastore(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual void disassemble(ostream&) const;
		virtual void decompile(ostream&) const;
		virtual sim_t simulate(stack_desc*);
	protected:
		int index;
};

class opc_astore : public opc_gastore {
	public:
		opc_astore(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual int length() const { return 2; };
};

class opc_astore_n : public opc_gastore {
	public:
		opc_astore_n(const long int apc, const vector<U1>& code,
				const code_info* aci, const int n);
		virtual int length() const { return 1; };
};

class opc_gldc : public opcode {
	public:
		opc_gldc(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual sim_t simulate(stack_desc*);
	protected:
		int index;
};

class opc_ldc : public opc_gldc {
	public:
		opc_ldc(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual void disassemble(ostream&) const;
		virtual int length() const { return 2; };
};

class opc_ldc_w : public opc_gldc {
	public:
		opc_ldc_w(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual void disassemble(ostream&) const;
		virtual int length() const { return 3; };
};

class opc_ldc2_w : public opc_gldc {
	public:
		opc_ldc2_w(const long int apc, const vector<U1>& code,
				const code_info* aci);
		virtual void disassemble(ostream&) const;
		virtual int length() const { return 3; };
};

#endif
