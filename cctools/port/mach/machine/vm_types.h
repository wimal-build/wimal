#ifndef CCTOOLS_MACH_MACHINE_VM_TYPES_H_
#define CCTOOLS_MACH_MACHINE_VM_TYPES_H_

#ifdef __APPLE__
#include_next <mach/machine/vm_types.h>
#else // !__APPLE__
#include <stdint.h>

// https://developer.apple.com/documentation/kernel/vm_size_t
typedef uintptr_t vm_size_t;

// https://developer.apple.com/documentation/kernel/integer_t
typedef int integer_t;

// https://developer.apple.com/documentation/kernel/kern_return_t
typedef int kern_return_t;
#endif // __APPLE__

#endif // CCTOOLS_MACH_MACHINE_VM_TYPES_H_
