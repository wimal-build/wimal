#ifndef CCTOOLS_SERVERS_BOOTSTRAP_H_
#define CCTOOLS_SERVERS_BOOTSTRAP_H_

#ifdef __APPLE__
#include_next <servers/bootstrap.h>
#endif // __APPLE__

#ifdef HOOK_STRNCMP
#include <string.h>
#ifdef strncmp
#undef strncmp
#endif // strncmp
#define strncmp cctools_strncmp
#endif // HOOK_STRNCMP

#endif // CCTOOLS_SERVERS_BOOTSTRAP_H_
