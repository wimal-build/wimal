// https://opensource.apple.com/source/cctools/cctools-921/include/mach-o/ranlib.h.
#ifndef LD64_MACH_O_RANLIB_H_
#define LD64_MACH_O_RANLIB_H_

#include <stdint.h>
#include <sys/types.h>

#define SYMDEF "__.SYMDEF"
#define SYMDEF_SORTED "__.SYMDEF SORTED"

struct ranlib {
    union {
        uint32_t ran_strx;
#ifndef __LP64__
        char *ran_name;
#endif
    } ran_un;
    uint32_t ran_off;
};

#define SYMDEF_64 "__.SYMDEF_64"
#define SYMDEF_64_SORTED "__.SYMDEF_64 SORTED"

struct ranlib_64 {
    union {
        uint64_t ran_strx;
    } ran_un;
    uint64_t ran_off;
};

#endif // LD64_MACH_O_RANLIB_H_
