// https://opensource.apple.com/source/xnu/xnu-4903.221.2/EXTERNAL_HEADERS/mach-o/loader.h
#ifndef LD64_MACHO_LOADER_H_
#define LD64_MACHO_LOADER_H_

#include <llvm/Object/MachO.h>

using llvm::MachO::mach_header;

using llvm::MachO::MH_MAGIC;
using llvm::MachO::MH_CIGAM;

using llvm::MachO::mach_header_64;

using llvm::MachO::MH_MAGIC_64;
using llvm::MachO::MH_CIGAM_64;

using llvm::MachO::MH_OBJECT;
using llvm::MachO::MH_EXECUTE;
using llvm::MachO::MH_FVMLIB;
using llvm::MachO::MH_CORE;
using llvm::MachO::MH_PRELOAD;
using llvm::MachO::MH_DYLIB;
using llvm::MachO::MH_DYLINKER;
using llvm::MachO::MH_BUNDLE;
using llvm::MachO::MH_DYLIB_STUB;
using llvm::MachO::MH_DSYM;
using llvm::MachO::MH_KEXT_BUNDLE;

using llvm::MachO::MH_NOUNDEFS;
using llvm::MachO::MH_INCRLINK;
using llvm::MachO::MH_DYLDLINK;
using llvm::MachO::MH_BINDATLOAD;
using llvm::MachO::MH_PREBOUND;
using llvm::MachO::MH_SPLIT_SEGS;
using llvm::MachO::MH_LAZY_INIT;
using llvm::MachO::MH_TWOLEVEL;
using llvm::MachO::MH_FORCE_FLAT;
using llvm::MachO::MH_NOMULTIDEFS;
using llvm::MachO::MH_NOFIXPREBINDING;
using llvm::MachO::MH_PREBINDABLE;
using llvm::MachO::MH_ALLMODSBOUND;
using llvm::MachO::MH_SUBSECTIONS_VIA_SYMBOLS;
using llvm::MachO::MH_CANONICAL;
using llvm::MachO::MH_WEAK_DEFINES;
using llvm::MachO::MH_BINDS_TO_WEAK;
using llvm::MachO::MH_ALLOW_STACK_EXECUTION;
using llvm::MachO::MH_ROOT_SAFE;
using llvm::MachO::MH_SETUID_SAFE;
using llvm::MachO::MH_NO_REEXPORTED_DYLIBS;
using llvm::MachO::MH_PIE;
using llvm::MachO::MH_DEAD_STRIPPABLE_DYLIB;
using llvm::MachO::MH_HAS_TLV_DESCRIPTORS;
using llvm::MachO::MH_NO_HEAP_EXECUTION;
using llvm::MachO::MH_APP_EXTENSION_SAFE;
using llvm::MachO::MH_NLIST_OUTOFSYNC_WITH_DYLDINFO;

using llvm::MachO::load_command;

using llvm::MachO::LC_REQ_DYLD;

