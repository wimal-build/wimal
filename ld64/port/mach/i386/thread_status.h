// https://opensource.apple.com/source/xnu/xnu-4903.221.2/osfmk/mach/i386/thread_status.h
#ifndef LD64_MACH_I386_THREAD_STATUS_H_
#define LD64_MACH_I386_THREAD_STATUS_H_

#include <mach/i386/_structs.h>

typedef _STRUCT_X86_THREAD_STATE32 i386_thread_state_t;

typedef _STRUCT_X86_THREAD_STATE64 x86_thread_state64_t;

#endif // LD64_MACH_I386_THREAD_STATUS_H_
