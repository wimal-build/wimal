#ifndef LD64_SYS_SYSCTL_H_
#define LD64_SYS_SYSCTL_H_

#ifndef __CYGWIN__
#include_next <sys/sysctl.h>
#else

enum {
  CTL_HW,
  HW_NCPU,
  CTL_KERN,
  KERN_OSRELEASE
};

static inline int sysctl(
        const int *name,
        unsigned int namelen,
        void *oldp,
        size_t *oldlenp,
        const void *newp,
        size_t newlen) {
    return -1;
}
#endif // __CYGWIN__

#endif // LD64_SYS_SYSCTL_H_
