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

// https://opensource.apple.com/source/xnu/xnu-4903.221.2/osfmk/mach/machine/vm_param.h
#if defined (__i386__) || defined(__x86_64__)
#ifndef I386_PGBYTES
#define I386_PGBYTES 4096
#endif // I386_PGBYTES

#ifndef PAGE_SIZE
#define	PAGE_SIZE I386_PGBYTES
#endif // PAGE_SIZE

#ifndef PAGE_MASK
#define	PAGE_MASK (PAGE_SIZE - 1)
#endif // PAGE_MASK
#elif defined (__arm__) || defined (__arm64__)

#ifndef PAGE_SHIFT_CONST
#ifdef	__arm__
#define PAGE_SHIFT_CONST 12
#elif defined(__arm64__)
extern unsigned		PAGE_SHIFT_CONST;
#else
#error Unsupported arch
#endif
#endif // PAGE_SHIFT_CONST

#define PAGE_SHIFT PAGE_SHIFT_CONST
#define PAGE_SIZE (1 << PAGE_SHIFT)
#define PAGE_MASK (PAGE_SIZE - 1)
#endif // defined (__i386__) || defined(__x86_64__)

#endif // __APPLE__

#endif // LD64_MACH_VM_STATISTICS_H_
