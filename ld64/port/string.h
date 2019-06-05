#ifndef LD64_STRING_H_
#define LD64_STRING_H_

#include_next <string.h>

#include <sys/cdefs.h> // For __BEGIN_DECLS/__END_DECLS
#include <sys/types.h> // For size_t

__BEGIN_DECLS

// https://www.freebsd.org/cgi/man.cgi?query=strlcpy
size_t strlcpy(char *dst, const char *src, size_t dstsize);
size_t strlcat(char *dst, const char *src, size_t dstsize);

__END_DECLS

#endif // LD64_STRING_H_
