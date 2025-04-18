// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: GameObject.proto

#include "GameObject.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG
namespace Protocol {
constexpr C_CREATE::C_CREATE(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : scene_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string)
  , layer_(0u)
  , create_id_(0u){}
struct C_CREATEDefaultTypeInternal {
  constexpr C_CREATEDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~C_CREATEDefaultTypeInternal() {}
  union {
    C_CREATE _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT C_CREATEDefaultTypeInternal _C_CREATE_default_instance_;
constexpr S_CREATE::S_CREATE(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : scene_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string)
  , state_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string)
  , layer_(0u)
  , id_(0u)
  , create_id_(0u)
  , anim_idx_(0u){}
struct S_CREATEDefaultTypeInternal {
  constexpr S_CREATEDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~S_CREATEDefaultTypeInternal() {}
  union {
    S_CREATE _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT S_CREATEDefaultTypeInternal _S_CREATE_default_instance_;
constexpr S_DELETE::S_DELETE(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : scene_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string)
  , layer_(0u)
  , delete_id_(0u){}
struct S_DELETEDefaultTypeInternal {
  constexpr S_DELETEDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~S_DELETEDefaultTypeInternal() {}
  union {
    S_DELETE _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT S_DELETEDefaultTypeInternal _S_DELETE_default_instance_;
}  // namespace Protocol
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_GameObject_2eproto[3];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_GameObject_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_GameObject_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_GameObject_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Protocol::C_CREATE, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::Protocol::C_CREATE, scene_),
  PROTOBUF_FIELD_OFFSET(::Protocol::C_CREATE, layer_),
  PROTOBUF_FIELD_OFFSET(::Protocol::C_CREATE, create_id_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Protocol::S_CREATE, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::Protocol::S_CREATE, scene_),
  PROTOBUF_FIELD_OFFSET(::Protocol::S_CREATE, layer_),
  PROTOBUF_FIELD_OFFSET(::Protocol::S_CREATE, id_),
  PROTOBUF_FIELD_OFFSET(::Protocol::S_CREATE, create_id_),
  PROTOBUF_FIELD_OFFSET(::Protocol::S_CREATE, state_),
  PROTOBUF_FIELD_OFFSET(::Protocol::S_CREATE, anim_idx_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Protocol::S_DELETE, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::Protocol::S_DELETE, scene_),
  PROTOBUF_FIELD_OFFSET(::Protocol::S_DELETE, layer_),
  PROTOBUF_FIELD_OFFSET(::Protocol::S_DELETE, delete_id_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::Protocol::C_CREATE)},
  { 8, -1, sizeof(::Protocol::S_CREATE)},
  { 19, -1, sizeof(::Protocol::S_DELETE)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::Protocol::_C_CREATE_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::Protocol::_S_CREATE_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::Protocol::_S_DELETE_default_instance_),
};

const char descriptor_table_protodef_GameObject_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\020GameObject.proto\022\010Protocol\";\n\010C_CREATE"
  "\022\r\n\005scene\030\001 \001(\t\022\r\n\005layer\030\002 \001(\r\022\021\n\tcreate"
  "_id\030\003 \001(\r\"h\n\010S_CREATE\022\r\n\005scene\030\001 \001(\t\022\r\n\005"
  "layer\030\002 \001(\r\022\n\n\002id\030\003 \001(\r\022\021\n\tcreate_id\030\004 \001"
  "(\r\022\r\n\005state\030\005 \001(\t\022\020\n\010anim_idx\030\006 \001(\r\";\n\010S"
  "_DELETE\022\r\n\005scene\030\001 \001(\t\022\r\n\005layer\030\002 \001(\r\022\021\n"
  "\tdelete_id\030\003 \001(\rb\006proto3"
  ;
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_GameObject_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_GameObject_2eproto = {
  false, false, 264, descriptor_table_protodef_GameObject_2eproto, "GameObject.proto", 
  &descriptor_table_GameObject_2eproto_once, nullptr, 0, 3,
  schemas, file_default_instances, TableStruct_GameObject_2eproto::offsets,
  file_level_metadata_GameObject_2eproto, file_level_enum_descriptors_GameObject_2eproto, file_level_service_descriptors_GameObject_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_GameObject_2eproto_getter() {
  return &descriptor_table_GameObject_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_GameObject_2eproto(&descriptor_table_GameObject_2eproto);
namespace Protocol {

// ===================================================================

class C_CREATE::_Internal {
 public:
};

C_CREATE::C_CREATE(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:Protocol.C_CREATE)
}
C_CREATE::C_CREATE(const C_CREATE& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  scene_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_scene().empty()) {
    scene_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_scene(), 
      GetArenaForAllocation());
  }
  ::memcpy(&layer_, &from.layer_,
    static_cast<size_t>(reinterpret_cast<char*>(&create_id_) -
    reinterpret_cast<char*>(&layer_)) + sizeof(create_id_));
  // @@protoc_insertion_point(copy_constructor:Protocol.C_CREATE)
}

void C_CREATE::SharedCtor() {
scene_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
    reinterpret_cast<char*>(&layer_) - reinterpret_cast<char*>(this)),
    0, static_cast<size_t>(reinterpret_cast<char*>(&create_id_) -
    reinterpret_cast<char*>(&layer_)) + sizeof(create_id_));
}

