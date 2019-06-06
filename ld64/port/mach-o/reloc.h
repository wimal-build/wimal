// https://opensource.apple.com/source/xnu/xnu-1504.15.3/EXTERNAL_HEADERS/mach-o/reloc.h
#ifndef LD64_MACHO_RELOC_H_
#define LD64_MACHO_RELOC_H_

#include <llvm/Object/MachO.h>

using llvm::MachO::relocation_info;
using llvm::MachO::scattered_relocation_info;

using llvm::MachO::R_ABS;
using llvm::MachO::R_SCATTERED;

using llvm::MachO::GENERIC_RELOC_VANILLA;
using llvm::MachO::GENERIC_RELOC_PAIR;
using llvm::MachO::GENERIC_RELOC_SECTDIFF;
using llvm::MachO::GENERIC_RELOC_PB_LA_PTR;
using llvm::MachO::GENERIC_RELOC_LOCAL_SECTDIFF;
using llvm::MachO::GENERIC_RELOC_TLV;

#endif // _MACHO_RELOC_H_
