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

/** @todo Use a standard open source command-line options parser
    instead of this 'temporary... but after all permanent' stuff. */

#ifndef __OPTIONSPARSER_H__
#define __OPTIONSPARSER_H__

#include <string>
#include <map>
#include <vector>

/** Abstract class for describing a set of command-line options.
    Subclasses defines the opt_args_cnt to provide the description
    of all flags supported. */
class options_descriptor {

	public:
		options_descriptor() { };
		virtual ~options_descriptor() { };

		virtual int opt_args_cnt(const string opt) const;
		
	protected:
		map<string, int> argscnt;
};

/** Concrete implementation for the javel program. */
class javel_options_descriptor : public options_descriptor {

	public:
		javel_options_descriptor();
		virtual ~javel_options_descriptor() { };
};
	
/** To construct an option_parser one must provide an instance of
    an option_descriptor which will describe options used.
    Pattern: Kind of Strategy. */
class options_parser {

	public:
		typedef map<string, string> opt_map_t;
		
		options_parser(options_descriptor* _optdsc,
				int argc, char* argv[]);
		virtual ~options_parser();

		bool is_option_set(const string opt) const;
		string get_option(const string opt) const;
		int get_file_count() const;
		string get_file(const int index) const;
		bool is_valid() const;
	
	protected:
	private:

		opt_map_t options;
		vector<string> files;
		options_descriptor* optdsc;
		bool valid;
};

#endif

