# Javel

Javel is an **experimental java class file disassembler** (but not yet decompiler), written entirely in C++.

The code is rather old (last modified in 2001) and will only work for class file up to version 45, JDK 1.1 (not tested with higher versions, right now we
are at version 52, J2SE 8).  

## Why this project?

Because at that time there was no fast disassembler so making one in C++ made sense performance-wise. It would be probably less uselful now, due to increase in performance.

Another (big) reason was the fun-factor.

## Is this a disassembler or a decompiler?

It's a disassembler (it does not reconstruct the full source code), altough I had a plan to implement this at the time, and as far as I remember there are already some code to implement this feature. There are still a few rough edges to solve, such as implementing a working heuristics to better detect `while` from `for` loops, as the compilation process is surjective in that respect, both pieces of code can produce the same compiled code.

Otherwise, the decompilation process is rather straightforward: you just have to back-build the expression tree from the stack, and implement a state machine for generating the correct expression given the code stack at any point. The rest of the process (method, constants, classes...) is already there as it is part of the disassembly process. The compiled code contains almost all the information needed to build a full version of the original code (except for the code comments and local variable names).

# Installation

As usual for a C++ project.

	$ make
	$ su
	$ make install

Please note that we do not use the standard automake/autoconf crap.
The make has been tested on a standard linux box only. Install will
copy javel onto /usr/local/bin/ and javel.1.gz (the man page) onto
/usr/share/man/man1/. Needs the stdc++ lib v3.

In short: all compilation and installation stuff are subject to fail. But the code being rather standard C++, this should not be a problem for any seasoned developer.

# Usage

To display a complete man page:

	$ man javel

To display a quick usage reminder:

	$ javel -help

To disassemble everything from a class 'Brol.class':

	$ javel -private -verbose -c Brol.class

# Copyright

This program is copyright (c) 2001,2002 by Laurent Gregoire,
<laurent.gregoire@gmail.com>. For more informations please contact the author.
Javel is released under the GNU GPL (General Public Licence) and can be freely
redistributed under the terms of this licence.

