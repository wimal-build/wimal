#ifndef LD64_MACH_MACH_INIT_H_
#define LD64_MACH_MACH_INIT_H_

#include <mach/mach_types.h>

__BEGIN_DECLS

// http://web.mit.edu/darwin/src/modules/xnu/osfmk/man/mach_task_self.html
mach_port_t mach_task_self(void);

// http://web.mit.edu/darwin/src/modules/xnu/osfmk/man/mach_host_self.html
host_name_port_t mach_host_self(void);

__END_DECLS

#endif // LD64_MACH_MACH_INIT_H_