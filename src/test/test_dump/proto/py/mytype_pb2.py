# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: mytype.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor.FileDescriptor(
  name='mytype.proto',
  package='',
  serialized_pb=_b('\n\x0cmytype.proto\"8\n\x06MyType\x12\n\n\x02id\x18\x01 \x01(\x05\x12\x0e\n\x06longId\x18\x02 \x01(\x03\x12\x12\n\nStrMessage\x18\x03 \x01(\x0c\"9\n\x07MyType1\x12\n\n\x02id\x18\x01 \x01(\x05\x12\x0e\n\x06longId\x18\x02 \x01(\x03\x12\x12\n\nStrMessage\x18\x03 \x01(\x0c\"9\n\x07MyType2\x12\n\n\x02id\x18\x01 \x01(\x05\x12\x0e\n\x06longId\x18\x02 \x01(\x03\x12\x12\n\nStrMessage\x18\x03 \x01(\x0c\"9\n\x07MyType3\x12\n\n\x02id\x18\x01 \x03(\x05\x12\x0e\n\x06longId\x18\x02 \x03(\x03\x12\x12\n\nStrMessage\x18\x03 \x03(\x0c\"`\n\x0bMyTypeArray\x12\x12\n\x01t\x18\x01 \x03(\x0b\x32\x07.MyType\x12\x13\n\x02t1\x18\x02 \x03(\x0b\x32\x07.MyType\x12\x13\n\x02t2\x18\x03 \x03(\x0b\x32\x07.MyType\x12\x13\n\x02t3\x18\x04 \x03(\x0b\x32\x07.MyType\")\n\x11TestRequiredField\x12\x14\n\x03val\x18\x01 \x02(\x0b\x32\x07.MyType')
)
_sym_db.RegisterFileDescriptor(DESCRIPTOR)




_MYTYPE = _descriptor.Descriptor(
  name='MyType',
  full_name='MyType',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='id', full_name='MyType.id', index=0,
      number=1, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='longId', full_name='MyType.longId', index=1,
      number=2, type=3, cpp_type=2, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='StrMessage', full_name='MyType.StrMessage', index=2,
      number=3, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value=_b(""),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=16,
  serialized_end=72,
)


_MYTYPE1 = _descriptor.Descriptor(
  name='MyType1',
  full_name='MyType1',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='id', full_name='MyType1.id', index=0,
      number=1, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='longId', full_name='MyType1.longId', index=1,
      number=2, type=3, cpp_type=2, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='StrMessage', full_name='MyType1.StrMessage', index=2,
      number=3, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value=_b(""),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=74,
  serialized_end=131,
)


_MYTYPE2 = _descriptor.Descriptor(
  name='MyType2',
  full_name='MyType2',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='id', full_name='MyType2.id', index=0,
      number=1, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='longId', full_name='MyType2.longId', index=1,
      number=2, type=3, cpp_type=2, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='StrMessage', full_name='MyType2.StrMessage', index=2,
      number=3, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value=_b(""),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=133,
  serialized_end=190,
)


_MYTYPE3 = _descriptor.Descriptor(
  name='MyType3',
  full_name='MyType3',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='id', full_name='MyType3.id', index=0,
      number=1, type=5, cpp_type=1, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='longId', full_name='MyType3.longId', index=1,
      number=2, type=3, cpp_type=2, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='StrMessage', full_name='MyType3.StrMessage', index=2,
      number=3, type=12, cpp_type=9, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=192,
  serialized_end=249,
)


_MYTYPEARRAY = _descriptor.Descriptor(
  name='MyTypeArray',
  full_name='MyTypeArray',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='t', full_name='MyTypeArray.t', index=0,
      number=1, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='t1', full_name='MyTypeArray.t1', index=1,
      number=2, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='t2', full_name='MyTypeArray.t2', index=2,
      number=3, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='t3', full_name='MyTypeArray.t3', index=3,
      number=4, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=251,
  serialized_end=347,
)


_TESTREQUIREDFIELD = _descriptor.Descriptor(
  name='TestRequiredField',
  full_name='TestRequiredField',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='val', full_name='TestRequiredField.val', index=0,
      number=1, type=11, cpp_type=10, label=2,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=349,
  serialized_end=390,
)

_MYTYPEARRAY.fields_by_name['t'].message_type = _MYTYPE
_MYTYPEARRAY.fields_by_name['t1'].message_type = _MYTYPE
_MYTYPEARRAY.fields_by_name['t2'].message_type = _MYTYPE
_MYTYPEARRAY.fields_by_name['t3'].message_type = _MYTYPE
_TESTREQUIREDFIELD.fields_by_name['val'].message_type = _MYTYPE
DESCRIPTOR.message_types_by_name['MyType'] = _MYTYPE
DESCRIPTOR.message_types_by_name['MyType1'] = _MYTYPE1
DESCRIPTOR.message_types_by_name['MyType2'] = _MYTYPE2
DESCRIPTOR.message_types_by_name['MyType3'] = _MYTYPE3
DESCRIPTOR.message_types_by_name['MyTypeArray'] = _MYTYPEARRAY
DESCRIPTOR.message_types_by_name['TestRequiredField'] = _TESTREQUIREDFIELD

MyType = _reflection.GeneratedProtocolMessageType('MyType', (_message.Message,), dict(
  DESCRIPTOR = _MYTYPE,
  __module__ = 'mytype_pb2'
  # @@protoc_insertion_point(class_scope:MyType)
  ))
_sym_db.RegisterMessage(MyType)

MyType1 = _reflection.GeneratedProtocolMessageType('MyType1', (_message.Message,), dict(
  DESCRIPTOR = _MYTYPE1,
  __module__ = 'mytype_pb2'
  # @@protoc_insertion_point(class_scope:MyType1)
  ))
_sym_db.RegisterMessage(MyType1)

MyType2 = _reflection.GeneratedProtocolMessageType('MyType2', (_message.Message,), dict(
  DESCRIPTOR = _MYTYPE2,
  __module__ = 'mytype_pb2'
  # @@protoc_insertion_point(class_scope:MyType2)
  ))
_sym_db.RegisterMessage(MyType2)

MyType3 = _reflection.GeneratedProtocolMessageType('MyType3', (_message.Message,), dict(
  DESCRIPTOR = _MYTYPE3,
  __module__ = 'mytype_pb2'
  # @@protoc_insertion_point(class_scope:MyType3)
  ))
_sym_db.RegisterMessage(MyType3)

MyTypeArray = _reflection.GeneratedProtocolMessageType('MyTypeArray', (_message.Message,), dict(
  DESCRIPTOR = _MYTYPEARRAY,
  __module__ = 'mytype_pb2'
  # @@protoc_insertion_point(class_scope:MyTypeArray)
  ))
_sym_db.RegisterMessage(MyTypeArray)

TestRequiredField = _reflection.GeneratedProtocolMessageType('TestRequiredField', (_message.Message,), dict(
  DESCRIPTOR = _TESTREQUIREDFIELD,
  __module__ = 'mytype_pb2'
  # @@protoc_insertion_point(class_scope:TestRequiredField)
  ))
_sym_db.RegisterMessage(TestRequiredField)


# @@protoc_insertion_point(module_scope)
