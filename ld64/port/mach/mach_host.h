#ifndef LD64_MACH_MACH_HOST_H_
#define LD64_MACH_MACH_HOST_H_

#ifdef __APPLE__
#include_next <mach/mach_host.h>
#else // !__APPLE__

#include <mach/mach_types.h>

__BEGIN_DECLS

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

// https://developer.apple.com/documentation/kernel/1502546-host_statistics
// http://web.mit.edu/darwin/src/modules/xnu/osfmk/man/host_statistics.html
kern_return_t host_statistics(
    host_t host_priv,
    host_flavor_t flavor,
    host_info_t host_info_out,
    mach_msg_type_number_t *host_info_outCnt
);

__END_DECLS

#endif // __APPLE__

#endif // LD64_MACH_MACH_HOST_H_
