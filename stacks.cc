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

#include "stacks.h"

stack_elem::stack_elem() { }

stack_elem::~stack_elem() { }

/* ----------------------------------------------------------- */

stack_elem* stk_int_const::clone() const {
	return new stk_int_const(constant);
}

void stk_int_const::decompile(ostream& os) const {
	os << constant;
}

/* ----------------------------------------------------------- */

stack_elem* stk_const::clone() const {
	return new stk_const(constant);
}

void stk_const::decompile(ostream& os) const {
	os << constant;
}

/* ----------------------------------------------------------- */

stack_elem* stk_local_var::clone() const {
	return new stk_local_var(variable);
}

void stk_local_var::decompile(ostream& os) const {
	os << variable;
}

/* ----------------------------------------------------------- */

stk_arref::stk_arref(const stack_elem* array, const stack_elem* index) :
		arr(array->clone()), ndx(index->clone()) { };

stk_arref::~stk_arref() {
	if (arr) delete arr;
	if (ndx) delete ndx;
}

stack_elem* stk_arref::clone() const {
	return new stk_arref(arr, ndx);
}

void stk_arref::decompile(ostream& os) const {
	if (arr && ndx) {
		arr->decompile(os);
		os << "[";
		ndx->decompile(os);
		os << "]";
	}
}

/* ----------------------------------------------------------- */

stk_arrlen::stk_arrlen(const stack_elem* array) :
		arr(array->clone()) { }

stk_arrlen::~stk_arrlen() {
	if (arr) delete arr;
}

stack_elem* stk_arrlen::clone() const {
	return new stk_arrlen(arr);
}

void stk_arrlen::decompile(ostream& os) const {
	if (arr) {
		arr->decompile(os);
		os << ".length";
	}
}

/* ----------------------------------------------------------- */

stk_newarr::stk_newarr(string type) :
		ty(type) { }

stk_newarr::~stk_newarr() {
	for (int i = 0; i < sz.size(); ++i)
		delete sz[i];
}

stack_elem* stk_newarr::clone() const {
	stk_newarr* a = new stk_newarr(ty);
	for (int i = 0; i < sz.size(); ++i)
		a->push_size(sz[i]);
	return a;
}

void stk_newarr::decompile(ostream& os) const {
	os << "new " << ty;
	for (int i = 0; i < sz.size(); ++i) {
		os << "[";
		sz[i]->decompile(os);
		os << "]";
	}
}

void stk_newarr::push_size(const stack_elem* size) {
	sz.push_back(size->clone());
}

void stk_newarr::rpush_size(const stack_elem* size) {
	sz.push_front(size->clone());
}

/* ----------------------------------------------------------- */

stk_func::stk_func(string aname) :
	obj(0), name(aname) { }
	
stk_func::~stk_func() {
	for (int i = 0; i < args.size(); ++i)
		delete args[i];
	if (obj) delete obj;
}

stack_elem* stk_func::clone() const {
	stk_func* f = new stk_func(name);
	if (obj) f->set_object(obj);
	f->set_classname(classname);
	for (int i = 0; i < args.size(); ++i)
		f->push_arg(args[i]);
	return f;
}

void stk_func::decompile(ostream& os) const {
	if (obj) {
		obj->decompile(os);
		os << ".";
	} else if (!classname.empty()) {
		os << classname << ".";
	}
	os << name << "(";
	for (int i = 0; i < args.size(); ++i) {
		args[i]->decompile(os);
		if (i < args.size() - 1)
			os << ", ";
	}
	os << ")";
}

void stk_func::push_arg(const stack_elem* arg) {
	args.push_back(arg->clone());
}

void stk_func::rpush_arg(const stack_elem* arg) {
	args.push_front(arg->clone());
}

void stk_func::set_object(const stack_elem* obj) {
	this->obj = obj->clone();
}

void stk_func::set_classname(const string& aclassname) {
	classname = aclassname;
}

