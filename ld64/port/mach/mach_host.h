#ifndef LD64_MACH_MACH_HOST_H_
#define LD64_MACH_MACH_HOST_H_

#include <mach/host_info.h>
#include <mach/kern_return.h>

__BEGIN_DECLS

// https://developer.apple.com/documentation/kernel/1502546-host_statistics
// http://web.mit.edu/darwin/src/modules/xnu/osfmk/man/host_statistics.html
kern_return_t host_statistics(
    host_t host_priv,
    host_flavor_t flavor,
    host_info_t host_info_out,
    mach_msg_type_number_t *host_info_outCnt
);

__END_DECLS

#endif // LD64_MACH_MACH_HOST_H_