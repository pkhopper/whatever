// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: mytype.proto

#ifndef PROTOBUF_mytype_2eproto__INCLUDED
#define PROTOBUF_mytype_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3000000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3000000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_mytype_2eproto();
void protobuf_AssignDesc_mytype_2eproto();
void protobuf_ShutdownFile_mytype_2eproto();

class MyType;

// ===================================================================

class MyType : public ::google::protobuf::Message {
 public:
  MyType();
  virtual ~MyType();

  MyType(const MyType& from);

  inline MyType& operator=(const MyType& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const MyType& default_instance();

  void Swap(MyType* other);

  // implements Message ----------------------------------------------

  inline MyType* New() const { return New(NULL); }

  MyType* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const MyType& from);
  void MergeFrom(const MyType& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(MyType* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required int32 id = 1;
  inline bool has_id() const;
  inline void clear_id();
  static const int kIdFieldNumber = 1;
  inline ::google::protobuf::int32 id() const;
  inline void set_id(::google::protobuf::int32 value);

  // required int64 longId = 2;
  inline bool has_longid() const;
  inline void clear_longid();
  static const int kLongIdFieldNumber = 2;
  inline ::google::protobuf::int64 longid() const;
  inline void set_longid(::google::protobuf::int64 value);

  // optional bytes StrMessage = 3;
  inline bool has_strmessage() const;
  inline void clear_strmessage();
  static const int kStrMessageFieldNumber = 3;
  inline const ::std::string& strmessage() const;
  inline void set_strmessage(const ::std::string& value);
  inline void set_strmessage(const char* value);
  inline void set_strmessage(const void* value, size_t size);
  inline ::std::string* mutable_strmessage();
  inline ::std::string* release_strmessage();
  inline void set_allocated_strmessage(::std::string* strmessage);

  // @@protoc_insertion_point(class_scope:MyType)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_longid();
  inline void clear_has_longid();
  inline void set_has_strmessage();
  inline void clear_has_strmessage();

  // helper for ByteSize()
  int RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::int64 longid_;
  ::google::protobuf::internal::ArenaStringPtr strmessage_;
  ::google::protobuf::int32 id_;
  friend void  protobuf_AddDesc_mytype_2eproto();
  friend void protobuf_AssignDesc_mytype_2eproto();
  friend void protobuf_ShutdownFile_mytype_2eproto();

  void InitAsDefaultInstance();
  static MyType* default_instance_;
};
// ===================================================================


// ===================================================================

// MyType

// required int32 id = 1;
inline bool MyType::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void MyType::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void MyType::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void MyType::clear_id() {
  id_ = 0;
  clear_has_id();
}
inline ::google::protobuf::int32 MyType::id() const {
  // @@protoc_insertion_point(field_get:MyType.id)
  return id_;
}
inline void MyType::set_id(::google::protobuf::int32 value) {
  set_has_id();
  id_ = value;
  // @@protoc_insertion_point(field_set:MyType.id)
}

// required int64 longId = 2;
inline bool MyType::has_longid() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void MyType::set_has_longid() {
  _has_bits_[0] |= 0x00000002u;
}
inline void MyType::clear_has_longid() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void MyType::clear_longid() {
  longid_ = GOOGLE_LONGLONG(0);
  clear_has_longid();
}
inline ::google::protobuf::int64 MyType::longid() const {
  // @@protoc_insertion_point(field_get:MyType.longId)
  return longid_;
}
inline void MyType::set_longid(::google::protobuf::int64 value) {
  set_has_longid();
  longid_ = value;
  // @@protoc_insertion_point(field_set:MyType.longId)
}

// optional bytes StrMessage = 3;
inline bool MyType::has_strmessage() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void MyType::set_has_strmessage() {
  _has_bits_[0] |= 0x00000004u;
}
inline void MyType::clear_has_strmessage() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void MyType::clear_strmessage() {
  strmessage_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_strmessage();
}
inline const ::std::string& MyType::strmessage() const {
  // @@protoc_insertion_point(field_get:MyType.StrMessage)
  return strmessage_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void MyType::set_strmessage(const ::std::string& value) {
  set_has_strmessage();
  strmessage_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:MyType.StrMessage)
}
inline void MyType::set_strmessage(const char* value) {
  set_has_strmessage();
  strmessage_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:MyType.StrMessage)
}
inline void MyType::set_strmessage(const void* value, size_t size) {
  set_has_strmessage();
  strmessage_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:MyType.StrMessage)
}
inline ::std::string* MyType::mutable_strmessage() {
  set_has_strmessage();
  // @@protoc_insertion_point(field_mutable:MyType.StrMessage)
  return strmessage_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* MyType::release_strmessage() {
  clear_has_strmessage();
  return strmessage_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void MyType::set_allocated_strmessage(::std::string* strmessage) {
  if (strmessage != NULL) {
    set_has_strmessage();
  } else {
    clear_has_strmessage();
  }
  strmessage_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), strmessage);
  // @@protoc_insertion_point(field_set_allocated:MyType.StrMessage)
}


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace protobuf
}  // namespace google
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_mytype_2eproto__INCLUDED