/* ----------------------------------------------------------- */

stk_new::stk_new(string aclassname) :
	classname(aclassname) { }
	
stk_new::~stk_new() {
	for (int i = 0; i < args.size(); ++i)
		delete args[i];
}

stack_elem* stk_new::clone() const {
	stk_new* n = new stk_new(classname);
	for (int i = 0; i < args.size(); i++)
		n->push_arg(args[i]);
	return n;
}

void stk_new::decompile(ostream& os) const {
	os << "new " << classname << "(";
	for (int i = 0; i < args.size(); ++i) {
		args[i]->decompile(os);
		if (i < args.size() - 1)
			os << ", ";
	}
	os << ")";
}

void stk_new::push_arg(const stack_elem* arg) {
	args.push_back(arg->clone());
}

void stk_new::rpush_arg(const stack_elem* arg) {
	args.push_front(arg->clone());
}

/* ----------------------------------------------------------- */

stk_binop::stk_binop(const stack_elem* l, const stack_elem* r, op_t o) :
	right(r->clone()), left(l->clone()), op(o) { }

stk_binop::~stk_binop() {
	if (left) delete left;
	if (right) delete right;
}

stack_elem* stk_binop::clone() const {
	return new stk_binop(left, right, op);
}

/** @todo Normally <x>CMP should not be decompiled that way. It should be
    linked to the if statement using the result of the comparison, then
    expanded using this int 'if'. */

void stk_binop::decompile(ostream& os) const {
	/** We enclose in parenthesis only what is needed, no more. */
	if (left->priority() < this->priority()) os << "(";
	left->decompile(os);
	if (left->priority() < this->priority()) os << ")";
	switch (op) {
	case ADD: os << " + "; break;
	case SUB: os << " - "; break;
	case MUL: os << " * "; break;
	case DIV: os << " / "; break;
	case MOD: os << " % "; break;
	case LCMP: os << " ?= "; break;
	}
	if (right->priority() < this->priority()) os << "(";
	right->decompile(os);
	if (right->priority() < this->priority()) os << ")";
}

stack_elem::priority_t stk_binop::priority() const {
	switch (op) {
		case ADD:
		case SUB:  return P3;
		case MUL:
		case DIV:
		case MOD:  return P2;
		case LCMP: return P4;
}	}

/* ----------------------------------------------------------- */

stk_conv::stk_conv(const stack_elem* w, kind_t k) :
	what(w->clone()), kind(k) { }

stk_conv::~stk_conv() {
	if (what) delete what;
}

stack_elem* stk_conv::clone() const {
	return new stk_conv(what, kind);
}

void stk_conv::decompile(ostream& os) const {
	switch (kind) {
		case I2L: os << "(long)"; break;
		case L2I: os << "(int)"; break;
	}
	/** We enclose in parenthesis only what is needed, no more. */
	if (what->priority() < this->priority()) os << "(";
	what->decompile(os);
	if (what->priority() < this->priority()) os << ")";
}

stack_elem::priority_t stk_conv::priority() const {
	return P1;
}

/* ----------------------------------------------------------- */

stk_field::stk_field(const stack_elem* object, const string& fieldname) {
	obj = object->clone();
	fieldn = fieldname;
}

stk_field::~stk_field() {
	if (obj) delete obj;
}

stack_elem* stk_field::clone() const {
	return new stk_field(obj, fieldn);
}

void stk_field::decompile(ostream& os) const {
	if (obj) {
		obj->decompile(os);
		os << ".";
	}
	os << fieldn;
}

/* ----------------------------------------------------------- */

stk_instance::stk_instance(const stack_elem* object, const string& classname) {
	obj = object->clone();
	classn = classname;
}

stk_instance::~stk_instance() {
	if (obj) delete obj;
}

stack_elem* stk_instance::clone() const {
	return new stk_instance(obj, classn);
}

