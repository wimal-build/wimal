#include <mach/mach.h>

const char apple_version[] = "cctools-921";

#ifndef __APPLE__

#define EMULATED_HOST_CPU_TYPE 16777223
#define EMULATED_HOST_CPU_SUBTYPE 3

kern_return_t host_info(
    host_t host,
    host_flavor_t flavor,
    host_info_t host_info_out,
    mach_msg_type_number_t *host_info_outCnt
) {
    if (flavor == HOST_BASIC_INFO) {
        host_basic_info_t basic_info;

        basic_info = (host_basic_info_t) host_info_out;
        memset(basic_info, 0x00, sizeof(*basic_info));
        basic_info->cpu_type = EMULATED_HOST_CPU_TYPE;
        basic_info->cpu_subtype = EMULATED_HOST_CPU_SUBTYPE;
    }

    return 0;
}

host_name_port_t mach_host_self(void) {
    return 0;
}

mach_port_t mach_task_self(void) {
    return 0;
}

kern_return_t vm_allocate(
    vm_map_t target_task,
    vm_address_t *address,
    vm_size_t size,
    int anywhere
) {
    vm_address_t addr = 0;
    addr = (vm_address_t) calloc(size, sizeof(char));
    if (addr == 0) {
        return 1;
    }
    *address = addr;
    return 0;
}

kern_return_t vm_deallocate(vm_map_t target_task, vm_address_t address, vm_size_t size) {
    return 0;
}

kern_return_t mach_port_deallocate(ipc_space_t task, mach_port_name_t name) {
    return 0;
}

#endif
