#ifndef CCTOOLS_MACH_BOOLEAN_H_
#define CCTOOLS_MACH_BOOLEAN_H_

#ifdef __APPLE__
#include_next <mach/boolean.h>
#else // !__APPLE__
// https://developer.apple.com/documentation/kernel/boolean_t
typedef int boolean_t;
#endif // __APPLE__

#endif // CCTOOLS_MACH_BOOLEAN_H_
