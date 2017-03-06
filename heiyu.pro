QT += qml quick

CONFIG += c++11

SOURCES += main.cpp \
    google/protobuf/compiler/cpp/cpp_enum.cc \
    google/protobuf/compiler/cpp/cpp_enum_field.cc \
    google/protobuf/compiler/cpp/cpp_extension.cc \
    google/protobuf/compiler/cpp/cpp_field.cc \
    google/protobuf/compiler/cpp/cpp_file.cc \
    google/protobuf/compiler/cpp/cpp_generator.cc \
    google/protobuf/compiler/cpp/cpp_helpers.cc \
    google/protobuf/compiler/cpp/cpp_map_field.cc \
    google/protobuf/compiler/cpp/cpp_message.cc \
    google/protobuf/compiler/cpp/cpp_message_field.cc \
    google/protobuf/compiler/cpp/cpp_primitive_field.cc \
    google/protobuf/compiler/cpp/cpp_service.cc \
    google/protobuf/compiler/cpp/cpp_string_field.cc \
    google/protobuf/compiler/code_generator.cc \
    google/protobuf/compiler/command_line_interface.cc \
    google/protobuf/compiler/importer.cc \
    google/protobuf/compiler/parser.cc \
    google/protobuf/compiler/plugin.cc \
    google/protobuf/compiler/plugin.pb.cc \
    google/protobuf/compiler/subprocess.cc \
    google/protobuf/compiler/zip_writer.cc \
    google/protobuf/io/coded_stream.cc \
    google/protobuf/io/gzip_stream.cc \
    google/protobuf/io/printer.cc \
    google/protobuf/io/strtod.cc \
    google/protobuf/io/tokenizer.cc \
    google/protobuf/io/zero_copy_stream.cc \
    google/protobuf/io/zero_copy_stream_impl.cc \
    google/protobuf/io/zero_copy_stream_impl_lite.cc \
    google/protobuf/stubs/atomicops_internals_x86_gcc.cc \
    google/protobuf/stubs/atomicops_internals_x86_msvc.cc \
    google/protobuf/stubs/bytestream.cc \
    google/protobuf/stubs/common.cc \
    google/protobuf/stubs/int128.cc \
    google/protobuf/stubs/mathlimits.cc \
    google/protobuf/stubs/once.cc \
    google/protobuf/stubs/status.cc \
    google/protobuf/stubs/statusor.cc \
    google/protobuf/stubs/stringpiece.cc \
    google/protobuf/stubs/stringprintf.cc \
    google/protobuf/stubs/structurally_valid.cc \
    google/protobuf/stubs/strutil.cc \
    google/protobuf/stubs/substitute.cc \
    google/protobuf/stubs/time.cc \
    google/protobuf/util/internal/datapiece.cc \
    google/protobuf/util/internal/default_value_objectwriter.cc \
    google/protobuf/util/internal/error_listener.cc \
    google/protobuf/util/internal/field_mask_utility.cc \
    google/protobuf/util/internal/json_escaping.cc \
    google/protobuf/util/internal/json_objectwriter.cc \
    google/protobuf/util/internal/json_stream_parser.cc \
    google/protobuf/util/internal/object_writer.cc \
    google/protobuf/util/internal/proto_writer.cc \
    google/protobuf/util/internal/protostream_objectsource.cc \
    google/protobuf/util/internal/protostream_objectwriter.cc \
    google/protobuf/util/internal/type_info.cc \
    google/protobuf/util/internal/utility.cc \
    google/protobuf/util/field_comparator.cc \
    google/protobuf/util/field_mask_util.cc \
    google/protobuf/util/json_util.cc \
    google/protobuf/util/message_differencer.cc \
    google/protobuf/util/time_util.cc \
    google/protobuf/util/type_resolver_util.cc \
    google/protobuf/any.cc \
    google/protobuf/any.pb.cc \
    google/protobuf/api.pb.cc \
    google/protobuf/arena.cc \
    google/protobuf/arenastring.cc \
    google/protobuf/descriptor.cc \
    google/protobuf/descriptor.pb.cc \
    google/protobuf/descriptor_database.cc \
    google/protobuf/duration.pb.cc \
    google/protobuf/dynamic_message.cc \
    google/protobuf/empty.pb.cc \
    google/protobuf/extension_set.cc \
    google/protobuf/extension_set_heavy.cc \
    google/protobuf/field_mask.pb.cc \
    google/protobuf/generated_message_reflection.cc \
    google/protobuf/generated_message_util.cc \
    google/protobuf/map_field.cc \
    google/protobuf/message.cc \
    google/protobuf/message_lite.cc \
    google/protobuf/reflection_ops.cc \
    google/protobuf/repeated_field.cc \
    google/protobuf/service.cc \
    google/protobuf/source_context.pb.cc \
    google/protobuf/struct.pb.cc \
    google/protobuf/text_format.cc \
    google/protobuf/timestamp.pb.cc \
    google/protobuf/type.pb.cc \
    google/protobuf/unknown_field_set.cc \
    google/protobuf/wire_format.cc \
    google/protobuf/wire_format_lite.cc \
    google/protobuf/wrappers.pb.cc \
    net_db/buffer_yi.cxx \
    net_db/chat_message.pb.cc \
    net_db/leveldb_yi.cpp \
    net_db/lib_client.cpp \
    net_db/libev_timer.cxx \
    net_db/net_yi.cpp \
    net_db/netdb_yi.cpp \
    net_db/typemap.cxx

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
CC

