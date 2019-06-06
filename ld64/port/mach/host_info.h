#ifndef LD64_MACH_HOST_INFO_H_
#define LD64_MACH_HOST_INFO_H_

#include <mach/machine.h>
#include <mach/message.h>

// https://developer.apple.com/documentation/kernel/host_info_t
typedef integer_t *host_info_t;

// https://developer.apple.com/documentation/kernel/host_t
typedef struct host *host_t;

// https://developer.apple.com/documentation/kernel/host_flavor_t
typedef integer_t host_flavor_t;

// https://developer.apple.com/documentation/kernel/host_name_port_t
typedef host_t host_name_port_t;

// host_statistics()
#define HOST_VM_INFO 2

#endif // LD64_MACH_HOST_INFO_H_