using llvm::MachO::LC_SEGMENT;
using llvm::MachO::LC_SYMTAB;
using llvm::MachO::LC_SYMSEG;
using llvm::MachO::LC_THREAD;
using llvm::MachO::LC_UNIXTHREAD;
using llvm::MachO::LC_LOADFVMLIB;
using llvm::MachO::LC_IDFVMLIB;
using llvm::MachO::LC_IDENT;
using llvm::MachO::LC_FVMFILE;
using llvm::MachO::LC_PREPAGE;
using llvm::MachO::LC_DYSYMTAB;
using llvm::MachO::LC_LOAD_DYLIB;
using llvm::MachO::LC_ID_DYLIB;
using llvm::MachO::LC_LOAD_DYLINKER;
using llvm::MachO::LC_ID_DYLINKER;
using llvm::MachO::LC_PREBOUND_DYLIB;
using llvm::MachO::LC_ROUTINES;
using llvm::MachO::LC_SUB_FRAMEWORK;
using llvm::MachO::LC_SUB_UMBRELLA;
using llvm::MachO::LC_SUB_CLIENT;
using llvm::MachO::LC_SUB_LIBRARY;
using llvm::MachO::LC_TWOLEVEL_HINTS;
using llvm::MachO::LC_PREBIND_CKSUM;
using llvm::MachO::LC_LOAD_WEAK_DYLIB;
using llvm::MachO::LC_SEGMENT_64;
using llvm::MachO::LC_ROUTINES_64;
using llvm::MachO::LC_UUID;
using llvm::MachO::LC_RPATH;
using llvm::MachO::LC_CODE_SIGNATURE;
using llvm::MachO::LC_SEGMENT_SPLIT_INFO;
using llvm::MachO::LC_REEXPORT_DYLIB;
using llvm::MachO::LC_LAZY_LOAD_DYLIB;
using llvm::MachO::LC_ENCRYPTION_INFO;
using llvm::MachO::LC_DYLD_INFO;
using llvm::MachO::LC_DYLD_INFO_ONLY;
using llvm::MachO::LC_LOAD_UPWARD_DYLIB;
using llvm::MachO::LC_VERSION_MIN_MACOSX;
using llvm::MachO::LC_VERSION_MIN_IPHONEOS;
using llvm::MachO::LC_FUNCTION_STARTS;
using llvm::MachO::LC_DYLD_ENVIRONMENT;
using llvm::MachO::LC_MAIN;
using llvm::MachO::LC_DATA_IN_CODE;
using llvm::MachO::LC_SOURCE_VERSION;
using llvm::MachO::LC_DYLIB_CODE_SIGN_DRS;
using llvm::MachO::LC_ENCRYPTION_INFO_64;
using llvm::MachO::LC_LINKER_OPTION;
using llvm::MachO::LC_LINKER_OPTIMIZATION_HINT;
using llvm::MachO::LC_VERSION_MIN_TVOS;
using llvm::MachO::LC_VERSION_MIN_WATCHOS;
using llvm::MachO::LC_NOTE;
using llvm::MachO::LC_BUILD_VERSION;

using llvm::MachO::segment_command;
using llvm::MachO::segment_command_64;

using llvm::MachO::SG_HIGHVM;
using llvm::MachO::SG_FVMLIB;
using llvm::MachO::SG_NORELOC;
using llvm::MachO::SG_PROTECTED_VERSION_1;

using llvm::MachO::section;
using llvm::MachO::section_64;

using llvm::MachO::SECTION_TYPE;
using llvm::MachO::SECTION_ATTRIBUTES;
using llvm::MachO::SECTION_ATTRIBUTES_USR;
using llvm::MachO::SECTION_ATTRIBUTES_SYS;

using llvm::MachO::S_REGULAR;
using llvm::MachO::S_ZEROFILL;
using llvm::MachO::S_CSTRING_LITERALS;
using llvm::MachO::S_4BYTE_LITERALS;
using llvm::MachO::S_8BYTE_LITERALS;
using llvm::MachO::S_LITERAL_POINTERS;
using llvm::MachO::S_NON_LAZY_SYMBOL_POINTERS;
using llvm::MachO::S_LAZY_SYMBOL_POINTERS;
using llvm::MachO::S_SYMBOL_STUBS;
using llvm::MachO::S_MOD_INIT_FUNC_POINTERS;
using llvm::MachO::S_MOD_TERM_FUNC_POINTERS;
using llvm::MachO::S_COALESCED;
using llvm::MachO::S_GB_ZEROFILL;
using llvm::MachO::S_INTERPOSING;
using llvm::MachO::S_16BYTE_LITERALS;
using llvm::MachO::S_DTRACE_DOF;
using llvm::MachO::S_LAZY_DYLIB_SYMBOL_POINTERS;
using llvm::MachO::S_THREAD_LOCAL_REGULAR;
using llvm::MachO::S_THREAD_LOCAL_ZEROFILL;
using llvm::MachO::S_THREAD_LOCAL_VARIABLES;
using llvm::MachO::S_THREAD_LOCAL_VARIABLE_POINTERS;
using llvm::MachO::S_THREAD_LOCAL_INIT_FUNCTION_POINTERS;

