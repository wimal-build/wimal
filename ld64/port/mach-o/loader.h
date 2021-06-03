// https://opensource.apple.com/source/xnu/xnu-4903.221.2/EXTERNAL_HEADERS/mach-o/loader.h
#ifndef LD64_MACHO_LOADER_H_
#define LD64_MACHO_LOADER_H_

#include <stdint.h>

struct mach_header {
    uint32_t magic;
    uint32_t cputype;
    uint32_t cpusubtype;
    uint32_t filetype;
    uint32_t ncmds;
    uint32_t sizeofcmds;
    uint32_t flags;
};

enum : uint32_t {
    MH_MAGIC = 0xFEEDFACEu,
    MH_CIGAM = 0xCEFAEDFEu,
    MH_MAGIC_64 = 0xFEEDFACFu,
    MH_CIGAM_64 = 0xCFFAEDFEu,
    FAT_MAGIC = 0xCAFEBABEu,
    FAT_CIGAM = 0xBEBAFECAu,
    FAT_MAGIC_64 = 0xCAFEBABFu,
    FAT_CIGAM_64 = 0xBFBAFECAu
};

struct mach_header_64 {
    uint32_t magic;
    uint32_t cputype;
    uint32_t cpusubtype;
    uint32_t filetype;
    uint32_t ncmds;
    uint32_t sizeofcmds;
    uint32_t flags;
    uint32_t reserved;
};

enum HeaderFileType {
    MH_OBJECT = 0x1u,
    MH_EXECUTE = 0x2u,
    MH_FVMLIB = 0x3u,
    MH_CORE = 0x4u,
    MH_PRELOAD = 0x5u,
    MH_DYLIB = 0x6u,
    MH_DYLINKER = 0x7u,
    MH_BUNDLE = 0x8u,
    MH_DYLIB_STUB = 0x9u,
    MH_DSYM = 0xAu,
    MH_KEXT_BUNDLE = 0xBu
};

enum : uint32_t {
    MH_NOUNDEFS = 0x00000001u,
    MH_INCRLINK = 0x00000002u,
    MH_DYLDLINK = 0x00000004u,
    MH_BINDATLOAD = 0x00000008u,
    MH_PREBOUND = 0x00000010u,
    MH_SPLIT_SEGS = 0x00000020u,
    MH_LAZY_INIT = 0x00000040u,
    MH_TWOLEVEL = 0x00000080u,
    MH_FORCE_FLAT = 0x00000100u,
    MH_NOMULTIDEFS = 0x00000200u,
    MH_NOFIXPREBINDING = 0x00000400u,
    MH_PREBINDABLE = 0x00000800u,
    MH_ALLMODSBOUND = 0x00001000u,
    MH_SUBSECTIONS_VIA_SYMBOLS = 0x00002000u,
    MH_CANONICAL = 0x00004000u,
    MH_WEAK_DEFINES = 0x00008000u,
    MH_BINDS_TO_WEAK = 0x00010000u,
    MH_ALLOW_STACK_EXECUTION = 0x00020000u,
    MH_ROOT_SAFE = 0x00040000u,
    MH_SETUID_SAFE = 0x00080000u,
    MH_NO_REEXPORTED_DYLIBS = 0x00100000u,
    MH_PIE = 0x00200000u,
    MH_DEAD_STRIPPABLE_DYLIB = 0x00400000u,
    MH_HAS_TLV_DESCRIPTORS = 0x00800000u,
    MH_NO_HEAP_EXECUTION = 0x01000000u,
    MH_APP_EXTENSION_SAFE = 0x02000000u,
    MH_NLIST_OUTOFSYNC_WITH_DYLDINFO = 0x04000000u,
    MH_SIM_SUPPORT = 0x08000000u,
    MH_DYLIB_IN_CACHE = 0x80000000u,
};

struct load_command {
    uint32_t cmd;
    uint32_t cmdsize;
};

enum  {
    LC_REQ_DYLD = 0x80000000u
};

