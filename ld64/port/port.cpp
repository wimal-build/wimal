extern "C" const char *compile_stubs = "empty";
extern "C" const char ldVersionString[] = "";

#ifndef __APPLE__

// fcntl_getpath
#define LD64_PORT_CPP
#include <fcntl.h> // for fcntl
#include <stdio.h> // for snprintf
#include <unistd.h> // for access / readlink
#include <errno.h> // for EINVAL
#include <limits.h> // for PATH_MAX

int (*real_fcntl)(int fd, int cmd, ...) = fcntl;

// See: `llvm/lib/Support/Unix/Path.inc`
int fcntl_getpath(int fd, char *path) {
    static const bool HAS_PROC_SELF_FD = (::access("/proc/self/fd", R_OK) == 0);
    if (HAS_PROC_SELF_FD) {
        char proc[64];
        snprintf(proc, sizeof(proc), "/proc/self/fd/%d", fd);
        ssize_t ret = ::readlink(proc, path, PATH_MAX);
        if (ret > 0) {
            return 0;
        }
    }
    return EINVAL;
}

// host_statistics
#include <mach/mach_host.h>

kern_return_t host_statistics(
    host_t host_priv,
    host_flavor_t flavor,
    host_info_t host_info_out,
    mach_msg_type_number_t *host_info_outCnt
) {
    return ENOTSUP;
}

// mach_timebase_info / mach_absolute_time
#include <mach/mach_time.h>
#include <sys/time.h> // for gettimeofday

kern_return_t mach_timebase_info(mach_timebase_info_t info) {
    info->numer = 1000;
    info->denom = 1;
    return 0;
}

uint64_t mach_absolute_time() {
    struct timeval tv{};
    if (gettimeofday(&tv, nullptr)) {
        return 0;
    }
    return (tv.tv_sec * 1000000ULL) + tv.tv_usec;
}

// strlcpy / strlcat
#include <string.h>

size_t strlcpy(char *dst, const char *src, size_t dstsize) {
    const size_t srclen = strlen(src);
    if (srclen < dstsize) {
        memcpy(dst, src, srclen + 1);
    } else if (dstsize != 0) {
        memcpy(dst, src, dstsize - 1);
        dst[dstsize - 1] = '\0';
    }
    return srclen;
}

size_t strlcat(char *dst, const char *src, size_t dstsize) {
    const size_t srclen = strlen(src);
    const size_t dstlen = strnlen(dst, dstsize);
    if (dstlen == dstsize) {
        return dstsize + srclen;
    }
    if (srclen < dstsize - dstlen) {
        memcpy(dst + dstlen, src, srclen + 1);
    } else {
        memcpy(dst + dstlen, src, dstsize - dstlen - 1);
        dst[dstsize - 1] = '\0';
    }
    return dstlen + srclen;
}

// OSAtomicAdd64 / OSAtomicIncrement32
#include <libkern/OSAtomic.h>
#ifdef LD64_ENABLE_ATOMIC
#include <stdatomic.h> // for atomic_fetch_add_explicit
#else
#include <mutex>
#endif // LD64_ENABLE_ATOMIC

// https://github.com/apple/darwin-xnu/blob/master/libkern/gen/OSAtomicOperations.c
int64_t OSAtomicAdd64(int64_t amount, volatile int64_t *address) {
#ifdef LD64_ENABLE_ATOMIC
    return atomic_fetch_add_explicit(
        (_Atomic int64_t *) (uintptr_t) address, amount, memory_order_relaxed
    );
#else
    static std::mutex mutex;
    std::lock_guard<std::mutex> lock(mutex);
    auto result = *address;
    *address += amount;
    return result;
#endif // LD64_ENABLE_ATOMIC
}

int32_t OSAtomicIncrement32(volatile int32_t *address) {
#ifdef LD64_ENABLE_ATOMIC
    return atomic_fetch_add_explicit(
        (_Atomic int32_t *) address, 1, memory_order_relaxed
    );
#else
    static std::mutex mutex;
    std::lock_guard<std::mutex> lock(mutex);
    return (*address)++;
#endif // LD64_ENABLE_ATOMIC
}

// __assert_rtn
#include <stdlib.h> // for exit
#include <libunwind/InternalMacros.h>

void __assert_rtn(const char *, const char *, int, const char *) {
    exit(1);
}

// mkpath_np
#include <memory> // for shared_ptr
#include <stdlib.h> // for free
#include <string.h> // for strdup / strlen / strrchr
#include <sys/stat.h> // for mkdir / stat / chmod
#include <sys/types.h> // for mode_t

