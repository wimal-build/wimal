#ifndef LD64_MACH_VM_TYPES_H_
#define LD64_MACH_VM_TYPES_H_

#include <stdint.h>

typedef unsigned int __darwin_natural_t;

// https://developer.apple.com/documentation/kernel/natural_t
typedef __darwin_natural_t natural_t;

// https://developer.apple.com/documentation/kernel/vm_offset_t
typedef uintptr_t vm_offset_t;

// https://developer.apple.com/documentation/kernel/vm_size_t
typedef uintptr_t vm_size_t;

// https://developer.apple.com/documentation/kernel/vm_address_t
typedef vm_offset_t vm_address_t;

// https://developer.apple.com/documentation/kernel/integer_t
typedef int integer_t;

// https://developer.apple.com/documentation/kernel/mach_vm_offset_t
typedef uint64_t mach_vm_offset_t;

#endif // LD64_MACH_VM_TYPES_H_
