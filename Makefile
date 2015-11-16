
# NOTE: makefile customizer, you can safely alter up to the '---EOA---'
# Building 
CC = g++
CFLAGS = -g -Wall -pedantic -Wno-long-long

# Installation paths
BIN_PATH = /usr/local/bin
MAN_PATH = /usr/share/man/man1

# ---EOA---

TARGET = javel
OBJS =	util.o \
	type_info.o \
	access_info.o \
	code_info.o \
	attribute_info.o \
	cp_info.o \
	class_info.o \
	field_info.o \
	main.o \
	method_info.o \
	options_parser.o \
	opcode.o \
	opc_ret.o \
	opc_call.o \
	opc_binop.o \
	opc_poush.o \
	opc_array.o \
	opc_jmp.o \
	opc_dup.o \
	opc_misc.o \
	stacks.o

all:: $(TARGET) mandoc

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

.cc.o:
	$(CC) $(CFLAGS) -c $< -o $@

version.h: version.hh VERSION
	cat version.hh | sed s/__version__/`cat VERSION`/ > version.h

run::
	./javel *.class > out;

release:: depend
	tar czf javel`cat VERSION`.tar.gz VERSION *.cc *.h *.hh makefile depend.mk javel.1 TODO README jcx-1.0.xsd

mandoc:: javel.1.gz

javel.1.gz: javel.1
	gzip -c javel.1 > javel.1.gz

depend::
	$(CC) *.cc -MM > depend.mk

clean::
	-rm $(OBJS) $(TARGET)
	-rm -Rf ./doc
	-rm *~

build:: clean depend all

test:: all
	-rm Test1.class Test2.class
	javac Test.java
	mv Test.class Test1.class
	jikes -classpath /usr/share/kaffe/Klasses.jar Test.java
	mv Test.class Test2.class
	./javel Test1.class Test2.class > out

test2:: all
	jikes -g -classpath /usr/share/kaffe/Klasses.jar Brol.java
	./javel -c Brol.class

install:: all
	@if [ `whoami` != 'root' ]; then \
		echo "Please be root to install!"; \
	else \
		echo "Installing binary to "$(BIN_PATH); \
		cp -f -p ./javel $(BIN_PATH); \
		echo "Installing man page to "$(MAN_PATH); \
		cp -f -p ./javel.1.gz $(MAN_PATH); \
	fi;

doc::
	doxygen doxyconf

include depend.mk

