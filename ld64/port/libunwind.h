#ifndef LD64_LIBUNWIND_H_
#define LD64_LIBUNWIND_H_

#include <stdint.h>

typedef uintptr_t unw_word_t;

#if defined(__arm__)
typedef uint64_t unw_fpreg_t;
#else
typedef double unw_fpreg_t;
#endif

enum {
    UNW_ESUCCESS = 0,
    UNW_EUNSPEC = -6540,
    UNW_ENOMEM = -6541,
    UNW_EBADREG = -6542,
    UNW_EREADONLYREG = -6543,
    UNW_ESTOPUNWIND = -6544,
    UNW_EINVALIDIP = -6545,
    UNW_EBADFRAME = -6546,
    UNW_EINVAL = -6547,
    UNW_EBADVERSION = -6548,
    UNW_ENOINFO = -6549,
    UNW_ECROSSRASIGNING = -6550
};

enum {
    UNW_PPC_R0 = 0,
    UNW_PPC_R1 = 1,
    UNW_PPC_R2 = 2,
    UNW_PPC_R3 = 3,
    UNW_PPC_R4 = 4,
    UNW_PPC_R5 = 5,
    UNW_PPC_R6 = 6,
    UNW_PPC_R7 = 7,
    UNW_PPC_R8 = 8,
    UNW_PPC_R9 = 9,
    UNW_PPC_R10 = 10,
    UNW_PPC_R11 = 11,
    UNW_PPC_R12 = 12,
    UNW_PPC_R13 = 13,
    UNW_PPC_R14 = 14,
    UNW_PPC_R15 = 15,
    UNW_PPC_R16 = 16,
    UNW_PPC_R17 = 17,
    UNW_PPC_R18 = 18,
    UNW_PPC_R19 = 19,
    UNW_PPC_R20 = 20,
    UNW_PPC_R21 = 21,
    UNW_PPC_R22 = 22,
    UNW_PPC_R23 = 23,
    UNW_PPC_R24 = 24,
    UNW_PPC_R25 = 25,
    UNW_PPC_R26 = 26,
    UNW_PPC_R27 = 27,
    UNW_PPC_R28 = 28,
    UNW_PPC_R29 = 29,
    UNW_PPC_R30 = 30,
    UNW_PPC_R31 = 31,
    UNW_PPC_F0 = 32,
    UNW_PPC_F1 = 33,
    UNW_PPC_F2 = 34,
    UNW_PPC_F3 = 35,
    UNW_PPC_F4 = 36,
    UNW_PPC_F5 = 37,
    UNW_PPC_F6 = 38,
    UNW_PPC_F7 = 39,
    UNW_PPC_F8 = 40,
    UNW_PPC_F9 = 41,
    UNW_PPC_F10 = 42,
    UNW_PPC_F11 = 43,
    UNW_PPC_F12 = 44,
    UNW_PPC_F13 = 45,
    UNW_PPC_F14 = 46,
    UNW_PPC_F15 = 47,
    UNW_PPC_F16 = 48,
    UNW_PPC_F17 = 49,
    UNW_PPC_F18 = 50,
    UNW_PPC_F19 = 51,
    UNW_PPC_F20 = 52,
    UNW_PPC_F21 = 53,
    UNW_PPC_F22 = 54,
    UNW_PPC_F23 = 55,
    UNW_PPC_F24 = 56,
    UNW_PPC_F25 = 57,
    UNW_PPC_F26 = 58,
    UNW_PPC_F27 = 59,
    UNW_PPC_F28 = 60,
    UNW_PPC_F29 = 61,
    UNW_PPC_F30 = 62,
    UNW_PPC_F31 = 63,
    UNW_PPC_MQ = 64,
    UNW_PPC_LR = 65,
    UNW_PPC_CTR = 66,
    UNW_PPC_AP = 67,
    UNW_PPC_CR0 = 68,
    UNW_PPC_CR1 = 69,
    UNW_PPC_CR2 = 70,
    UNW_PPC_CR3 = 71,
    UNW_PPC_CR4 = 72,
    UNW_PPC_CR5 = 73,
    UNW_PPC_CR6 = 74,
    UNW_PPC_CR7 = 75,
    UNW_PPC_XER = 76,
    UNW_PPC_V0 = 77,
    UNW_PPC_V1 = 78,
    UNW_PPC_V2 = 79,
    UNW_PPC_V3 = 80,
    UNW_PPC_V4 = 81,
    UNW_PPC_V5 = 82,
    UNW_PPC_V6 = 83,
    UNW_PPC_V7 = 84,
    UNW_PPC_V8 = 85,
    UNW_PPC_V9 = 86,
    UNW_PPC_V10 = 87,
    UNW_PPC_V11 = 88,
    UNW_PPC_V12 = 89,
    UNW_PPC_V13 = 90,
    UNW_PPC_V14 = 91,
    UNW_PPC_V15 = 92,
    UNW_PPC_V16 = 93,
    UNW_PPC_V17 = 94,
    UNW_PPC_V18 = 95,
    UNW_PPC_V19 = 96,
    UNW_PPC_V20 = 97,
    UNW_PPC_V21 = 98,
    UNW_PPC_V22 = 99,
    UNW_PPC_V23 = 100,
    UNW_PPC_V24 = 101,
    UNW_PPC_V25 = 102,
    UNW_PPC_V26 = 103,
    UNW_PPC_V27 = 104,
    UNW_PPC_V28 = 105,
    UNW_PPC_V29 = 106,
    UNW_PPC_V30 = 107,
    UNW_PPC_V31 = 108,
    UNW_PPC_VRSAVE = 109,
    UNW_PPC_VSCR = 110,
    UNW_PPC_SPE_ACC = 111,
    UNW_PPC_SPEFSCR = 112
};

