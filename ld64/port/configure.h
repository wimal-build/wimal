#ifndef LD64_CONFIGURE_H_
#define LD64_CONFIGURE_H_

#include <sys/param.h>
#include <limits.h>
#include <unistd.h>
#include <stddef.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

#define SUPPORT_ARCH_armv6 1
#define SUPPORT_ARCH_armv7 1
#define SUPPORT_ARCH_armv7s 1
#define SUPPORT_ARCH_arm64 1
#define SUPPORT_ARCH_i386 1
#define SUPPORT_ARCH_x86_64 1
#define SUPPORT_ARCH_x86_64h 1
#define SUPPORT_ARCH_armv6m 1
#define SUPPORT_ARCH_armv7k 1
#define SUPPORT_ARCH_armv7m 1
#define SUPPORT_ARCH_armv7em 1

#define ALL_SUPPORTED_ARCHS "i386 x86_64 x86_64h armv6 armv7 armv7s armv7m armv7k arm64"

#define LD64_VERSION_NUM 0

#define BITCODE_XAR_VERSION "1.0"

#ifndef HW_NCPU
#define HW_NCPU 3
#endif

#ifndef CTL_HW
#define CTL_HW  6
#endif

#ifndef ARG_MAX
#define ARG_MAX 31072
#endif

// https://developer.apple.com/documentation/kernel/uuid_string_t
// https://opensource.apple.com/source/xnu/xnu-4570.41.2/bsd/sys/_types.h
typedef char uuid_string_t[37];

#ifdef __cplusplus
// Fix missing includes
#include <algorithm>
#include <mutex>
#endif // __cplusplus

#ifndef __APPLE__

#define dl_info Dl_info

// Fix statfs
// https://www.manpagez.com/man/2/statfs/
#include <sys/param.h>
#include <sys/mount.h>

#define statfs ld64_statfs

struct ld64_statfs {
    const char *f_fstypename;
};

static inline int ld64_statfs(const char *file, ld64_statfs *buf) {
    buf->f_fstypename = "";
    return -1;
}

// Fix qsort_r
#include <stdlib.h>

__BEGIN_DECLS
extern void ld64_qsort_r(
    void *base,
    size_t nmemb,
    size_t size,
    void *thunk,
    int (*compar)(void *, const void *, const void *)
);
__END_DECLS

#ifdef qsort_r
#undef qsort_r
#endif // qsort_r
#define qsort_r(...) ld64_qsort_r(__VA_ARGS__)

#ifndef PAGE_MASK
#define PAGE_MASK 0xFFFFF000UL
#endif // PAGE_MASK

#endif // __APPLE__

#endif // LD64_CONFIGURE_H_