enum {
    LC_SEGMENT = 0x00000001u,
    LC_SYMTAB = 0x00000002u,
    LC_SYMSEG = 0x00000003u,
    LC_THREAD = 0x00000004u,
    LC_UNIXTHREAD = 0x00000005u,
    LC_LOADFVMLIB = 0x00000006u,
    LC_IDFVMLIB = 0x00000007u,
    LC_IDENT = 0x00000008u,
    LC_FVMFILE = 0x00000009u,
    LC_PREPAGE = 0x0000000Au,
    LC_DYSYMTAB = 0x0000000Bu,
    LC_LOAD_DYLIB = 0x0000000Cu,
    LC_ID_DYLIB = 0x0000000Du,
    LC_LOAD_DYLINKER = 0x0000000Eu,
    LC_ID_DYLINKER = 0x0000000Fu,
    LC_PREBOUND_DYLIB = 0x00000010u,
    LC_ROUTINES = 0x00000011u,
    LC_SUB_FRAMEWORK = 0x00000012u,
    LC_SUB_UMBRELLA = 0x00000013u,
    LC_SUB_CLIENT = 0x00000014u,
    LC_SUB_LIBRARY = 0x00000015u,
    LC_TWOLEVEL_HINTS = 0x00000016u,
    LC_PREBIND_CKSUM = 0x00000017u,
    LC_LOAD_WEAK_DYLIB = 0x80000018u,
    LC_SEGMENT_64 = 0x00000019u,
    LC_ROUTINES_64 = 0x0000001Au,
    LC_UUID = 0x0000001Bu,
    LC_RPATH = 0x8000001Cu,
    LC_CODE_SIGNATURE = 0x0000001Du,
    LC_SEGMENT_SPLIT_INFO = 0x0000001Eu,
    LC_REEXPORT_DYLIB = 0x8000001Fu,
    LC_LAZY_LOAD_DYLIB = 0x00000020u,
    LC_ENCRYPTION_INFO = 0x00000021u,
    LC_DYLD_INFO = 0x00000022u,
    LC_DYLD_INFO_ONLY = 0x80000022u,
    LC_LOAD_UPWARD_DYLIB = 0x80000023u,
    LC_VERSION_MIN_MACOSX = 0x00000024u,
    LC_VERSION_MIN_IPHONEOS = 0x00000025u,
    LC_FUNCTION_STARTS = 0x00000026u,
    LC_DYLD_ENVIRONMENT = 0x00000027u,
    LC_MAIN = 0x80000028u,
    LC_DATA_IN_CODE = 0x00000029u,
    LC_SOURCE_VERSION = 0x0000002Au,
    LC_DYLIB_CODE_SIGN_DRS = 0x0000002Bu,
    LC_ENCRYPTION_INFO_64 = 0x0000002Cu,
    LC_LINKER_OPTION = 0x0000002Du,
    LC_LINKER_OPTIMIZATION_HINT = 0x0000002Eu,
    LC_VERSION_MIN_TVOS = 0x0000002Fu,
    LC_VERSION_MIN_WATCHOS = 0x00000030u,
    LC_NOTE = 0x00000031u,
    LC_BUILD_VERSION = 0x00000032u,
};

struct segment_command {
    uint32_t cmd;
    uint32_t cmdsize;
    char segname[16];
    uint32_t vmaddr;
    uint32_t vmsize;
    uint32_t fileoff;
    uint32_t filesize;
    uint32_t maxprot;
    uint32_t initprot;
    uint32_t nsects;
    uint32_t flags;
};

struct segment_command_64 {
    uint32_t cmd;
    uint32_t cmdsize;
    char segname[16];
    uint64_t vmaddr;
    uint64_t vmsize;
    uint64_t fileoff;
    uint64_t filesize;
    uint32_t maxprot;
    uint32_t initprot;
    uint32_t nsects;
    uint32_t flags;
};

enum : uint32_t {
    SG_HIGHVM = 0x1u,
    SG_FVMLIB = 0x2u,
    SG_NORELOC = 0x4u,
    SG_PROTECTED_VERSION_1 = 0x8u,
    SECTION_TYPE = 0x000000ffu,
    SECTION_ATTRIBUTES = 0xffffff00u,
    SECTION_ATTRIBUTES_USR = 0xff000000u,
    SECTION_ATTRIBUTES_SYS = 0x00ffff00u
};

struct section {
    char sectname[16];
    char segname[16];
    uint32_t addr;
    uint32_t size;
    uint32_t offset;
    uint32_t align;
    uint32_t reloff;
    uint32_t nreloc;
    uint32_t flags;
    uint32_t reserved1;
    uint32_t reserved2;
};

