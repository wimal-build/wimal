#ifndef LD64_FCNTL_H_
#define LD64_FCNTL_H_

#if !defined(__cplusplus) || defined(F_GETPATH) || defined(LD64_PORT_CPP)
#include_next <fcntl.h>
#else
#define fcntl no_fcntl
#include_next <fcntl.h>
#undef fcntl
#include <errno.h>
#include <limits.h>

#define F_GETPATH -1000

extern int (*real_fcntl)(int fd, int cmd, ...);
extern int fcntl_getpath(int fd, char *path);

namespace ld64 {

template <typename... Args>
inline static int fcntl(int fd, int cmd, Args... args) {
    if (cmd == F_GETPATH) {
        return EINVAL;
    } else {
        return real_fcntl(fd, cmd, args...);
    }
}

template <>
inline int fcntl(int fd, int cmd, char *path) {
    if (cmd == F_GETPATH) {
        return fcntl_getpath(fd, path);
    } else {
        return real_fcntl(fd, cmd, path);
    }
}

template <int n>
inline int fcntl(int fd, int cmd, char (&path)[n]) {
    return fcntl(fd, cmd, (char *) path);
}

}

using ld64::fcntl;

#endif // __cplusplus

#endif // LD64_FCNTL_H_
