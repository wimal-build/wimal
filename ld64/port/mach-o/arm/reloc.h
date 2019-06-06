// https://opensource.apple.com/source/xnu/xnu-4903.221.2/EXTERNAL_HEADERS/mach-o/arm/reloc.h
#ifndef LD64_MACH_O_ARM_RELOC_H_
#define LD64_MACH_O_ARM_RELOC_H_

#include <llvm/Object/MachO.h>

using llvm::MachO::ARM_RELOC_VANILLA;
using llvm::MachO::ARM_RELOC_PAIR;
using llvm::MachO::ARM_RELOC_SECTDIFF;
using llvm::MachO::ARM_RELOC_LOCAL_SECTDIFF;
using llvm::MachO::ARM_RELOC_PB_LA_PTR;
using llvm::MachO::ARM_RELOC_BR24;
using llvm::MachO::ARM_THUMB_RELOC_BR22;
using llvm::MachO::ARM_THUMB_32BIT_BRANCH;
using llvm::MachO::ARM_RELOC_HALF;
using llvm::MachO::ARM_RELOC_HALF_SECTDIFF;

#endif // LD64_MACH_O_ARM_RELOC_H_