struct section_64 {
    char sectname[16];
    char segname[16];
    uint64_t addr;
    uint64_t size;
    uint32_t offset;
    uint32_t align;
    uint32_t reloff;
    uint32_t nreloc;
    uint32_t flags;
    uint32_t reserved1;
    uint32_t reserved2;
    uint32_t reserved3;
};

enum SectionType  {
    S_REGULAR = 0x00u,
    S_ZEROFILL = 0x01u,
    S_CSTRING_LITERALS = 0x02u,
    S_4BYTE_LITERALS = 0x03u,
    S_8BYTE_LITERALS = 0x04u,
    S_LITERAL_POINTERS = 0x05u,
    S_NON_LAZY_SYMBOL_POINTERS = 0x06u,
    S_LAZY_SYMBOL_POINTERS = 0x07u,
    S_SYMBOL_STUBS = 0x08u,
    S_MOD_INIT_FUNC_POINTERS = 0x09u,
    S_MOD_TERM_FUNC_POINTERS = 0x0au,
    S_COALESCED = 0x0bu,
    S_GB_ZEROFILL = 0x0cu,
    S_INTERPOSING = 0x0du,
    S_16BYTE_LITERALS = 0x0eu,
    S_DTRACE_DOF = 0x0fu,
    S_LAZY_DYLIB_SYMBOL_POINTERS = 0x10u,
    S_THREAD_LOCAL_REGULAR = 0x11u,
    S_THREAD_LOCAL_ZEROFILL = 0x12u,
    S_THREAD_LOCAL_VARIABLES = 0x13u,
    S_THREAD_LOCAL_VARIABLE_POINTERS = 0x14u,
    S_THREAD_LOCAL_INIT_FUNCTION_POINTERS = 0x15u,
    LAST_KNOWN_SECTION_TYPE = S_THREAD_LOCAL_INIT_FUNCTION_POINTERS
};

enum  {
    S_ATTR_PURE_INSTRUCTIONS = 0x80000000u,
    S_ATTR_NO_TOC = 0x40000000u,
    S_ATTR_STRIP_STATIC_SYMS = 0x20000000u,
    S_ATTR_NO_DEAD_STRIP = 0x10000000u,
    S_ATTR_LIVE_SUPPORT = 0x08000000u,
    S_ATTR_SELF_MODIFYING_CODE = 0x04000000u,
    S_ATTR_DEBUG = 0x02000000u,
    S_ATTR_SOME_INSTRUCTIONS = 0x00000400u,
    S_ATTR_EXT_RELOC = 0x00000200u,
    S_ATTR_LOC_RELOC = 0x00000100u,
    INDIRECT_SYMBOL_LOCAL = 0x80000000u,
    INDIRECT_SYMBOL_ABS = 0x40000000u
};

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

struct thread_command {
    uint32_t cmd;
    uint32_t cmdsize;
};

struct routines_command {
    uint32_t cmd;
    uint32_t cmdsize;
    uint32_t init_address;
    uint32_t init_module;
    uint32_t reserved1;
    uint32_t reserved2;
    uint32_t reserved3;
    uint32_t reserved4;
    uint32_t reserved5;
    uint32_t reserved6;
};

struct routines_command_64 {
    uint32_t cmd;
    uint32_t cmdsize;
    uint64_t init_address;
    uint64_t init_module;
    uint64_t reserved1;
    uint64_t reserved2;
    uint64_t reserved3;
    uint64_t reserved4;
    uint64_t reserved5;
    uint64_t reserved6;
};

struct symtab_command {
    uint32_t cmd;
    uint32_t cmdsize;
    uint32_t symoff;
    uint32_t nsyms;
    uint32_t stroff;
    uint32_t strsize;
};

struct dysymtab_command {
    uint32_t cmd;
    uint32_t cmdsize;
    uint32_t ilocalsym;
    uint32_t nlocalsym;
    uint32_t iextdefsym;
    uint32_t nextdefsym;
    uint32_t iundefsym;
    uint32_t nundefsym;
    uint32_t tocoff;
    uint32_t ntoc;
    uint32_t modtaboff;
    uint32_t nmodtab;
    uint32_t extrefsymoff;
    uint32_t nextrefsyms;
    uint32_t indirectsymoff;
    uint32_t nindirectsyms;
    uint32_t extreloff;
    uint32_t nextrel;
    uint32_t locreloff;
    uint32_t nlocrel;
};

