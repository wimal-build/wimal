#ifndef LD64_LIBKERN_OSATOMIC_H_
#define LD64_LIBKERN_OSATOMIC_H_

#ifdef __APPLE__
#include_next <libkern/OSAtomic.h>
#else // !__APPLE__

#include <stdint.h>

// https://developer.apple.com/documentation/kernel/1576451-osaddatomic64
int64_t OSAtomicAdd64(int64_t amount, volatile int64_t *address);

// https://developer.apple.com/documentation/kernel/1576460-osincrementatomic
int32_t OSAtomicIncrement32(volatile int32_t *address);

#endif // __APPLE__

#endif // LD64_LIBKERN_OSATOMIC_H_
