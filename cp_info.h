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

#ifndef __CP_INFO_H__
#define __CP_INFO_H__

#include <iostream>
#include <vector>
#include <string>

#include "util.h"

const unsigned int CONSTANT_CLASS		= 7;
const unsigned int CONSTANT_FIELDREF		= 9;
const unsigned int CONSTANT_METHODREF		= 10;
const unsigned int CONSTANT_INTERFACEMETHODREF	= 11;
const unsigned int CONSTANT_STRING		= 8;
const unsigned int CONSTANT_INTEGER		= 3;
const unsigned int CONSTANT_FLOAT		= 4;
const unsigned int CONSTANT_LONG		= 5;
const unsigned int CONSTANT_DOUBLE		= 6;
const unsigned int CONSTANT_NAMEANDTYPE		= 12;
const unsigned int CONSTANT_UTF8		= 1;

class class_info;

class cp_info {
	public:
		virtual ~cp_info() {};
		virtual cp_info* clone() const = 0;
		virtual void get(istream&) = 0;
		virtual int get_num_slots() { return 1; };
		virtual string str() const { return ""; };
		virtual string classname() const { return ""; };
		virtual string descriptor() const { return ""; };
		virtual string idname() const { return ""; };
		virtual void makedepend(depend_list& di) const { };
	protected:
		const class_info* ci;
};

class cp_class_info : public cp_info {
	public:
		cp_class_info(const class_info* _ci) { ci = _ci; };
		virtual cp_info* clone() const
			{ return new cp_class_info(ci); };
		virtual void get(istream&);
		virtual string str() const;
		virtual void makedepend(depend_list& di) const;
	private:
		U2 name_index;
};

class cp_utf8_info : public cp_info {
	public:
		cp_utf8_info(const class_info* _ci) { ci = _ci; };
		virtual cp_info* clone() const
			{ return new cp_utf8_info(ci); };
		virtual void get(istream&);
		virtual string str() const;
	private:
		string utf8;
};

class cp_nameandtype_info : public cp_info {
	public:
		cp_nameandtype_info(const class_info* _ci) { ci = _ci; };
		virtual cp_info* clone() const
			{ return new cp_nameandtype_info(ci); };
		virtual void get(istream&);
		virtual string str() const;
		virtual string descriptor() const;
		virtual void makedepend(depend_list& di) const;
#if 0
		U2 get_name() const { return name_index; };
		U2 get_desc() const { return descriptor_index; };
#endif
	private:
		U2 name_index;
		U2 descriptor_index;
};

class cp_xxxref_info : public cp_info {
	public:
		virtual void get(istream&);
		virtual string str() const;
		virtual string classname() const;
		virtual string descriptor() const;
#if 0
		U2 get_class() const { return class_index; };
		U2 get_type() const { return name_and_type_index; };
#endif
	protected:
		U2 class_index;
		U2 name_and_type_index;
};

class cp_fieldref_info : public cp_xxxref_info {
	public:
		cp_fieldref_info(const class_info* _ci) { ci = _ci; };
		virtual cp_info* clone() const
			{ return new cp_fieldref_info(ci); };
};
		
class cp_methodref_info : public cp_xxxref_info {
	public:
		cp_methodref_info(const class_info* _ci) { ci = _ci; };
		virtual cp_info* clone() const
			{ return new cp_methodref_info(ci); };
		virtual void makedepend(depend_list& di) const;
};
		
class cp_interfacemethodref_info : public cp_xxxref_info {
	public:
		cp_interfacemethodref_info(const class_info* _ci) { ci = _ci; };
		virtual cp_info* clone() const
			{ return new cp_interfacemethodref_info(ci); };
};

class cp_string_info : public cp_info {
	public:
		cp_string_info(const class_info* _ci) { ci = _ci; };
		virtual cp_info* clone() const
			{ return new cp_string_info(ci); };
		virtual void get(istream&);
		virtual string str() const;
	private:
		U2 string_index;
};

class cp_integer_info : public cp_info {
	public:
		cp_integer_info(const class_info* _ci) { ci = _ci; };
		virtual cp_info* clone() const
			{ return new cp_integer_info(ci); };
		virtual void get(istream&);
		virtual string str() const;
	private:
		U4 bytes;
};

class cp_float_info : public cp_info {
	public:
		cp_float_info(const class_info* _ci) { ci = _ci; };
		virtual cp_info* clone() const
			{ return new cp_float_info(ci); };
		virtual void get(istream&);
		virtual string str() const;
	private:
		U4 bytes;
};
		
class cp_long_info : public cp_info {
	public:
		cp_long_info(const class_info* _ci) { ci = _ci; };
		virtual cp_info* clone() const
			{ return new cp_long_info(ci); };
		virtual void get(istream&);
		virtual int get_num_slots() { return 2; };
		virtual string str() const;
	private:
		U4 high_bytes;
		U4 low_bytes;
};
		
class cp_double_info : public cp_info {
	public:
		cp_double_info(const class_info* _ci) { ci = _ci; };
		virtual cp_info* clone() const
			{ return new cp_double_info(ci); };
		virtual void get(istream&);
		virtual int get_num_slots() { return 2; };
		virtual string str() const;
	private:
		U4 high_bytes;
		U4 low_bytes;
};

#endif

