#ifndef	LD64_MACH_VM_PROT_H_
#define	LD64_MACH_VM_PROT_H_

#include <llvm/Object/MachO.h>

#ifdef __APPLE__
#include_next <mach/vm_prot.h>
#else // !__APPLE__

// https://developer.apple.com/documentation/kernel/vm_prot_t
typedef int	vm_prot_t;

// https://github.com/apple/darwin-xnu/blob/xnu-4903.221.2/osfmk/mach/vm_prot.h#L83
using llvm::MachO::VM_PROT_READ;
using llvm::MachO::VM_PROT_WRITE;
using llvm::MachO::VM_PROT_EXECUTE;

#endif // __APPLE__

#endif // LD64_MACH_VM_PROT_H_
