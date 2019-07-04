#ifndef CCTOOLS_MACH_VM_PROT_H_
#define CCTOOLS_MACH_VM_PROT_H_

#ifdef __APPLE__
#include_next <mach/vm_prot.h>
#else // __APPLE__

// https://developer.apple.com/documentation/kernel/vm_prot_t
typedef int vm_prot_t;

// https://github.com/apple/darwin-xnu/blob/xnu-4903.221.2/osfmk/mach/vm_prot.h#L83
enum {
    VM_PROT_READ = 0x1,
    VM_PROT_WRITE = 0x2,
    VM_PROT_EXECUTE = 0x4
};

#endif // __APPLE__

#endif // CCTOOLS_MACH_VM_PROT_H_
