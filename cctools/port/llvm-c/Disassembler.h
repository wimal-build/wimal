#ifndef CCTOOLS_LLVM_C_DISASSEMBLER_H_
#define CCTOOLS_LLVM_C_DISASSEMBLER_H_

#include <stddef.h>

#include <architecture/sparc/reg.h>
#undef PC // Fix name conflict
#include_next <llvm-c/Disassembler.h>
#define PC (1)

// For MAXPATHLEN
#include <sys/param.h>

#define LLVMCreateDisasm LLVMCreateDisasmCPU

#endif // CCTOOLS_LLVM_C_DISASSEMBLER_H_
