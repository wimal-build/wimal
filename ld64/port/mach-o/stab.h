// https://opensource.apple.com/source/xnu/xnu-1504.15.3/EXTERNAL_HEADERS/mach-o/stab.h
#ifndef LD64_MACHO_STAB_H_
#define LD64_MACHO_STAB_H_

#include <llvm/Object/MachO.h>

using llvm::MachO::N_GSYM;
using llvm::MachO::N_FNAME;
using llvm::MachO::N_FUN;
using llvm::MachO::N_STSYM;
using llvm::MachO::N_LCSYM;
using llvm::MachO::N_BNSYM;
using llvm::MachO::N_AST;
using llvm::MachO::N_OPT;
using llvm::MachO::N_RSYM;
using llvm::MachO::N_SLINE;
using llvm::MachO::N_ENSYM;
using llvm::MachO::N_SSYM;
using llvm::MachO::N_SO;
using llvm::MachO::N_OSO;
using llvm::MachO::N_LSYM;
using llvm::MachO::N_BINCL;
using llvm::MachO::N_SOL;
using llvm::MachO::N_PARAMS;
using llvm::MachO::N_VERSION;
using llvm::MachO::N_OLEVEL;
using llvm::MachO::N_PSYM;
using llvm::MachO::N_EINCL;
using llvm::MachO::N_ENTRY;
using llvm::MachO::N_LBRAC;
using llvm::MachO::N_EXCL;
using llvm::MachO::N_RBRAC;
using llvm::MachO::N_BCOMM;
using llvm::MachO::N_ECOMM;
using llvm::MachO::N_ECOML;
using llvm::MachO::N_LENG;
using llvm::MachO::N_PC;

#endif // LD64_MACHO_STAB_H_