struct dylib_table_of_contents {
    uint32_t symbol_index;
    uint32_t module_index;
};

struct dylib_module {
    uint32_t module_name;
    uint32_t iextdefsym;
    uint32_t nextdefsym;
    uint32_t irefsym;
    uint32_t nrefsym;
    uint32_t ilocalsym;
    uint32_t nlocalsym;
    uint32_t iextrel;
    uint32_t nextrel;
    uint32_t iinit_iterm;
    uint32_t ninit_nterm;
    uint32_t objc_module_info_addr;
    uint32_t objc_module_info_size;
};

struct dylib_module_64 {
    uint32_t module_name;
    uint32_t iextdefsym;
    uint32_t nextdefsym;
    uint32_t irefsym;
    uint32_t nrefsym;
    uint32_t ilocalsym;
    uint32_t nlocalsym;
    uint32_t iextrel;
    uint32_t nextrel;
    uint32_t iinit_iterm;
    uint32_t ninit_nterm;
    uint32_t objc_module_info_size;
    uint64_t objc_module_info_addr;
};

struct dylib_reference {
    uint32_t isym: 24, flags: 8;
};

struct twolevel_hints_command {
    uint32_t cmd;
    uint32_t cmdsize;
    uint32_t offset;
    uint32_t nhints;
};

struct twolevel_hint {
    uint32_t isub_image: 8, itoc: 24;
};

struct uuid_command {
    uint32_t cmd;
    uint32_t cmdsize;
    uint8_t uuid[16];
};

struct rpath_command {
    uint32_t cmd;
    uint32_t cmdsize;
    union lc_str path;
};

struct linkedit_data_command {
    uint32_t cmd;
    uint32_t cmdsize;
    uint32_t dataoff;
    uint32_t datasize;
};

struct encryption_info_command {
    uint32_t cmd;
    uint32_t cmdsize;
    uint32_t cryptoff;
    uint32_t cryptsize;
    uint32_t cryptid;
};

struct encryption_info_command_64 {
    uint32_t cmd;
    uint32_t cmdsize;
    uint32_t cryptoff;
    uint32_t cryptsize;
    uint32_t cryptid;
    uint32_t pad;
};

struct version_min_command {
    uint32_t cmd;
    uint32_t cmdsize;
    uint32_t version;
    uint32_t sdk;
};

struct build_tool_version {
    uint32_t tool;
    uint32_t version;
};

struct build_version_command {
    uint32_t cmd;
    uint32_t cmdsize;
    uint32_t platform;
    uint32_t minos;
    uint32_t sdk;
    uint32_t ntools;
};

struct dyld_info_command {
    uint32_t cmd;
    uint32_t cmdsize;
    uint32_t rebase_off;
    uint32_t rebase_size;
    uint32_t bind_off;
    uint32_t bind_size;
    uint32_t weak_bind_off;
    uint32_t weak_bind_size;
    uint32_t lazy_bind_off;
    uint32_t lazy_bind_size;
    uint32_t export_off;
    uint32_t export_size;
};

struct linker_option_command {
    uint32_t cmd;
    uint32_t cmdsize;
    uint32_t count;
};

struct entry_point_command {
    uint32_t cmd;
    uint32_t cmdsize;
    uint64_t entryoff;
    uint64_t stacksize;
};

struct data_in_code_entry {
    uint32_t offset;
    uint16_t length;
    uint16_t kind;
};

struct source_version_command {
    uint32_t cmd;
    uint32_t cmdsize;
    uint64_t version;
};

enum PlatformType {
    PLATFORM_MACOS = 1,
    PLATFORM_IOS = 2,
    PLATFORM_TVOS = 3,
    PLATFORM_WATCHOS = 4,
    PLATFORM_BRIDGEOS = 5,
    PLATFORM_MACCATALYST = 6,
    PLATFORM_IOSSIMULATOR = 7,
    PLATFORM_TVOSSIMULATOR = 8,
    PLATFORM_WATCHOSSIMULATOR = 9,
    PLATFORM_DRIVERKIT = 10,
};

enum {
    TOOL_CLANG = 1, TOOL_SWIFT = 2, TOOL_LD = 3
};

