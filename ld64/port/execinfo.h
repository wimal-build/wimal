#ifndef LD64_EXECINFO_H_
#define LD64_EXECINFO_H_

#ifndef __CYGWIN__
#include_next <execinfo.h>
#else
static inline int backtrace(void **array, int size) {
    return 0;
}
#endif // __CYGWIN__

#endif // LD64_EXECINFO_H_
