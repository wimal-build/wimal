#ifndef	LD64_MACH_MACH_TYPES_H_
#define LD64_MACH_MACH_TYPES_H_

#ifdef __APPLE__
#include_next <mach/mach_types.h>
#else // !__APPLE__

#include <stdint.h>

// https://developer.apple.com/documentation/kernel/kern_return_t
typedef int kern_return_t;

// https://github.com/apple/darwin-xnu/blob/xnu-4903.221.2/osfmk/mach/kern_return.h#L72
#define KERN_SUCCESS 0

// https://github.com/apple/darwin-xnu/blob/master/bsd/arm/_types.h
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

// https://developer.apple.com/documentation/kernel/mach_msg_type_number_t
typedef natural_t mach_msg_type_number_t;

// https://developer.apple.com/documentation/kernel/ipc_port_t
typedef struct ipc_port	*ipc_port_t;

// https://developer.apple.com/documentation/kernel/mach_port_t
typedef ipc_port_t mach_port_t;

// https://developer.apple.com/documentation/kernel/mach_port_name_t
typedef natural_t mach_port_name_t;

// https://developer.apple.com/documentation/kernel/thread_t
typedef struct thread *thread_t;

// https://developer.apple.com/documentation/kernel/thread_port_t
typedef thread_t thread_port_t;

#endif // __APPLE__

#endif	// LD64_MACH_MACH_TYPES_H_
