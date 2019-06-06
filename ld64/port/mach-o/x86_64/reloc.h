// https://opensource.apple.com/source/xnu/xnu-4903.221.2/EXTERNAL_HEADERS/mach-o/x86_64/reloc.h
#ifndef LD64_MACH_O_X86_64_RELOC_H_
#define LD64_MACH_O_X86_64_RELOC_H_

#include <llvm/Object/MachO.h>

using llvm::MachO::X86_64_RELOC_UNSIGNED;
using llvm::MachO::X86_64_RELOC_SIGNED;
using llvm::MachO::X86_64_RELOC_BRANCH;
using llvm::MachO::X86_64_RELOC_GOT_LOAD;
using llvm::MachO::X86_64_RELOC_GOT;
using llvm::MachO::X86_64_RELOC_SUBTRACTOR;
using llvm::MachO::X86_64_RELOC_SIGNED_1;
using llvm::MachO::X86_64_RELOC_SIGNED_2;
using llvm::MachO::X86_64_RELOC_SIGNED_4;
using llvm::MachO::X86_64_RELOC_TLV;

#endif // LD64_MACH_O_X86_64_RELOC_H_
