// https://opensource.apple.com/source/xnu/xnu-1504.15.3/EXTERNAL_HEADERS/mach-o/nlist.h
#ifndef LD64_MACHO_NLIST_H_
#define LD64_MACHO_NLIST_H_

#include <llvm/Object/MachO.h>

struct nlist {
    union {
        char *n_name;
        uint32_t n_strx;
    } n_un;
    uint8_t n_type;
    uint8_t n_sect;
    int16_t n_desc;
    uint32_t n_value;
};

struct nlist_64 {
    union {
        uint32_t n_strx;
    } n_un;
    uint8_t n_type;
    uint8_t n_sect;
    uint16_t n_desc;
    uint64_t n_value;
};

using llvm::MachO::N_STAB;
using llvm::MachO::N_PEXT;
using llvm::MachO::N_TYPE;
using llvm::MachO::N_EXT;
using llvm::MachO::N_UNDF;
using llvm::MachO::N_ABS;
using llvm::MachO::N_SECT;
using llvm::MachO::N_INDR;

using llvm::MachO::GET_COMM_ALIGN;
using llvm::MachO::SET_COMM_ALIGN;

using llvm::MachO::REFERENCE_FLAG_UNDEFINED_NON_LAZY;
using llvm::MachO::REFERENCE_FLAG_UNDEFINED_LAZY;
using llvm::MachO::REFERENCED_DYNAMICALLY;

using llvm::MachO::GET_LIBRARY_ORDINAL;
using llvm::MachO::SET_LIBRARY_ORDINAL;

using llvm::MachO::DYNAMIC_LOOKUP_ORDINAL;
using llvm::MachO::EXECUTABLE_ORDINAL;

using llvm::MachO::N_NO_DEAD_STRIP;
using llvm::MachO::N_WEAK_REF;
using llvm::MachO::N_WEAK_DEF;
using llvm::MachO::N_ARM_THUMB_DEF;
using llvm::MachO::N_SYMBOL_RESOLVER;
using llvm::MachO::N_ALT_ENTRY;

enum {
    N_REF_TO_WEAK = llvm::MachO::N_WEAK_DEF
};

#endif // LD64_MACHO_LIST_H_
