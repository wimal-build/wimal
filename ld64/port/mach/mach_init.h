#ifndef LD64_MACH_MACH_INIT_H_
#define LD64_MACH_MACH_INIT_H_

#ifdef __APPLE__
#include_next <mach/mach_init.h>
#else // !__APPLE__

#include <mach/mach_host.h>

__BEGIN_DECLS

// http://web.mit.edu/darwin/src/modules/xnu/osfmk/man/mach_task_self.html
mach_port_t mach_task_self(void);

// http://web.mit.edu/darwin/src/modules/xnu/osfmk/man/mach_host_self.html
host_name_port_t mach_host_self(void);

__END_DECLS

#endif // __APPLE__

#endif // LD64_MACH_MACH_INIT_H_