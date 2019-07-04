#ifndef LD64_MACH_MACH_TIME_H_
#define LD64_MACH_MACH_TIME_H_

#ifdef __APPLE__
#include_next <mach/mach_time.h>
#else // !__APPLE__

#include <mach/mach_types.h>

__BEGIN_DECLS

struct mach_timebase_info {
    uint32_t numer;
    uint32_t denom;
};

typedef struct mach_timebase_info *mach_timebase_info_t;

typedef struct mach_timebase_info mach_timebase_info_data_t;

kern_return_t mach_timebase_info(mach_timebase_info_t info);

uint64_t mach_absolute_time();

__END_DECLS

#endif // __APPLE__

#endif // LD64_MACH_MACH_TIME_H_
