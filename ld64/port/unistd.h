#ifndef LD64_UNISTD_H_
#define LD64_UNISTD_H_

#include_next <unistd.h>

#ifndef __APPLE__

// http://www.manpagez.com/man/5/types/
#include <sys/types.h> // For mode_t

// http://www.manpagez.com/man/3/mkpath_np/
int mkpath_np(const char *path, mode_t omode);

#endif // __APPLE__

// Fix missing include in ld64/src/ld/code-sign-blobs/blob.cpp
#include <string.h>

#endif // LD64_UNISTD_H_