using llvm::MachO::S_ATTR_PURE_INSTRUCTIONS;
using llvm::MachO::S_ATTR_NO_TOC;
using llvm::MachO::S_ATTR_STRIP_STATIC_SYMS;
using llvm::MachO::S_ATTR_NO_DEAD_STRIP;
using llvm::MachO::S_ATTR_LIVE_SUPPORT;
using llvm::MachO::S_ATTR_SELF_MODIFYING_CODE;

using llvm::MachO::S_ATTR_DEBUG;
using llvm::MachO::S_ATTR_SOME_INSTRUCTIONS;
using llvm::MachO::S_ATTR_EXT_RELOC;
using llvm::MachO::S_ATTR_LOC_RELOC;

union lc_str {
    uint32_t offset;
};

struct dylib {
    union lc_str name;
    uint32_t timestamp;
    uint32_t current_version;
    uint32_t compatibility_version;
};

struct dylib_command {
    uint32_t cmd;
    uint32_t cmdsize;
    struct dylib dylib;
};

struct sub_framework_command {
    uint32_t cmd;
    uint32_t cmdsize;
    union lc_str umbrella;
};

struct sub_client_command {
    uint32_t cmd;
    uint32_t cmdsize;
    union lc_str client;
};

struct sub_umbrella_command {
    uint32_t cmd;
    uint32_t cmdsize;
    union lc_str sub_umbrella;
};

struct sub_library_command {
    uint32_t cmd;
    uint32_t cmdsize;
    union lc_str sub_library;
};

struct dylinker_command {
    uint32_t cmd;
    uint32_t cmdsize;
    union lc_str name;
};

using llvm::MachO::thread_command;

using llvm::MachO::routines_command;
using llvm::MachO::routines_command_64;

using llvm::MachO::symtab_command;

using llvm::MachO::dysymtab_command;

using llvm::MachO::INDIRECT_SYMBOL_LOCAL;
using llvm::MachO::INDIRECT_SYMBOL_ABS;

using llvm::MachO::dylib_table_of_contents;

using llvm::MachO::dylib_module;

using llvm::MachO::dylib_module_64;

using llvm::MachO::dylib_reference;

using llvm::MachO::twolevel_hints_command;

using llvm::MachO::twolevel_hint;

using llvm::MachO::uuid_command;

struct rpath_command {
    uint32_t cmd;
    uint32_t cmdsize;
    union lc_str path;
};

using llvm::MachO::linkedit_data_command;

using llvm::MachO::encryption_info_command;

using llvm::MachO::PLATFORM_MACOS;
using llvm::MachO::PLATFORM_IOS;
using llvm::MachO::PLATFORM_TVOS;
using llvm::MachO::PLATFORM_WATCHOS;
using llvm::MachO::PLATFORM_BRIDGEOS;
using llvm::MachO::PLATFORM_IOSSIMULATOR;
using llvm::MachO::PLATFORM_TVOSSIMULATOR;
using llvm::MachO::PLATFORM_WATCHOSSIMULATOR;

using llvm::MachO::TOOL_CLANG;
using llvm::MachO::TOOL_SWIFT;
using llvm::MachO::TOOL_LD;

using llvm::MachO::REBASE_TYPE_POINTER;
using llvm::MachO::REBASE_TYPE_TEXT_ABSOLUTE32;
using llvm::MachO::REBASE_TYPE_TEXT_PCREL32;

