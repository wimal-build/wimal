#ifdef __APPLE__
#include_next <libc.h>
#else // !__APPLE__
// For MAXPATHLEN
#include <sys/param.h>
// For TIMESPEC_TO_TIMEVAL
#include <sys/time.h>
#endif // __APPLE__

#ifndef LTO_SUPPORT
static void *llvm_bundle_pointer;
static int llvm_bundle_size;
#endif // LTO_SUPPORT