C_CREATE::~C_CREATE() {
  // @@protoc_insertion_point(destructor:Protocol.C_CREATE)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void C_CREATE::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  scene_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void C_CREATE::ArenaDtor(void* object) {
  C_CREATE* _this = reinterpret_cast< C_CREATE* >(object);
  (void)_this;
}
void C_CREATE::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void C_CREATE::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void C_CREATE::Clear() {
// @@protoc_insertion_point(message_clear_start:Protocol.C_CREATE)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  scene_.ClearToEmpty();
  ::memset(&layer_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&create_id_) -
      reinterpret_cast<char*>(&layer_)) + sizeof(create_id_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* C_CREATE::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // string scene = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          auto str = _internal_mutable_scene();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "Protocol.C_CREATE.scene"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // uint32 layer = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
          layer_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // uint32 create_id = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 24)) {
          create_id_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag == 0) || ((tag & 7) == 4)) {
          CHK_(ptr);
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* C_CREATE::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Protocol.C_CREATE)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string scene = 1;
  if (!this->scene().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_scene().data(), static_cast<int>(this->_internal_scene().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "Protocol.C_CREATE.scene");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_scene(), target);
  }

  // uint32 layer = 2;
  if (this->layer() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32ToArray(2, this->_internal_layer(), target);
  }

  // uint32 create_id = 3;
  if (this->create_id() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32ToArray(3, this->_internal_create_id(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Protocol.C_CREATE)
  return target;
}

size_t C_CREATE::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Protocol.C_CREATE)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string scene = 1;
  if (!this->scene().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_scene());
  }

  // uint32 layer = 2;
  if (this->layer() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32Size(
        this->_internal_layer());
  }

  // uint32 create_id = 3;
  if (this->create_id() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32Size(
        this->_internal_create_id());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void C_CREATE::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:Protocol.C_CREATE)
  GOOGLE_DCHECK_NE(&from, this);
  const C_CREATE* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<C_CREATE>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:Protocol.C_CREATE)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:Protocol.C_CREATE)
    MergeFrom(*source);
  }
}

void C_CREATE::MergeFrom(const C_CREATE& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:Protocol.C_CREATE)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from.scene().empty()) {
    _internal_set_scene(from._internal_scene());
  }
  if (from.layer() != 0) {
    _internal_set_layer(from._internal_layer());
  }
  if (from.create_id() != 0) {
    _internal_set_create_id(from._internal_create_id());
  }
}