enum RebaseType {
    REBASE_TYPE_POINTER = 1u,
    REBASE_TYPE_TEXT_ABSOLUTE32 = 2u,
    REBASE_TYPE_TEXT_PCREL32 = 3u
};

enum {
    REBASE_OPCODE_MASK = 0xF0u, REBASE_IMMEDIATE_MASK = 0x0Fu
};

enum RebaseOpcode {
    REBASE_OPCODE_DONE = 0x00u,
    REBASE_OPCODE_SET_TYPE_IMM = 0x10u,
    REBASE_OPCODE_SET_SEGMENT_AND_OFFSET_ULEB = 0x20u,
    REBASE_OPCODE_ADD_ADDR_ULEB = 0x30u,
    REBASE_OPCODE_ADD_ADDR_IMM_SCALED = 0x40u,
    REBASE_OPCODE_DO_REBASE_IMM_TIMES = 0x50u,
    REBASE_OPCODE_DO_REBASE_ULEB_TIMES = 0x60u,
    REBASE_OPCODE_DO_REBASE_ADD_ADDR_ULEB = 0x70u,
    REBASE_OPCODE_DO_REBASE_ULEB_TIMES_SKIPPING_ULEB = 0x80u
};

enum BindType {
    BIND_TYPE_POINTER = 1u,
    BIND_TYPE_TEXT_ABSOLUTE32 = 2u,
    BIND_TYPE_TEXT_PCREL32 = 3u
};

enum BindSpecialDylib {
    BIND_SPECIAL_DYLIB_SELF = 0,
    BIND_SPECIAL_DYLIB_MAIN_EXECUTABLE = -1,
    BIND_SPECIAL_DYLIB_FLAT_LOOKUP = -2
};

enum {
    BIND_SYMBOL_FLAGS_WEAK_IMPORT = 0x1u,
    BIND_SYMBOL_FLAGS_NON_WEAK_DEFINITION = 0x8u,

    BIND_OPCODE_MASK = 0xF0u,
    BIND_IMMEDIATE_MASK = 0x0Fu
};

enum BindOpcode {
    BIND_OPCODE_DONE = 0x00u,
    BIND_OPCODE_SET_DYLIB_ORDINAL_IMM = 0x10u,
    BIND_OPCODE_SET_DYLIB_ORDINAL_ULEB = 0x20u,
    BIND_OPCODE_SET_DYLIB_SPECIAL_IMM = 0x30u,
    BIND_OPCODE_SET_SYMBOL_TRAILING_FLAGS_IMM = 0x40u,
    BIND_OPCODE_SET_TYPE_IMM = 0x50u,
    BIND_OPCODE_SET_ADDEND_SLEB = 0x60u,
    BIND_OPCODE_SET_SEGMENT_AND_OFFSET_ULEB = 0x70u,
    BIND_OPCODE_ADD_ADDR_ULEB = 0x80u,
    BIND_OPCODE_DO_BIND = 0x90u,
    BIND_OPCODE_DO_BIND_ADD_ADDR_ULEB = 0xA0u,
    BIND_OPCODE_DO_BIND_ADD_ADDR_IMM_SCALED = 0xB0u,
    BIND_OPCODE_DO_BIND_ULEB_TIMES_SKIPPING_ULEB = 0xC0u
};

enum {
    EXPORT_SYMBOL_FLAGS_KIND_MASK = 0x03u,
    EXPORT_SYMBOL_FLAGS_WEAK_DEFINITION = 0x04u,
    EXPORT_SYMBOL_FLAGS_REEXPORT = 0x08u,
    EXPORT_SYMBOL_FLAGS_STUB_AND_RESOLVER = 0x10u
};

enum ExportSymbolKind {
    EXPORT_SYMBOL_FLAGS_KIND_REGULAR = 0x00u,
    EXPORT_SYMBOL_FLAGS_KIND_THREAD_LOCAL = 0x01u,
    EXPORT_SYMBOL_FLAGS_KIND_ABSOLUTE = 0x02u
};

enum DataRegionType {
    DICE_KIND_DATA = 1u,
    DICE_KIND_JUMP_TABLE8 = 2u,
    DICE_KIND_JUMP_TABLE16 = 3u,
    DICE_KIND_JUMP_TABLE32 = 4u,
    DICE_KIND_ABS_JUMP_TABLE32 = 5u
};

#endif // _MACHO_LOADER_H_
