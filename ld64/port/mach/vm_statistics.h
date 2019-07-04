#ifndef LD64_MACH_VM_STATISTICS_H_
#define LD64_MACH_VM_STATISTICS_H_

#ifdef __APPLE__
#include_next <mach/vm_statistics.h>
#else // !__APPLE__

#include <mach/mach_types.h>
#include <mach/vm_prot.h>

struct vm_statistics {
    integer_t free_count;
    integer_t active_count;
    integer_t inactive_count;
    integer_t wire_count;
    integer_t zero_fill_count;
    integer_t reactivations;
    integer_t pageins;
    integer_t pageouts;
    integer_t faults;
    integer_t cow_faults;
    integer_t lookups;
    integer_t hits;
};

typedef struct vm_statistics *vm_statistics_t;

typedef struct vm_statistics vm_statistics_data_t;

#endif // __APPLE__

#endif // LD64_MACH_VM_STATISTICS_H_