void C_CREATE::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:Protocol.C_CREATE)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void C_CREATE::CopyFrom(const C_CREATE& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Protocol.C_CREATE)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool C_CREATE::IsInitialized() const {
  return true;
}

void C_CREATE::InternalSwap(C_CREATE* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &scene_, GetArenaForAllocation(),
      &other->scene_, other->GetArenaForAllocation()
  );
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(C_CREATE, create_id_)
      + sizeof(C_CREATE::create_id_)
      - PROTOBUF_FIELD_OFFSET(C_CREATE, layer_)>(
          reinterpret_cast<char*>(&layer_),
          reinterpret_cast<char*>(&other->layer_));
}

::PROTOBUF_NAMESPACE_ID::Metadata C_CREATE::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_GameObject_2eproto_getter, &descriptor_table_GameObject_2eproto_once,
      file_level_metadata_GameObject_2eproto[0]);
}

// ===================================================================

class S_CREATE::_Internal {
 public:
};

S_CREATE::S_CREATE(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:Protocol.S_CREATE)
}
S_CREATE::S_CREATE(const S_CREATE& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  scene_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_scene().empty()) {
    scene_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_scene(), 
      GetArenaForAllocation());
  }
  state_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_state().empty()) {
    state_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_state(), 
      GetArenaForAllocation());
  }
  ::memcpy(&layer_, &from.layer_,
    static_cast<size_t>(reinterpret_cast<char*>(&anim_idx_) -
    reinterpret_cast<char*>(&layer_)) + sizeof(anim_idx_));
  // @@protoc_insertion_point(copy_constructor:Protocol.S_CREATE)
}

void S_CREATE::SharedCtor() {
scene_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
state_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
    reinterpret_cast<char*>(&layer_) - reinterpret_cast<char*>(this)),
    0, static_cast<size_t>(reinterpret_cast<char*>(&anim_idx_) -
    reinterpret_cast<char*>(&layer_)) + sizeof(anim_idx_));
}

S_CREATE::~S_CREATE() {
  // @@protoc_insertion_point(destructor:Protocol.S_CREATE)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void S_CREATE::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  scene_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  state_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void S_CREATE::ArenaDtor(void* object) {
  S_CREATE* _this = reinterpret_cast< S_CREATE* >(object);
  (void)_this;
}
void S_CREATE::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void S_CREATE::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void S_CREATE::Clear() {
// @@protoc_insertion_point(message_clear_start:Protocol.S_CREATE)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  scene_.ClearToEmpty();
  state_.ClearToEmpty();
  ::memset(&layer_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&anim_idx_) -
      reinterpret_cast<char*>(&layer_)) + sizeof(anim_idx_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* S_CREATE::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // string scene = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          auto str = _internal_mutable_scene();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "Protocol.S_CREATE.scene"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // uint32 layer = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
          layer_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // uint32 id = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 24)) {
          id_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // uint32 create_id = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 32)) {
          create_id_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // string state = 5;
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 42)) {
          auto str = _internal_mutable_state();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "Protocol.S_CREATE.state"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // uint32 anim_idx = 6;
      case 6:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 48)) {
          anim_idx_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag == 0) || ((tag & 7) == 4)) {
          CHK_(ptr);
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* S_CREATE::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Protocol.S_CREATE)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string scene = 1;
  if (!this->scene().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_scene().data(), static_cast<int>(this->_internal_scene().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "Protocol.S_CREATE.scene");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_scene(), target);
  }

  // uint32 layer = 2;
  if (this->layer() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32ToArray(2, this->_internal_layer(), target);
  }

  // uint32 id = 3;
  if (this->id() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32ToArray(3, this->_internal_id(), target);
  }

  // uint32 create_id = 4;
  if (this->create_id() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32ToArray(4, this->_internal_create_id(), target);
  }

  // string state = 5;
  if (!this->state().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_state().data(), static_cast<int>(this->_internal_state().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "Protocol.S_CREATE.state");
    target = stream->WriteStringMaybeAliased(
        5, this->_internal_state(), target);
  }

  // uint32 anim_idx = 6;
  if (this->anim_idx() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32ToArray(6, this->_internal_anim_idx(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Protocol.S_CREATE)
  return target;
}

size_t S_CREATE::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Protocol.S_CREATE)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string scene = 1;
  if (!this->scene().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_scene());
  }

  // string state = 5;
  if (!this->state().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_state());
  }

  // uint32 layer = 2;
  if (this->layer() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32Size(
        this->_internal_layer());
  }

  // uint32 id = 3;
  if (this->id() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32Size(
        this->_internal_id());
  }

  // uint32 create_id = 4;
  if (this->create_id() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32Size(
        this->_internal_create_id());
  }

  // uint32 anim_idx = 6;
  if (this->anim_idx() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32Size(
        this->_internal_anim_idx());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void S_CREATE::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:Protocol.S_CREATE)
  GOOGLE_DCHECK_NE(&from, this);
  const S_CREATE* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<S_CREATE>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:Protocol.S_CREATE)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:Protocol.S_CREATE)
    MergeFrom(*source);
  }
}

