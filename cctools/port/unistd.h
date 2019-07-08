#ifndef CCTOOLS_UNISTD_H_
#define CCTOOLS_UNISTD_H_

#include_next <unistd.h>

#ifndef __APPLE__
// https://opensource.apple.com/source/xnu/xnu-4903.221.2/bsd/sys/errno.h
#ifndef EFTYPE
#define EFTYPE 79
#endif // EFTYPE

#ifndef EBADRPC
#define EBADRPC 72
#endif // EBADRPC

#define st_mtimespec st_mtim

#ifndef AR_EFMT1
#define AR_EFMT1 "#1/"
#endif // AR_EFMT1

#endif // __APPLE__

#endif // CCTOOLS_UNISTD_H_
