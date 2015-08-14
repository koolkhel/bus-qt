// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ui_message.proto

#ifndef PROTOBUF_ui_5fmessage_2eproto__INCLUDED
#define PROTOBUF_ui_5fmessage_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2006000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message_lite.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include "indigo_message.pb.h"
// @@protoc_insertion_point(includes)

namespace indigo {
namespace pb {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_ui_5fmessage_2eproto();
void protobuf_AssignDesc_ui_5fmessage_2eproto();
void protobuf_ShutdownFile_ui_5fmessage_2eproto();

class ui_message;

// ===================================================================

class ui_message : public ::google::protobuf::MessageLite {
 public:
  ui_message();
  virtual ~ui_message();

  ui_message(const ui_message& from);

  inline ui_message& operator=(const ui_message& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::std::string& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::std::string* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ui_message& default_instance();

  void Swap(ui_message* other);

  // implements Message ----------------------------------------------

  ui_message* New() const;
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from);
  void CopyFrom(const ui_message& from);
  void MergeFrom(const ui_message& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  void DiscardUnknownFields();
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::std::string GetTypeName() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional int32 data = 2 [default = 2];
  inline bool has_data() const;
  inline void clear_data();
  static const int kDataFieldNumber = 2;
  inline ::google::protobuf::int32 data() const;
  inline void set_data(::google::protobuf::int32 value);

  static const int kUiMessageOutFieldNumber = 200;
  static ::google::protobuf::internal::ExtensionIdentifier< ::indigo::pb::indigo_msg,
      ::google::protobuf::internal::MessageTypeTraits< ::indigo::pb::ui_message >, 11, false >
    ui_message_out;
  static const int kUiMessageInFieldNumber = 200;
  static ::google::protobuf::internal::ExtensionIdentifier< ::indigo::pb::internal_msg,
      ::google::protobuf::internal::MessageTypeTraits< ::indigo::pb::ui_message >, 11, false >
    ui_message_in;
  // @@protoc_insertion_point(class_scope:indigo.pb.ui_message)
 private:
  inline void set_has_data();
  inline void clear_has_data();

  ::std::string _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::int32 data_;
  friend void  protobuf_AddDesc_ui_5fmessage_2eproto();
  friend void protobuf_AssignDesc_ui_5fmessage_2eproto();
  friend void protobuf_ShutdownFile_ui_5fmessage_2eproto();

  void InitAsDefaultInstance();
  static ui_message* default_instance_;
};
// ===================================================================


// ===================================================================

// ui_message

// optional int32 data = 2 [default = 2];
inline bool ui_message::has_data() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ui_message::set_has_data() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ui_message::clear_has_data() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ui_message::clear_data() {
  data_ = 2;
  clear_has_data();
}
inline ::google::protobuf::int32 ui_message::data() const {
  // @@protoc_insertion_point(field_get:indigo.pb.ui_message.data)
  return data_;
}
inline void ui_message::set_data(::google::protobuf::int32 value) {
  set_has_data();
  data_ = value;
  // @@protoc_insertion_point(field_set:indigo.pb.ui_message.data)
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace pb
}  // namespace indigo

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_ui_5fmessage_2eproto__INCLUDED
