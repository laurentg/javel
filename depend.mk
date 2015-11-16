access_info.o: access_info.cc access_info.h util.h format_spec.h
attribute_info.o: attribute_info.cc attribute_info.h util.h class_info.h \
  cp_info.h field_info.h access_info.h format_spec.h method_info.h \
  type_info.h code_info.h opcode.h stacks.h
class_info.o: class_info.cc class_info.h cp_info.h util.h field_info.h \
  access_info.h format_spec.h attribute_info.h method_info.h type_info.h \
  version.h
code_info.o: code_info.cc code_info.h util.h attribute_info.h \
  format_spec.h opcode.h stacks.h class_info.h cp_info.h field_info.h \
  access_info.h method_info.h type_info.h
cp_info.o: cp_info.cc cp_info.h util.h class_info.h field_info.h \
  access_info.h format_spec.h attribute_info.h method_info.h type_info.h
field_info.o: field_info.cc field_info.h access_info.h util.h \
  format_spec.h attribute_info.h class_info.h cp_info.h method_info.h \
  type_info.h
main.o: main.cc javel.h class_info.h cp_info.h util.h field_info.h \
  access_info.h format_spec.h attribute_info.h method_info.h type_info.h \
  version.h options_parser.h
method_info.o: method_info.cc method_info.h type_info.h util.h \
  access_info.h format_spec.h attribute_info.h class_info.h cp_info.h \
  field_info.h code_info.h opcode.h stacks.h
opc_array.o: opc_array.cc opc_array.h util.h stacks.h opcode.h \
  code_info.h attribute_info.h format_spec.h class_info.h cp_info.h \
  field_info.h access_info.h method_info.h type_info.h
opc_binop.o: opc_binop.cc opc_binop.h util.h stacks.h opcode.h \
  code_info.h attribute_info.h format_spec.h class_info.h cp_info.h \
  field_info.h access_info.h method_info.h type_info.h
opc_call.o: opc_call.cc opc_call.h util.h stacks.h opcode.h code_info.h \
  attribute_info.h format_spec.h class_info.h cp_info.h field_info.h \
  access_info.h method_info.h type_info.h
opc_dup.o: opc_dup.cc opc_dup.h util.h stacks.h opcode.h code_info.h \
  attribute_info.h format_spec.h class_info.h cp_info.h field_info.h \
  access_info.h method_info.h type_info.h
opc_jmp.o: opc_jmp.cc opc_jmp.h util.h stacks.h opcode.h code_info.h \
  attribute_info.h format_spec.h class_info.h cp_info.h field_info.h \
  access_info.h method_info.h type_info.h
opc_misc.o: opc_misc.cc opc_misc.h util.h stacks.h opcode.h code_info.h \
  attribute_info.h format_spec.h class_info.h cp_info.h field_info.h \
  access_info.h method_info.h type_info.h
opcode.o: opcode.cc opcode.h util.h stacks.h opc_ret.h opc_call.h \
  opc_binop.h opc_poush.h opc_array.h opc_jmp.h opc_dup.h opc_misc.h \
  code_info.h attribute_info.h format_spec.h class_info.h cp_info.h \
  field_info.h access_info.h method_info.h type_info.h
opc_poush.o: opc_poush.cc opc_poush.h util.h stacks.h opcode.h \
  code_info.h attribute_info.h format_spec.h class_info.h cp_info.h \
  field_info.h access_info.h method_info.h type_info.h
opc_ret.o: opc_ret.cc opc_ret.h util.h stacks.h opcode.h code_info.h \
  attribute_info.h format_spec.h class_info.h cp_info.h field_info.h \
  access_info.h method_info.h type_info.h
options_parser.o: options_parser.cc options_parser.h
stacks.o: stacks.cc stacks.h
type_info.o: type_info.cc type_info.h util.h
util.o: util.cc util.h