// https://opensource.apple.com/source/Libc/Libc-1272.200.26/util/mkpath_np.c
int mkpath_np(const char *path, mode_t omode) {
    char *apath = nullptr;
    char *opath = nullptr;
    auto guard = std::shared_ptr<int>(
        new int(errno), [&](const int *error) {
            free(apath);
            free(opath);
            errno = *error;
        }
    );

    if (0 == mkdir(path, omode)) {
        return 0;
    }

    struct stat sbuf{};
    switch (errno) {
        case ENOENT:
            break;
        case EEXIST:
            if (stat(path, &sbuf) == 0) {
                if (S_ISDIR(sbuf.st_mode)) {
                    return EEXIST;
                } else {
                    return ENOTDIR;
                }
            } else {
                return EIO;
            }
        case EISDIR:
            return EEXIST;
        default: {
            return errno;
        }
    }

    apath = strdup(path);
    if (apath == nullptr) {
        return ENOMEM;
    }

    mode_t chmod_mode = 0;
    char *s, *sn, *sl;
    sl = s = apath + strlen(apath) - 1;
    do {
        sn = s;
        if (s - 1 > apath && *s == '.' && *(s - 1) == '/') {
            s -= 2;
        }
        if (s > apath && *s == '/') {
            s--;
        }
    } while (s < sn);
    if (s < sl) {
        s[1] = '\0';
        path = opath = strdup(apath);
        if (opath == nullptr) {
            return ENOMEM;
        }
    }

    if (0 == mkdir(path, omode)) {
        return 0;
    }

    unsigned int depth = 0;
    while (true) {
        s = strrchr(apath, '/');
        if (!s) {
            return ENOENT;
        }
        *s = '\0';
        depth++;

        if (0 == mkdir(apath, S_IRWXU | S_IRWXG | S_IRWXO)) {
            struct stat dirstat{};
            if (-1 == stat(apath, &dirstat)) {
                return ENOENT;
            }

            if ((dirstat.st_mode & (S_IWUSR | S_IXUSR)) != (S_IWUSR | S_IXUSR)) {
                chmod_mode = dirstat.st_mode | S_IWUSR | S_IXUSR;
                if (-1 == chmod(apath, chmod_mode)) {
                    return ENOENT;
                }
            }

            break;
        } else if (errno == EEXIST) {
            if (stat(apath, &sbuf) == 0 &&
                S_ISDIR(sbuf.st_mode)) {

                break;
            }

            return ENOTDIR;
        } else if (errno != ENOENT) {
            return errno;
        }
    }

    while (depth > 1) {
        s = strrchr(apath, '\0');
        *s = '/';
        depth--;

        if (-1 == mkdir(apath, S_IRWXU | S_IRWXG | S_IRWXO)) {
            if (errno == EEXIST) {
                continue;
            }
            return errno;
        }

        if (chmod_mode) {
            if (-1 == chmod(apath, chmod_mode)) {
                return ENOENT;
            }
        }
    }

    if (-1 == mkdir(path, omode)) {
        if (errno == EEXIST && stat(path, &sbuf) == 0 && !S_ISDIR(sbuf.st_mode)) {
            return ENOTDIR;
        }
        return errno;
    }
    return 0;
}

// _NSGetExecutablePath
#include <mach-o/dyld.h>
#include <sys/types.h> // for sysctl
#include <sys/sysctl.h> // for sysctl
#include <unistd.h> // for access / readlink

int _NSGetExecutablePath(char *epath, unsigned int *size) {
#if defined(__FreeBSD__) || defined(__DragonFly__)
    int mib[4];
    mib[0] = CTL_KERN;
    mib[1] = KERN_PROC;
    mib[2] = KERN_PROC_PATHNAME;
    mib[3] = -1;
    size_t cb = *size;
    if (sysctl(mib, 4, epath, &cb, NULL, 0) != 0) {
        return -1;
    }
    *size = cb;
    return 0;
#elif defined(__OpenBSD__)
    int mib[4];
    char **argv;
    size_t len;
    const char *comm;
    int ok = 0;
    mib[0] = CTL_KERN;
    mib[1] = KERN_PROC_ARGS;
    mib[2] = getpid();
    mib[3] = KERN_PROC_ARGV;
    if (sysctl(mib, 4, NULL, &len, NULL, 0) < 0) {
        abort();
    }
    if (!(argv = malloc(len))) {
        abort();
    }
    if (sysctl(mib, 4, argv, &len, NULL, 0) < 0) {
        abort();
    }
    comm = argv[0];
    if (*comm == '/' || *comm == '.') {
        char *rpath;
        if ((rpath = realpath(comm, NULL))) {
          strlcpy(epath, rpath, *size);
          free(rpath);
          ok = 1;
        }
    } else {
        char *sp;
        char *xpath = strdup(getenv("PATH"));
        char *path = strtok_r(xpath, ":", &sp);
        struct stat st;
        if (!xpath) {
            abort();
        }
        while (path) {
            snprintf(epath, *size, "%s/%s", path, comm);
            if (!stat(epath, &st) && (st.st_mode & S_IXUSR)) {
                ok = 1;
                break;
            }
            path = strtok_r(NULL, ":", &sp);
        }
        free(xpath);
    }
    free(argv);
    if (ok) {
        *size = strlen(epath);
        return 0;
    }
    return -1;
#else
    int bufsize = *size;
    int ret_size;
    ret_size = readlink("/proc/self/exe", epath, bufsize - 1);
    if (ret_size != -1) {
        *size = ret_size;
        epath[ret_size] = 0;
        return 0;
    } else {
        return -1;
    }
#endif
}

// mach_host_self
#include <mach/mach_init.h>

host_name_port_t mach_host_self() {
    return nullptr;
}

// log2
#include <math.h>

extern "C" double ld64_log2(double x) {
    return log2(x);
}

// qsort_r
#include "configure.h"

#undef qsort_r

void ld64_qsort_r(
    void *base,
    size_t nmemb,
    size_t size,
    void *thunk,
    int (*compar)(void *, const void *, const void *)
) {
    struct ld64_qsort_extra {
        int (*compar)(void *, const void *, const void *);
        void *arg;
    };
    ld64_qsort_extra extra = {compar, thunk};
    ::qsort_r(base, nmemb, size, [](const void *l, const void *r, void *thunk) {
        auto *extra = (ld64_qsort_extra *) thunk;
        return extra->compar(extra->arg, l, r);
    }, &extra);
}

#endif // __APPLE__
