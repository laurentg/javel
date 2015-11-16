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
#include <math.h>

#include "cp_info.h"
#include "class_info.h"

/** Set this symbol if you want to dump float values in the s.m.2^m form: */
#undef DUMP_FLOAT
/** Same for double: */
#undef DUMP_DOUBLE

/** This symbol is named something else on other platforms (like VC++).
    If you have problem compiling, please put a (un)signed 64 bits int. */
typedef unsigned long long ullong_t;
typedef signed long long sllong_t;

/** cp_class_info */

void cp_class_info::get(istream& is) {
	name_index = util::read_U2(is);
}

string cp_class_info::str() const {
	return ci->get_cp_info(name_index)->str();
}

void cp_class_info::makedepend(depend_list& di) const {
	di[str()] = true;	
}

/** cp_utf8_info */

void cp_utf8_info::get(istream& is) {
	ostringstream ost;
	U2 length = util::read_U2(is);
	U1* bytes = new U1[length + 1];
	for (int i = 0; i < length; i++) {
		bytes[i] = util::read_U1(is);
	}
	bytes[length] = '\0';
	ost << bytes;
	delete bytes;
	utf8 = ost.str();
}

/** @todo Handle Utf-8 decoding on local page code. */
string cp_utf8_info::str() const {
	return utf8;
}	

/** cp_nameandtype_info */

void cp_nameandtype_info::get(istream& is) {
	name_index = util::read_U2(is);
	descriptor_index = util::read_U2(is);
}

string cp_nameandtype_info::str() const {
	return ci->get_cp_info(name_index)->str();
}

string cp_nameandtype_info::descriptor() const {
	return ci->get_cp_info(descriptor_index)->str();
}

void cp_nameandtype_info::makedepend(depend_list& di) const {
}

/** cp_methodref_info */

void cp_methodref_info::makedepend(depend_list& di) const {
}

/** cp_xxxref_info */

void cp_xxxref_info::get(istream& is) {
	class_index = util::read_U2(is);
	name_and_type_index = util::read_U2(is);
}	

string cp_xxxref_info::str() const {
	return ci->get_cp_info(name_and_type_index)->str();
}

string cp_xxxref_info::classname() const {
	return ci->get_cp_info(class_index)->str();
}

string cp_xxxref_info::descriptor() const {
	return ci->get_cp_info(name_and_type_index)->descriptor();
}

/** cp_string_info */

void cp_string_info::get(istream& is) {
	string_index = util::read_U2(is);
}

string cp_string_info::str() const {
	return "\"" + ci->get_cp_info(string_index)->str() + "\"";
}	

/** cp_integer_info */

void cp_integer_info::get(istream& is) {
	bytes = util::read_U4(is);
}

string cp_integer_info::str() const {
	ostringstream ost;
	signed long int i = bytes;
	ost << i;
	return ost.str();
}

/** cp_float_info */

void cp_float_info::get(istream& is) {
	bytes = util::read_U4(is);
}

string cp_float_info::str() const {
	ostringstream ost;
	/** We need to put parenthesis around a (1.0/0.0) or similar because
	    we assume in stack decompilation that a constant has the highest
	    priority of all, which would be wrong with a division of constants
	    without parenthesis. */
	if (bytes == 0x7f800000) {
		ost << "(+1.0F / 0.0F)"; // -infinity
	} else
	if (bytes == 0xff800000) {
		ost << "(-1.0F / 0.0F)"; // +infinity
	} else
	if ((bytes >= 0x7f800001 && bytes <= 0x7fffffff) ||
	    (bytes >= 0xff800001 && bytes <= 0xffffffff)) {
		ost << "(0.0F / 0.0F)"; // NaN
	} else {
		int sign = ((bytes >> 31) == 0) ? 1 : -1;
		int expo = ((bytes >> 23) & 0xff);
		int mant = (expo == 0) ?
			(bytes & 0x7fffff) << 1 :
			(bytes & 0x7fffff) | 0x800000;
		expo -= 150;
		double x = sign;
		x *= mant;
		x *= pow(2.0, expo);
		ost << x << "F";
#ifdef DUMP_FLOAT
		ost << " /* ";
		if (sign == -1) ost << "-";
		ost << mant << ".2^" << expo << " */ ";
#endif
	}
	return ost.str();
}

/** cp_long_info */

void cp_long_info::get(istream& is) {
	high_bytes = util::read_U4(is);
	low_bytes = util::read_U4(is);
}

string cp_long_info::str() const {
	ostringstream ost;
	ullong_t n = (ullong_t)low_bytes + ((ullong_t)high_bytes << 32);
	sllong_t i = n;
	ost << i << "L";
	return ost.str();
}

/** cp_double_info */

void cp_double_info::get(istream& is) {
	high_bytes = util::read_U4(is);
	low_bytes = util::read_U4(is);
}

string cp_double_info::str() const {
	ostringstream ost;
	/** Same remark as for float. */
	if (high_bytes == 0x7ff00000 && low_bytes == 0x00000000) {
		ost << "(+1.0D / 1.0D)"; // -infinity
	} else
	if (high_bytes == 0xfff00000 && low_bytes == 0x00000000) {
		ost << "(-1.0D / 1.0D)"; // +infinity
	} else 
	if ((high_bytes & 0xfff00000 == 0x7ff00000) ||
	    (high_bytes & 0xfff00000 == 0xfff00000)) {
		ost << "(0.0D / 0.0D)"; // NaN
	} else {
		ullong_t bytes =
			((ullong_t)low_bytes + ((ullong_t)high_bytes << 32));
		int sign = ((high_bytes >> 31) == 0) ? 1 : -1;
		int expo = (high_bytes >> 20) & 0x7ff;
		expo -= 1075;
		ullong_t mant = (expo == 0) ?
			(bytes & 0xfffffffffffffLL) << 1 :
			(bytes & 0xfffffffffffffLL) | 0x10000000000000LL;
		long double x = sign;
		x *= mant;
		x *= pow(2.0, expo);
		ost << x << "D";
#ifdef DUMP_DOUBLE
		ost << " /* ";
		if (sign == -1) ost << "-";
		ost << mant << ".2^" << expo << " */ ";
#endif
	}
	return ost.str();
}

/* EOF */
