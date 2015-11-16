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

#include <string.h>

#include "options_parser.h"

int options_descriptor::opt_args_cnt(const string opt) const {
	map<string, int>::const_iterator p = argscnt.find(opt);
	if (p == argscnt.end())
		return -1;
	return p->second;
}

javel_options_descriptor::javel_options_descriptor() {
	argscnt["b"] = 0;
	argscnt["c"] = 0;
	argscnt["classpath"] = 1;
	argscnt["help"] = 0;
	argscnt["l"] = 0;
	argscnt["public"] = 0;
	argscnt["protected"] = 0;
	argscnt["package"] = 0;
	argscnt["private"] = 0;
	argscnt["s"] = 0;
	argscnt["verbose"] = 0;
	argscnt["depend"] = 0;
}

options_parser::options_parser(options_descriptor* _optdsc,
	int argc, char* argv[])
	: valid(true), optdsc(_optdsc) {

	for (int i = 1; i < argc; i++) {
		int len = strlen(argv[i]);
		if (len) {
			if (argv[i][0] == '-') {
				char* p = &(argv[i][1]);
				string optname = p;
				int argscnt = optdsc->opt_args_cnt(optname);
				if (argscnt == -1) {
					cerr << "*** Invalid option "
						<< optname << endl;
					valid = false;
				} else {
					string optargs;
					for (int j = 0; j < argscnt; j++) {
						/** @todo Handle multiple
						    arguments better. */
						i++;
						if (i < argc) { // Sanity check
							optargs += argv[i];
						} else {
							cerr << "*** Missing "
							  "argument to option "
							  << optname << endl;
							valid = false;
						}
					}
					options[optname] = optargs;
				}
			} else {
				string filename = argv[i];
				files.push_back(filename);
			}
		}
	}
}

options_parser::~options_parser() {
	delete optdsc;	
}

bool options_parser::is_option_set(const string opt) const {
	return (options.find(opt) != options.end());
}

int options_parser::get_file_count() const {
	return (files.size());
}

string options_parser::get_file(int index) const {
	if (index >= 0 && index < files.size())
		return files[index];
	return "";
}

bool options_parser::is_valid() const {
	return valid;
}

