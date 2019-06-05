// https://opensource.apple.com/source/dyld/dyld-635.2/include/mach-o/dyld.h
#ifndef LD64_MACH_O_DYLD_H_
#define LD64_MACH_O_DYLD_H_

#include <stdint.h>

__BEGIN_DECLS

typedef void *NSObjectFileImage;

extern int _NSGetExecutablePath(char *buf, uint32_t *bufsize);

__END_DECLS

#endif // LD64_MACH_O_DYLD_H_
