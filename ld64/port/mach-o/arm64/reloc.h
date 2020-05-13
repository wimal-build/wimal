// https://opensource.apple.com/source/xnu/xnu-4903.221.2/EXTERNAL_HEADERS/mach-o/arm64/reloc.h
#ifndef LD64_MACH_O_ARM64_RELOC_H_
#define LD64_MACH_O_ARM64_RELOC_H_

#include <llvm/Object/MachO.h>

using llvm::MachO::ARM64_RELOC_UNSIGNED;
using llvm::MachO::ARM64_RELOC_SUBTRACTOR;
using llvm::MachO::ARM64_RELOC_BRANCH26;
using llvm::MachO::ARM64_RELOC_PAGE21;
using llvm::MachO::ARM64_RELOC_PAGEOFF12;
using llvm::MachO::ARM64_RELOC_GOT_LOAD_PAGE21;
using llvm::MachO::ARM64_RELOC_GOT_LOAD_PAGEOFF12;
using llvm::MachO::ARM64_RELOC_POINTER_TO_GOT;
using llvm::MachO::ARM64_RELOC_TLVP_LOAD_PAGE21;
using llvm::MachO::ARM64_RELOC_TLVP_LOAD_PAGEOFF12;
using llvm::MachO::ARM64_RELOC_ADDEND;

#endif // LD64_MACH_O_ARM64_RELOC_H_
