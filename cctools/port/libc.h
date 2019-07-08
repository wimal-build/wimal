#ifdef __APPLE__
#include_next <libc.h>
#else // !__APPLE__
// For MAXPATHLEN
#include <sys/param.h>
#endif // __APPLE__
