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

#include <iostream>
#include <fstream>

#include "javel.h"
#include "version.h"
#include "options_parser.h"

/** Display the javel command-line use informations. */
void usage() {
	cerr << "JAVEL version " << VERSION << endl;
	cerr << "Copyright (C) 2001,2002 Laurent Gregoire "
		<< "(laurent.gregoire@icam.fr)" << endl;
	cerr << "usage: javel [-options] classes" << endl;
	cerr << "\tOptions are:" << endl;
	cerr << "\t-b *                 For compatibility only" << endl;
	cerr << "\t-c                   Disassemble bytecode" << endl;
	cerr << "\t-help                Prints this usage message" << endl;
	cerr << "\t-l                   Prints line number information" << endl;
	cerr << "\t-public              Show only public classes & members"
		<< endl;
	cerr << "\t-protected           Show protected/public classes & "
	       "members" << endl;
	cerr << "\t-package             Show package/protected/public "
		"classes & members" << endl;
	cerr << "\t-private             Show all classes & members"	<< endl;
	cerr << "\t-s *                 Print internal type signatures" << endl;
	cerr << "\t-verbose             Print stack size, locals and arguments"
			<< endl;
	cerr << "\t-classpath [path] *  For compatibility only" << endl;
	cerr << "\t-depend              Print depend informations" << endl;
	cerr << "\t* Option ignored." << endl;
}

/** Main entry point: catches all exceptions, parse options, build one or
    several class_info objects, and depending on the options, dump infos
    for them. */
int main(int argc, char* argv[]) {

	try {
		/** Build an option_parser with the javel_options_descriptor
		    as the options descriptor parameter. */
		options_parser op(new javel_options_descriptor(), argc, argv);

		if (!op.is_valid()) {
			return EXIT_FAILURE;
		}
		
		/** If no files are specified on the command line, or if the
		    help was required, display use and exit. */
		if (op.get_file_count() == 0 || op.is_option_set("help")) {
			usage();
			return EXIT_FAILURE;
		}
		
		/** Loop for each classes specified on the command-line. */
		for (int i = 0; i < op.get_file_count(); i++) {
			/** Build the input stream. */
			ifstream in(op.get_file(i).c_str());
			if (!in)
				throw io_exception();
			/** Load the class from it. */
			class_info ci(in);
			/** Specify the format_spec from the options. */
			int visibility = format_spec::PRT_PUBLIC;
			if (op.is_option_set("private"))
				visibility = format_spec::PRT_PRIVATE;
			if (op.is_option_set("package"))
				visibility = format_spec::PRT_PACKAGE;
			if (op.is_option_set("protected"))
				visibility = format_spec::PRT_PROTECTED;
			if (op.is_option_set("public"))
				visibility = format_spec::PRT_PUBLIC;
			format_spec fs(
				op.is_option_set("c"),
				op.is_option_set("l"),
				op.is_option_set("verbose"),
				visibility);
			/** Make dependencies or disassemble. */
			if (op.is_option_set("depend"))
				ci.makedepend(op.get_file(i), cout);
			else
				ci.disassemble(fs, cout);
		}
		
	/** On exception, exit. */
	} catch (javel_exception& e) {
		cerr << e << endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

