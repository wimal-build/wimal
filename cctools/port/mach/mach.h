#ifndef CCTOOLS_MACH_MACH_H_
#define CCTOOLS_MACH_MACH_H_

#include <fcntl.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include <mach/machine.h>

#ifndef O_FSYNC
#define O_FSYNC O_SYNC
#endif // O_FSYNC

typedef unsigned int __darwin_natural_t;

// https://developer.apple.com/documentation/kernel/natural_t
typedef __darwin_natural_t natural_t;

// https://developer.apple.com/documentation/kernel/kern_return_t
typedef int kern_return_t;

// https://developer.apple.com/documentation/kernel/ipc_port_t
typedef struct ipc_port	*ipc_port_t;

// https://developer.apple.com/documentation/kernel/mach_port_t
typedef ipc_port_t mach_port_t;

// https://developer.apple.com/documentation/kernel/mach_port_name_t
typedef natural_t mach_port_name_t;

// https://developer.apple.com/documentation/kernel/ipc_space_t
typedef mach_port_t ipc_space_t;

// https://developer.apple.com/documentation/kernel/mach_msg_type_number_t
typedef natural_t mach_msg_type_number_t;

// https://developer.apple.com/documentation/kernel/integer_t
typedef int integer_t;

// https://developer.apple.com/documentation/kernel/vm_map_t
typedef mach_port_t vm_map_t;

// https://developer.apple.com/documentation/kernel/host_t
typedef struct host *host_t;

// https://developer.apple.com/documentation/kernel/host_flavor_t
typedef integer_t host_flavor_t;

// https://github.com/apple/darwin-xnu/blob/xnu-4903.221.2/osfmk/mach/host_info.h#L130
#pragma pack(4)
struct host_basic_info {
    integer_t max_cpus;
    integer_t avail_cpus;
    natural_t memory_size;
    cpu_type_t cpu_type;
    cpu_subtype_t cpu_subtype;
    cpu_threadtype_t cpu_threadtype;
    integer_t physical_cpu;
    integer_t physical_cpu_max;
    integer_t logical_cpu;
    integer_t logical_cpu_max;
    uint64_t max_mem;
};
#pragma pack()

// https://developer.apple.com/documentation/kernel/host_basic_info_t
typedef struct host_basic_info *host_basic_info_t;

// https://developer.apple.com/documentation/kernel/host_sched_info_data_t
struct host_sched_info {
    integer_t min_timeout;
    integer_t min_quantum;
};

// https://developer.apple.com/documentation/kernel/host_basic_info_data_t
typedef struct host_basic_info host_basic_info_data_t;

// https://developer.apple.com/documentation/kernel/host_sched_info_data_t
typedef struct host_sched_info host_sched_info_data_t;

// https://developer.apple.com/documentation/kernel/host_name_port_t
typedef host_t host_name_port_t;

// https://developer.apple.com/documentation/kernel/host_info_t
typedef integer_t *host_info_t;

// http://web.mit.edu/darwin/src/modules/xnu/osfmk/man/host_info.html
#define HOST_BASIC_INFO 1
#define HOST_SCHED_INFO 3

#define HOST_BASIC_INFO_COUNT (sizeof(host_basic_info_data_t) / sizeof(integer_t))
#define HOST_SCHED_INFO_COUNT (sizeof(host_sched_info_data_t) / sizeof(integer_t))

// https://github.com/apple/darwin-xnu/blob/xnu-4903.221.2/osfmk/mach/kern_return.h#L72
#define KERN_SUCCESS 0

// https://developer.apple.com/documentation/kernel/vm_offset_t
typedef uintptr_t vm_offset_t;

// https://developer.apple.com/documentation/kernel/vm_size_t
typedef uintptr_t vm_size_t;

// https://developer.apple.com/documentation/kernel/vm_address_t
typedef vm_offset_t vm_address_t;

__BEGIN_DECLS

// https://developer.apple.com/documentation/kernel/1502514-host_info
// http://web.mit.edu/darwin/src/modules/xnu/osfmk/man/host_info.html
kern_return_t host_info(
    host_t host,
    host_flavor_t flavor,
    host_info_t host_info_out,
    mach_msg_type_number_t *host_info_outCnt
);

// http://web.mit.edu/darwin/src/modules/xnu/osfmk/man/mach_task_self.html
mach_port_t mach_task_self(void);

// http://web.mit.edu/darwin/src/modules/xnu/osfmk/man/mach_host_self.html
host_name_port_t mach_host_self(void);

// http://web.mit.edu/darwin/src/modules/xnu/osfmk/man/vm_allocate.html
// https://developer.apple.com/documentation/kernel/1585381-vm_allocate
kern_return_t vm_allocate(
    vm_map_t target_task,
    vm_address_t *address,
    vm_size_t size,
    int flags
);

// http://web.mit.edu/darwin/src/modules/xnu/osfmk/man/vm_deallocate.html
// https://developer.apple.com/documentation/kernel/1585284-vm_deallocate
kern_return_t vm_deallocate(
    vm_map_t target_task,
    vm_address_t address,
    vm_size_t size
);

// https://developer.apple.com/documentation/kernel/1578777-mach_port_deallocate
kern_return_t mach_port_deallocate(
    ipc_space_t task,
    mach_port_name_t name
);

#define mach_error_string(...) "unknown error"

__END_DECLS

#endif // CCTOOLS_MACH_MACH_H_