void S_CREATE::MergeFrom(const S_CREATE& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:Protocol.S_CREATE)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from.scene().empty()) {
    _internal_set_scene(from._internal_scene());
  }
  if (!from.state().empty()) {
    _internal_set_state(from._internal_state());
  }
  if (from.layer() != 0) {
    _internal_set_layer(from._internal_layer());
  }
  if (from.id() != 0) {
    _internal_set_id(from._internal_id());
  }
  if (from.create_id() != 0) {
    _internal_set_create_id(from._internal_create_id());
  }
  if (from.anim_idx() != 0) {
    _internal_set_anim_idx(from._internal_anim_idx());
  }
}

void S_CREATE::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:Protocol.S_CREATE)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void S_CREATE::CopyFrom(const S_CREATE& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Protocol.S_CREATE)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool S_CREATE::IsInitialized() const {
  return true;
}

void S_CREATE::InternalSwap(S_CREATE* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &scene_, GetArenaForAllocation(),
      &other->scene_, other->GetArenaForAllocation()
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &state_, GetArenaForAllocation(),
      &other->state_, other->GetArenaForAllocation()
  );
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(S_CREATE, anim_idx_)
      + sizeof(S_CREATE::anim_idx_)
      - PROTOBUF_FIELD_OFFSET(S_CREATE, layer_)>(
          reinterpret_cast<char*>(&layer_),
          reinterpret_cast<char*>(&other->layer_));
}

::PROTOBUF_NAMESPACE_ID::Metadata S_CREATE::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_GameObject_2eproto_getter, &descriptor_table_GameObject_2eproto_once,
      file_level_metadata_GameObject_2eproto[1]);
}

// ===================================================================

class S_DELETE::_Internal {
 public:
};

S_DELETE::S_DELETE(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:Protocol.S_DELETE)
}
S_DELETE::S_DELETE(const S_DELETE& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  scene_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_scene().empty()) {
    scene_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_scene(), 
      GetArenaForAllocation());
  }
  ::memcpy(&layer_, &from.layer_,
    static_cast<size_t>(reinterpret_cast<char*>(&delete_id_) -
    reinterpret_cast<char*>(&layer_)) + sizeof(delete_id_));
  // @@protoc_insertion_point(copy_constructor:Protocol.S_DELETE)
}

void S_DELETE::SharedCtor() {
scene_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
    reinterpret_cast<char*>(&layer_) - reinterpret_cast<char*>(this)),
    0, static_cast<size_t>(reinterpret_cast<char*>(&delete_id_) -
    reinterpret_cast<char*>(&layer_)) + sizeof(delete_id_));
}

