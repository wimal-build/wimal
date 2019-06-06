#ifndef LD64_MACH_O_COMPACT_UNWIND_ENCODING_H_
#define LD64_MACH_O_COMPACT_UNWIND_ENCODING_H_

#include <stdint.h>

typedef uint32_t compact_unwind_encoding_t;

enum {
    UNWIND_IS_NOT_FUNCTION_START = 0x80000000,
    UNWIND_HAS_LSDA = 0x40000000,
    UNWIND_PERSONALITY_MASK = 0x30000000,
};

enum {
    UNWIND_X86_MODE_MASK = 0x0F000000,
    UNWIND_X86_MODE_EBP_FRAME = 0x01000000,
    UNWIND_X86_MODE_STACK_IMMD = 0x02000000,
    UNWIND_X86_MODE_STACK_IND = 0x03000000,
    UNWIND_X86_MODE_DWARF = 0x04000000,

    UNWIND_X86_EBP_FRAME_REGISTERS = 0x00007FFF,
    UNWIND_X86_EBP_FRAME_OFFSET = 0x00FF0000,

    UNWIND_X86_FRAMELESS_STACK_SIZE = 0x00FF0000,
    UNWIND_X86_FRAMELESS_STACK_ADJUST = 0x0000E000,
    UNWIND_X86_FRAMELESS_STACK_REG_COUNT = 0x00001C00,
    UNWIND_X86_FRAMELESS_STACK_REG_PERMUTATION = 0x000003FF,

    UNWIND_X86_DWARF_SECTION_OFFSET = 0x00FFFFFF,
};

enum {
    UNWIND_X86_REG_NONE = 0,
    UNWIND_X86_REG_EBX = 1,
    UNWIND_X86_REG_ECX = 2,
    UNWIND_X86_REG_EDX = 3,
    UNWIND_X86_REG_EDI = 4,
    UNWIND_X86_REG_ESI = 5,
    UNWIND_X86_REG_EBP = 6,
};

enum {
    UNWIND_X86_64_MODE_MASK = 0x0F000000,
    UNWIND_X86_64_MODE_RBP_FRAME = 0x01000000,
    UNWIND_X86_64_MODE_STACK_IMMD = 0x02000000,
    UNWIND_X86_64_MODE_STACK_IND = 0x03000000,
    UNWIND_X86_64_MODE_DWARF = 0x04000000,

    UNWIND_X86_64_RBP_FRAME_REGISTERS = 0x00007FFF,
    UNWIND_X86_64_RBP_FRAME_OFFSET = 0x00FF0000,

    UNWIND_X86_64_FRAMELESS_STACK_SIZE = 0x00FF0000,
    UNWIND_X86_64_FRAMELESS_STACK_ADJUST = 0x0000E000,
    UNWIND_X86_64_FRAMELESS_STACK_REG_COUNT = 0x00001C00,
    UNWIND_X86_64_FRAMELESS_STACK_REG_PERMUTATION = 0x000003FF,

    UNWIND_X86_64_DWARF_SECTION_OFFSET = 0x00FFFFFF,
};

enum {
    UNWIND_X86_64_REG_NONE = 0,
    UNWIND_X86_64_REG_RBX = 1,
    UNWIND_X86_64_REG_R12 = 2,
    UNWIND_X86_64_REG_R13 = 3,
    UNWIND_X86_64_REG_R14 = 4,
    UNWIND_X86_64_REG_R15 = 5,
    UNWIND_X86_64_REG_RBP = 6,
};

enum {
    UNWIND_ARM64_MODE_MASK = 0x0F000000,
    UNWIND_ARM64_MODE_FRAMELESS = 0x02000000,
    UNWIND_ARM64_MODE_DWARF = 0x03000000,
    UNWIND_ARM64_MODE_FRAME = 0x04000000,

    UNWIND_ARM64_FRAME_X19_X20_PAIR = 0x00000001,
    UNWIND_ARM64_FRAME_X21_X22_PAIR = 0x00000002,
    UNWIND_ARM64_FRAME_X23_X24_PAIR = 0x00000004,
    UNWIND_ARM64_FRAME_X25_X26_PAIR = 0x00000008,
    UNWIND_ARM64_FRAME_X27_X28_PAIR = 0x00000010,
    UNWIND_ARM64_FRAME_D8_D9_PAIR = 0x00000100,
    UNWIND_ARM64_FRAME_D10_D11_PAIR = 0x00000200,
    UNWIND_ARM64_FRAME_D12_D13_PAIR = 0x00000400,
    UNWIND_ARM64_FRAME_D14_D15_PAIR = 0x00000800,

    UNWIND_ARM64_FRAMELESS_STACK_SIZE_MASK = 0x00FFF000,
    UNWIND_ARM64_DWARF_SECTION_OFFSET = 0x00FFFFFF,
};

#define UNWIND_SECTION_VERSION 1
struct unwind_info_section_header {
    uint32_t version;
    uint32_t commonEncodingsArraySectionOffset;
    uint32_t commonEncodingsArrayCount;
    uint32_t personalityArraySectionOffset;
    uint32_t personalityArrayCount;
    uint32_t indexSectionOffset;
    uint32_t indexCount;
};

struct unwind_info_section_header_index_entry {
    uint32_t functionOffset;
    uint32_t secondLevelPagesSectionOffset;
    uint32_t lsdaIndexArraySectionOffset;
};

struct unwind_info_section_header_lsda_index_entry {
    uint32_t functionOffset;
    uint32_t lsdaOffset;
};

struct unwind_info_regular_second_level_entry {
    uint32_t functionOffset;
    compact_unwind_encoding_t encoding;
};

#define UNWIND_SECOND_LEVEL_REGULAR 2
struct unwind_info_regular_second_level_page_header {
    uint32_t kind;
    uint16_t entryPageOffset;
    uint16_t entryCount;
};

#define UNWIND_SECOND_LEVEL_COMPRESSED 3
struct unwind_info_compressed_second_level_page_header {
    uint32_t kind;
    uint16_t entryPageOffset;
    uint16_t entryCount;
    uint16_t encodingsPageOffset;
    uint16_t encodingsCount;
};

#endif // LD64_MACH_O_COMPACT_UNWIND_ENCODING_H_