DISTFILES += \
    net_db/root-ca.crt

HEADERS += \
    google/protobuf/compiler/cpp/cpp_enum.h \
    google/protobuf/compiler/cpp/cpp_enum_field.h \
    google/protobuf/compiler/cpp/cpp_extension.h \
    google/protobuf/compiler/cpp/cpp_field.h \
    google/protobuf/compiler/cpp/cpp_file.h \
    google/protobuf/compiler/cpp/cpp_generator.h \
    google/protobuf/compiler/cpp/cpp_helpers.h \
    google/protobuf/compiler/cpp/cpp_map_field.h \
    google/protobuf/compiler/cpp/cpp_message.h \
    google/protobuf/compiler/cpp/cpp_message_field.h \
    google/protobuf/compiler/cpp/cpp_options.h \
    google/protobuf/compiler/cpp/cpp_primitive_field.h \
    google/protobuf/compiler/cpp/cpp_service.h \
    google/protobuf/compiler/cpp/cpp_string_field.h \
    google/protobuf/compiler/code_generator.h \
    google/protobuf/compiler/command_line_interface.h \
    google/protobuf/compiler/importer.h \
    google/protobuf/compiler/package_info.h \
    google/protobuf/compiler/parser.h \
    google/protobuf/compiler/plugin.h \
    google/protobuf/compiler/plugin.pb.h \
    google/protobuf/compiler/subprocess.h \
    google/protobuf/compiler/zip_writer.h \
    google/protobuf/io/coded_stream.h \
    google/protobuf/io/coded_stream_inl.h \
    google/protobuf/io/gzip_stream.h \
    google/protobuf/io/package_info.h \
    google/protobuf/io/printer.h \
    google/protobuf/io/strtod.h \
    google/protobuf/io/tokenizer.h \
    google/protobuf/io/zero_copy_stream.h \
    google/protobuf/io/zero_copy_stream_impl.h \
    google/protobuf/io/zero_copy_stream_impl_lite.h \
    google/protobuf/stubs/atomic_sequence_num.h \
    google/protobuf/stubs/atomicops.h \
    google/protobuf/stubs/atomicops_internals_arm64_gcc.h \
    google/protobuf/stubs/atomicops_internals_arm_gcc.h \
    google/protobuf/stubs/atomicops_internals_arm_qnx.h \
    google/protobuf/stubs/atomicops_internals_atomicword_compat.h \
    google/protobuf/stubs/atomicops_internals_generic_c11_atomic.h \
    google/protobuf/stubs/atomicops_internals_generic_gcc.h \
    google/protobuf/stubs/atomicops_internals_macosx.h \
    google/protobuf/stubs/atomicops_internals_mips_gcc.h \
    google/protobuf/stubs/atomicops_internals_power.h \
    google/protobuf/stubs/atomicops_internals_ppc_gcc.h \
    google/protobuf/stubs/atomicops_internals_solaris.h \
    google/protobuf/stubs/atomicops_internals_tsan.h \
    google/protobuf/stubs/atomicops_internals_x86_gcc.h \
    google/protobuf/stubs/atomicops_internals_x86_msvc.h \
    google/protobuf/stubs/bytestream.h \
    google/protobuf/stubs/callback.h \
    google/protobuf/stubs/casts.h \
    google/protobuf/stubs/common.h \
    google/protobuf/stubs/fastmem.h \
    google/protobuf/stubs/hash.h \
    google/protobuf/stubs/int128.h \
    google/protobuf/stubs/logging.h \
    google/protobuf/stubs/macros.h \
    google/protobuf/stubs/map_util.h \
    google/protobuf/stubs/mathlimits.h \
    google/protobuf/stubs/mathutil.h \
    google/protobuf/stubs/mutex.h \
    google/protobuf/stubs/once.h \
    google/protobuf/stubs/platform_macros.h \
    google/protobuf/stubs/port.h \
    google/protobuf/stubs/scoped_ptr.h \
    google/protobuf/stubs/shared_ptr.h \
    google/protobuf/stubs/singleton.h \
    google/protobuf/stubs/status.h \
    google/protobuf/stubs/status_macros.h \
    google/protobuf/stubs/statusor.h \
    google/protobuf/stubs/stl_util.h \
    google/protobuf/stubs/stringpiece.h \
    google/protobuf/stubs/stringprintf.h \
    google/protobuf/stubs/strutil.h \
    google/protobuf/stubs/substitute.h \
    google/protobuf/stubs/template_util.h \
    google/protobuf/stubs/time.h \
    google/protobuf/stubs/type_traits.h \
    google/protobuf/util/internal/constants.h \
    google/protobuf/util/internal/datapiece.h \
    google/protobuf/util/internal/default_value_objectwriter.h \
    google/protobuf/util/internal/error_listener.h \
    google/protobuf/util/internal/expecting_objectwriter.h \
    google/protobuf/util/internal/field_mask_utility.h \
    google/protobuf/util/internal/json_escaping.h \
    google/protobuf/util/internal/json_objectwriter.h \
    google/protobuf/util/internal/json_stream_parser.h \
    google/protobuf/util/internal/location_tracker.h \
    google/protobuf/util/internal/mock_error_listener.h \
    google/protobuf/util/internal/object_location_tracker.h \
    google/protobuf/util/internal/object_source.h \
    google/protobuf/util/internal/object_writer.h \
    google/protobuf/util/internal/proto_writer.h \
    google/protobuf/util/internal/protostream_objectsource.h \
    google/protobuf/util/internal/protostream_objectwriter.h \
    google/protobuf/util/internal/structured_objectwriter.h \
    google/protobuf/util/internal/type_info.h \
    google/protobuf/util/internal/utility.h \
    google/protobuf/util/field_comparator.h \
    google/protobuf/util/field_mask_util.h \
    google/protobuf/util/json_util.h \
    google/protobuf/util/message_differencer.h \
    google/protobuf/util/package_info.h \
    google/protobuf/util/time_util.h \
    google/protobuf/util/type_resolver.h \
    google/protobuf/util/type_resolver_util.h \
    google/protobuf/any.h \
    google/protobuf/any.pb.h \
    google/protobuf/api.pb.h \
    google/protobuf/arena.h \
    google/protobuf/arenastring.h \
    google/protobuf/descriptor.h \
    google/protobuf/descriptor.pb.h \
    google/protobuf/descriptor_database.h \
    google/protobuf/duration.pb.h \
    google/protobuf/dynamic_message.h \
    google/protobuf/empty.pb.h \
    google/protobuf/extension_set.h \
    google/protobuf/field_mask.pb.h \
    google/protobuf/generated_enum_reflection.h \
    google/protobuf/generated_enum_util.h \
    google/protobuf/generated_message_reflection.h \
    google/protobuf/generated_message_util.h \
    google/protobuf/has_bits.h \
    google/protobuf/map.h \
    google/protobuf/map_entry.h \
    google/protobuf/map_entry_lite.h \
    google/protobuf/map_field.h \
    google/protobuf/map_field_inl.h \
    google/protobuf/map_field_lite.h \
    google/protobuf/map_type_handler.h \
    google/protobuf/message.h \
    google/protobuf/message_lite.h \
    google/protobuf/metadata.h \
    google/protobuf/package_info.h \
    google/protobuf/reflection.h \
    google/protobuf/reflection_internal.h \
    google/protobuf/reflection_ops.h \
    google/protobuf/repeated_field.h \
    google/protobuf/service.h \
    google/protobuf/source_context.pb.h \
    google/protobuf/struct.pb.h \
    google/protobuf/text_format.h \
    google/protobuf/timestamp.pb.h \
    google/protobuf/type.pb.h \
    google/protobuf/unknown_field_set.h \
    google/protobuf/wire_format.h \
    google/protobuf/wire_format_lite.h \
    google/protobuf/wire_format_lite_inl.h \
    google/protobuf/wrappers.pb.h \
    google/config.h \
    net_db/buffer_yi.h \
    net_db/buffer_yi_util.hpp \
    net_db/chat_message.pb.h \
    net_db/leveldb_yi.hpp \
    net_db/lib_client.h \
    net_db/libev_timer.hpp \
    net_db/macro.h \
    net_db/net_yi.h \
    net_db/netdb_yi.hpp \
    net_db/typemap.h \
    net_db/typemapre.h
