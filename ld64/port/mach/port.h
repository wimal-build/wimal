#ifndef	LD64_MACH_PORT_H_
#define LD64_MACH_PORT_H_

#include <mach/vm_types.h>

// https://developer.apple.com/documentation/kernel/ipc_port_t
typedef struct ipc_port	*ipc_port_t;

// https://developer.apple.com/documentation/kernel/mach_port_t
typedef ipc_port_t mach_port_t;

// https://developer.apple.com/documentation/kernel/mach_port_name_t
typedef natural_t mach_port_name_t;

#endif // LD64_MACH_PORT_H_