void stk_instance::decompile(ostream& os) const {
	/** We enclose in parenthesis only what is needed, no more. */
	if (obj->priority() < this->priority()) os << "(";
	obj->decompile(os);
	if (obj->priority() < this->priority()) os << ")";
	os << " instanceof " << classn;
}

/* ----------------------------------------------------------- */

stk_clcast::stk_clcast(const stack_elem* object, const string& classname) {
	obj = object->clone();
	classn = classname;
}

stk_clcast::~stk_clcast() {
	if (obj) delete obj;
}

stack_elem* stk_clcast::clone() const {
	return new stk_clcast(obj, classn);
}

void stk_clcast::decompile(ostream& os) const {
	os << "(" << classn << ")";
	/** We enclose in parenthesis only what is needed, no more. */
	if (obj->priority() < this->priority()) os << "(";
	obj->decompile(os);
	if (obj->priority() < this->priority()) os << ")";
}


/* ----------------------------------------------------------- */

stk_staticfield::stk_staticfield(const string& classname,
		const string& fieldname) {
	classn = classname;
	fieldn = fieldname;
}

stack_elem* stk_staticfield::clone() const {
	return new stk_staticfield(classn, fieldn);
}

void stk_staticfield::decompile(ostream& os) const {
	os << classn << "." << fieldn;
}

/* ----------------------------------------------------------- */

stack_item::stack_item() : elem(0) {
}

stack_item::stack_item(const stack_item& si) : elem(0) {
	if (si.elem)	elem = si->clone();
}

stack_item::stack_item(stack_elem* e) : elem(e) { }

stack_item::~stack_item() {
	if (elem) delete elem;
}

stack_item& stack_item::operator=(const stack_item& si) {
	if (elem) delete elem;
	if (si.elem)	elem = si->clone();
	else		elem = 0;
	return *this;
}

/* ----------------------------------------------------------- */

stack_desc::stack_desc() { }

stack_desc::stack_desc(const stack_desc& sc) {
	stk = sc.stk;
}

stack_desc::~stack_desc() {

}

stack_item stack_desc::pop() {
#if USE_VECTOR
	assert(!stk.empty());
	stack_item si = stk[stk.size() - 1];
	stk.pop_back();
	return si;
#else
	stack_item si = stk.top();
	stk.pop();
	return si;
#endif
}

const stack_item& stack_desc::top() {
#if USE_VECTOR
	assert(!stk.empty());
	return stk[stk.size() - 1];
#else
	return stk.top();
#endif
}

stack_item stack_desc::top(const int n) {
#if USE_VECTOR
	assert(n < stk.size());
	return stk[stk.size() - n - 1];
#else
	/** Be careful! Code highly inefficient! See remark below. */
	int loop = n;
	stack<stack_item> s2;
	stack_item si;
	while (!stk.empty() && loop--) {
		s2.push(stk.top());
		stk.pop();
	}
	si = stk.top();
	while (!s2.empty()) {
		stk.push(s2.top());
		s2.pop();
	}
	return si;
#endif
}

void stack_desc::push(const stack_item& si) {
#if USE_VECTOR
	stk.push_back(si);
#else
	stk.push(si);
#endif
}

void stack_desc::disassemble(ostream& os) const {
	os << "\t\t\t";
#if USE_VECTOR
	if (stk.empty())
		os << "-";
	else
	for(vector<stack_item>::const_iterator p = stk.begin();
			p != stk.end(); ++p) {
		os << "{";
		(*p)->decompile(os);
		os << "} ";
	}
	os << endl;
#else
	stack<stack_item> s2;
	/** Be careful! Code highly inefficient! Devise a way to
	    iterate throught a STL stack. */
	while (!stk.empty()) {
		s2.push(stk.top());
		stk.pop();
	}
	while (!s2.empty()) {
		os << "{";
		if (s2.top().empty())	os << "?";
		else			s2.top()->decompile(os);
		os << "} ";
		stk.push(s2.top());
		s2.pop();
	}
#endif
}