S_DELETE::~S_DELETE() {
  // @@protoc_insertion_point(destructor:Protocol.S_DELETE)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void S_DELETE::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  scene_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void S_DELETE::ArenaDtor(void* object) {
  S_DELETE* _this = reinterpret_cast< S_DELETE* >(object);
  (void)_this;
}
void S_DELETE::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void S_DELETE::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void S_DELETE::Clear() {
// @@protoc_insertion_point(message_clear_start:Protocol.S_DELETE)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  scene_.ClearToEmpty();
  ::memset(&layer_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&delete_id_) -
      reinterpret_cast<char*>(&layer_)) + sizeof(delete_id_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* S_DELETE::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // string scene = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          auto str = _internal_mutable_scene();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "Protocol.S_DELETE.scene"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // uint32 layer = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
          layer_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // uint32 delete_id = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 24)) {
          delete_id_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag == 0) || ((tag & 7) == 4)) {
          CHK_(ptr);
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* S_DELETE::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Protocol.S_DELETE)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string scene = 1;
  if (!this->scene().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_scene().data(), static_cast<int>(this->_internal_scene().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "Protocol.S_DELETE.scene");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_scene(), target);
  }

  // uint32 layer = 2;
  if (this->layer() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32ToArray(2, this->_internal_layer(), target);
  }

  // uint32 delete_id = 3;
  if (this->delete_id() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32ToArray(3, this->_internal_delete_id(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Protocol.S_DELETE)
  return target;
}

size_t S_DELETE::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Protocol.S_DELETE)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string scene = 1;
  if (!this->scene().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_scene());
  }

  // uint32 layer = 2;
  if (this->layer() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32Size(
        this->_internal_layer());
  }

  // uint32 delete_id = 3;
  if (this->delete_id() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32Size(
        this->_internal_delete_id());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void S_DELETE::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:Protocol.S_DELETE)
  GOOGLE_DCHECK_NE(&from, this);
  const S_DELETE* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<S_DELETE>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:Protocol.S_DELETE)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:Protocol.S_DELETE)
    MergeFrom(*source);
  }
}

void S_DELETE::MergeFrom(const S_DELETE& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:Protocol.S_DELETE)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from.scene().empty()) {
    _internal_set_scene(from._internal_scene());
  }
  if (from.layer() != 0) {
    _internal_set_layer(from._internal_layer());
  }
  if (from.delete_id() != 0) {
    _internal_set_delete_id(from._internal_delete_id());
  }
}

void S_DELETE::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:Protocol.S_DELETE)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void S_DELETE::CopyFrom(const S_DELETE& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Protocol.S_DELETE)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool S_DELETE::IsInitialized() const {
  return true;
}

void S_DELETE::InternalSwap(S_DELETE* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &scene_, GetArenaForAllocation(),
      &other->scene_, other->GetArenaForAllocation()
  );
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(S_DELETE, delete_id_)
      + sizeof(S_DELETE::delete_id_)
      - PROTOBUF_FIELD_OFFSET(S_DELETE, layer_)>(
          reinterpret_cast<char*>(&layer_),
          reinterpret_cast<char*>(&other->layer_));
}

::PROTOBUF_NAMESPACE_ID::Metadata S_DELETE::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_GameObject_2eproto_getter, &descriptor_table_GameObject_2eproto_once,
      file_level_metadata_GameObject_2eproto[2]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace Protocol
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::Protocol::C_CREATE* Arena::CreateMaybeMessage< ::Protocol::C_CREATE >(Arena* arena) {
  return Arena::CreateMessageInternal< ::Protocol::C_CREATE >(arena);
}
template<> PROTOBUF_NOINLINE ::Protocol::S_CREATE* Arena::CreateMaybeMessage< ::Protocol::S_CREATE >(Arena* arena) {
  return Arena::CreateMessageInternal< ::Protocol::S_CREATE >(arena);
}
template<> PROTOBUF_NOINLINE ::Protocol::S_DELETE* Arena::CreateMaybeMessage< ::Protocol::S_DELETE >(Arena* arena) {
  return Arena::CreateMessageInternal< ::Protocol::S_DELETE >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
