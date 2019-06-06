// https://opensource.apple.com/source/xnu/xnu-4903.221.2/EXTERNAL_HEADERS/mach-o/fat.h
#ifndef LD64_MACH_O_FAT_H_
#define LD64_MACH_O_FAT_H_

#include <llvm/Object/MachO.h>

using llvm::MachO::FAT_MAGIC;
using llvm::MachO::FAT_CIGAM;

using llvm::MachO::fat_header;
using llvm::MachO::fat_arch;

#endif // LD64_MACH_O_FAT_H_
