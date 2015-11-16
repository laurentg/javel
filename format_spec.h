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

#ifndef __FORMAT_SPEC_H__
#define __FORMAT_SPEC_H__

/** Disassembling format specifier class. Used as a parameter
    to the disassemble() method of the class_info class.
    @todo Should be an inner class of class_info ?
    @todo Can be implemented as a set of stream modifiers ? */
class format_spec {
	public:
		static const int PRT_PUBLIC    = 1;
		static const int PRT_PROTECTED = 2;
		static const int PRT_PACKAGE   = 3;
		static const int PRT_PRIVATE   = 4;

		format_spec(bool bc, bool ln, bool sl, int vs) :
			print_bytecode(bc),
			print_linenumber(ln),
			print_stacklocals(sl),
			print_visibility(vs) { };
		bool bytecode()    const { return print_bytecode; };
		bool linenumber()  const { return print_linenumber; };
		bool stacklocals() const { return print_stacklocals; };
		int  visibility()  const { return print_visibility; };
		
	private:
		bool print_bytecode;
		bool print_linenumber;
		bool print_stacklocals;
		int  print_visibility;
};

#endif

