#ifndef	LD64_MACH_VM_PROT_H_
#define	LD64_MACH_VM_PROT_H_

// https://developer.apple.com/documentation/kernel/vm_prot_t
typedef int	vm_prot_t;

// https://github.com/apple/darwin-xnu/blob/xnu-4903.221.2/osfmk/mach/vm_prot.h#L83
#define VM_PROT_READ ((vm_prot_t) 0x01)
#define VM_PROT_WRITE ((vm_prot_t) 0x02)
#define VM_PROT_EXECUTE ((vm_prot_t) 0x04)

#endif // LD64_MACH_VM_PROT_H_