using llvm::MachO::REBASE_OPCODE_MASK;
using llvm::MachO::REBASE_IMMEDIATE_MASK;
using llvm::MachO::REBASE_OPCODE_DONE;
using llvm::MachO::REBASE_OPCODE_SET_TYPE_IMM;
using llvm::MachO::REBASE_OPCODE_SET_SEGMENT_AND_OFFSET_ULEB;
using llvm::MachO::REBASE_OPCODE_ADD_ADDR_ULEB;
using llvm::MachO::REBASE_OPCODE_ADD_ADDR_IMM_SCALED;
using llvm::MachO::REBASE_OPCODE_DO_REBASE_IMM_TIMES;
using llvm::MachO::REBASE_OPCODE_DO_REBASE_ULEB_TIMES;
using llvm::MachO::REBASE_OPCODE_DO_REBASE_ADD_ADDR_ULEB;
using llvm::MachO::REBASE_OPCODE_DO_REBASE_ULEB_TIMES_SKIPPING_ULEB;

using llvm::MachO::BIND_TYPE_POINTER;
using llvm::MachO::BIND_TYPE_TEXT_ABSOLUTE32;
using llvm::MachO::BIND_TYPE_TEXT_PCREL32;

using llvm::MachO::BIND_SPECIAL_DYLIB_SELF;
using llvm::MachO::BIND_SPECIAL_DYLIB_MAIN_EXECUTABLE;
using llvm::MachO::BIND_SPECIAL_DYLIB_FLAT_LOOKUP;

using llvm::MachO::BIND_SYMBOL_FLAGS_WEAK_IMPORT;
using llvm::MachO::BIND_SYMBOL_FLAGS_NON_WEAK_DEFINITION;

using llvm::MachO::BIND_OPCODE_MASK;
using llvm::MachO::BIND_IMMEDIATE_MASK;
using llvm::MachO::BIND_OPCODE_DONE;
using llvm::MachO::BIND_OPCODE_SET_DYLIB_ORDINAL_IMM;
using llvm::MachO::BIND_OPCODE_SET_DYLIB_ORDINAL_ULEB;
using llvm::MachO::BIND_OPCODE_SET_DYLIB_SPECIAL_IMM;
using llvm::MachO::BIND_OPCODE_SET_SYMBOL_TRAILING_FLAGS_IMM;
using llvm::MachO::BIND_OPCODE_SET_TYPE_IMM;
using llvm::MachO::BIND_OPCODE_SET_ADDEND_SLEB;
using llvm::MachO::BIND_OPCODE_SET_SEGMENT_AND_OFFSET_ULEB;
using llvm::MachO::BIND_OPCODE_ADD_ADDR_ULEB;
using llvm::MachO::BIND_OPCODE_DO_BIND;
using llvm::MachO::BIND_OPCODE_DO_BIND_ADD_ADDR_ULEB;
using llvm::MachO::BIND_OPCODE_DO_BIND_ADD_ADDR_IMM_SCALED;
using llvm::MachO::BIND_OPCODE_DO_BIND_ULEB_TIMES_SKIPPING_ULEB;

using llvm::MachO::EXPORT_SYMBOL_FLAGS_KIND_MASK;
using llvm::MachO::EXPORT_SYMBOL_FLAGS_KIND_REGULAR;
using llvm::MachO::EXPORT_SYMBOL_FLAGS_KIND_THREAD_LOCAL;
using llvm::MachO::EXPORT_SYMBOL_FLAGS_KIND_ABSOLUTE;
using llvm::MachO::EXPORT_SYMBOL_FLAGS_WEAK_DEFINITION;
using llvm::MachO::EXPORT_SYMBOL_FLAGS_REEXPORT;
using llvm::MachO::EXPORT_SYMBOL_FLAGS_STUB_AND_RESOLVER;

using llvm::MachO::DICE_KIND_DATA;
using llvm::MachO::DICE_KIND_JUMP_TABLE8;
using llvm::MachO::DICE_KIND_JUMP_TABLE16;
using llvm::MachO::DICE_KIND_JUMP_TABLE32;
using llvm::MachO::DICE_KIND_ABS_JUMP_TABLE32;

#endif // _MACHO_LOADER_H_
