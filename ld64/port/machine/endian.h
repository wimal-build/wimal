#ifndef LD64_MACHINE_ENDIAN_H_
#define LD64_MACHINE_ENDIAN_H_

#ifdef __APPLE__
#include_next <machine/endian.h>
#else // !__APPLE__
#include <arpa/inet.h>
#endif // __APPLE__

#endif // LD64_MACHINE_ENDIAN_H_
