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

#ifndef __STACKS_H__
#define __STACKS_H__

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <stack>

#define USE_VECTOR 1

class stack_elem {
	public:
		enum priority_t {
			PMIN, P13, P12, P11, P10, P9, P8, P7,
			P6, P5, P4, P3, P2, P1, PMAX };
		stack_elem();
		virtual ~stack_elem();
		/** virtual constructor */
		virtual stack_elem* clone() const = 0;
		virtual void decompile(ostream& os) const = 0;
		virtual priority_t priority() const { return PMAX; };
	private:
		stack_elem(const stack_elem&);
		stack_elem& operator=(const stack_elem&);
};

class stk_int_const : public stack_elem {
	public:
		stk_int_const(long cst) : constant(cst) { };
		virtual stack_elem* clone() const;
		virtual void decompile(ostream& os) const;
	private:
		long constant;
};

class stk_const : public stack_elem {
	public:
		stk_const(const string& cst) : constant(cst) { };
		virtual stack_elem* clone() const;
		virtual void decompile(ostream& os) const;
	private:
		string constant;
};

class stk_local_var : public stack_elem {
	public:
		stk_local_var(string v) : variable(v) { };
		virtual stack_elem* clone() const;
		virtual void decompile(ostream& os) const;
	private:
		string variable;
};

class stk_arref : public stack_elem {
	public:
		stk_arref(const stack_elem* array, const stack_elem* index);
		virtual ~stk_arref();
		virtual stack_elem* clone() const;
		virtual void decompile(ostream& os) const;
	private:
		stack_elem *arr, *ndx;
};

class stk_arrlen : public stack_elem {
	public:
		stk_arrlen(const stack_elem* array);
		virtual ~stk_arrlen();
		virtual stack_elem* clone() const;
		virtual void decompile(ostream& os) const;
	private:
		stack_elem *arr;
};

class stk_newarr : public stack_elem {
	public:
		stk_newarr(string type);
		virtual ~stk_newarr();
		virtual stack_elem* clone() const;
		virtual void decompile(ostream& os) const;
		void push_size(const stack_elem* size);
		void rpush_size(const stack_elem* size);
	private:
		string ty;
		deque<stack_elem*> sz;
};

class stk_func : public stack_elem {
	public:
		stk_func(string aname);
		virtual ~stk_func();
		virtual stack_elem* clone() const;
		virtual void decompile(ostream& os) const;
		void push_arg(const stack_elem* arg);
		void rpush_arg(const stack_elem* arg);
		void set_object(const stack_elem* obj);
		void set_classname(const string& aclassname);
	private:
		stack_elem* obj;
		deque<stack_elem*> args;
		string name, classname;
};

class stk_new : public stack_elem {
	public:
		stk_new(string aclassname);
		virtual ~stk_new();
		virtual stack_elem* clone() const;
		virtual void decompile(ostream& os) const;
		void push_arg(const stack_elem* arg);
		void rpush_arg(const stack_elem* arg);
	private:
		deque<stack_elem*> args;
		string classname;
};

class stk_binop : public stack_elem {
	public:
		enum op_t { ADD, SUB, MUL, DIV, MOD, LCMP };
		stk_binop(const stack_elem* l, const stack_elem* r, op_t o);
		virtual ~stk_binop();
		virtual stack_elem* clone() const;
		virtual void decompile(ostream& os) const;
		virtual priority_t priority() const;
	private:
		stack_elem *right, *left;
		op_t op;
};

class stk_conv : public stack_elem {
	public:
		enum kind_t { I2L, L2I };
		stk_conv(const stack_elem* w, kind_t k);
		virtual ~stk_conv();
		virtual stack_elem* clone() const;
		virtual void decompile(ostream& os) const;
		virtual priority_t priority() const;
	private:
		stack_elem *what;
		kind_t kind;
};

class stk_instance : public stack_elem {
	public:
		stk_instance(const stack_elem* object, const string& classname);
		virtual ~stk_instance();
		virtual stack_elem* clone() const;
		virtual void decompile(ostream& os) const;
		virtual priority_t priority() const { return P5; };
	private:
		stack_elem *obj;
		string classn;
};

class stk_clcast : public stack_elem {
	public:
		stk_clcast(const stack_elem* object, const string& classname);
		virtual ~stk_clcast();
		virtual stack_elem* clone() const;
		virtual void decompile(ostream& os) const;
		virtual priority_t priority() const { return P1; };
	private:
		stack_elem *obj;
		string classn;
};

class stk_field : public stack_elem {
	public:
		stk_field(const stack_elem* object, const string& fieldname);
		virtual ~stk_field();
		virtual stack_elem* clone() const;
		virtual void decompile(ostream& os) const;
	private:
		stack_elem *obj;
		string fieldn;
};

class stk_staticfield : public stack_elem {
	public:
		stk_staticfield(const string& classname,
			const string& fieldname);
		virtual stack_elem* clone() const;
		virtual void decompile(ostream& os) const;
	private:
		string classn, fieldn;
};

class stack_item {
	public:
		stack_item();
		stack_item(const stack_item&);
		stack_item(stack_elem*);
		~stack_item();
		stack_item& operator=(const stack_item&);
		stack_elem* operator->() { return elem; };
		const stack_elem* operator->() const { return elem; };
		operator stack_elem*() { return elem; };
		operator const stack_elem*() const { return elem; };
		bool empty() const { return (elem == 0); };
	private:
		stack_elem* elem;
};

class stack_desc {
	public:
		/** Create an empty stack */
		stack_desc();
		/** Create a copy of a stack */
		stack_desc(const stack_desc&);
		/** Destructor */
		virtual ~stack_desc();

		/** Pop and get one item from the top */
		stack_item pop();
		/** Get the top element */
		const stack_item& top();
		/** Get the top element - n */
		stack_item top(const int n);
		/** Push one item on the top */
		void push(const stack_item& item);

		/** Disassemble the stack to output stream */
		void disassemble(ostream&) const;

	private:
#if USE_VECTOR
		mutable vector<stack_item> stk;
#else
		mutable stack<stack_item> stk;
#endif
};

#endif