enum {
    UNW_X86_64_RAX = 0,
    UNW_X86_64_RDX = 1,
    UNW_X86_64_RCX = 2,
    UNW_X86_64_RBX = 3,
    UNW_X86_64_RSI = 4,
    UNW_X86_64_RDI = 5,
    UNW_X86_64_RBP = 6,
    UNW_X86_64_RSP = 7,
    UNW_X86_64_R8 = 8,
    UNW_X86_64_R9 = 9,
    UNW_X86_64_R10 = 10,
    UNW_X86_64_R11 = 11,
    UNW_X86_64_R12 = 12,
    UNW_X86_64_R13 = 13,
    UNW_X86_64_R14 = 14,
    UNW_X86_64_R15 = 15,
    UNW_X86_64_RIP = 16,
    UNW_X86_64_XMM0 = 17,
    UNW_X86_64_XMM1 = 18,
    UNW_X86_64_XMM2 = 19,
    UNW_X86_64_XMM3 = 20,
    UNW_X86_64_XMM4 = 21,
    UNW_X86_64_XMM5 = 22,
    UNW_X86_64_XMM6 = 23,
    UNW_X86_64_XMM7 = 24,
    UNW_X86_64_XMM8 = 25,
    UNW_X86_64_XMM9 = 26,
    UNW_X86_64_XMM10 = 27,
    UNW_X86_64_XMM11 = 28,
    UNW_X86_64_XMM12 = 29,
    UNW_X86_64_XMM13 = 30,
    UNW_X86_64_XMM14 = 31,
    UNW_X86_64_XMM15 = 32,
};

enum {
    UNW_X86_EAX = 0,
    UNW_X86_ECX = 1,
    UNW_X86_EDX = 2,
    UNW_X86_EBX = 3,
    UNW_X86_EBP = 4,
    UNW_X86_ESP = 5,
    UNW_X86_ESI = 6,
    UNW_X86_EDI = 7
};

enum {
    UNW_REG_IP = -1,
    UNW_REG_SP = -2,
};

#define _LIBUNWIND_CONTEXT_SIZE 167
struct unw_context_t {
    uint64_t data[_LIBUNWIND_CONTEXT_SIZE];
};

struct dyld_unwind_sections {
    const struct mach_header *mh;
    const void *dwarf_section;
    uintptr_t dwarf_section_length;
    const void *compact_unwind_section;
    uintptr_t compact_unwind_section_length;
};

extern "C" bool _dyld_find_unwind_sections(void *, dyld_unwind_sections *);

#endif // LD64_LIBUNWIND_H_
