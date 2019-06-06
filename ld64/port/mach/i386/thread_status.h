// https://opensource.apple.com/source/xnu/xnu-4903.221.2/osfmk/mach/i386/thread_status.h
#ifndef LD64_MACH_I386_THREAD_STATUS_H_
#define LD64_MACH_I386_THREAD_STATUS_H_

#include <llvm/Object/MachO.h>

using i386_thread_state_t = llvm::MachO::x86_thread_state32_t;
using llvm::MachO::x86_thread_state64_t;

#define __eax eax
#define __ebx ebx
#define __ecx ecx
#define __edx edx
#define __edi edi
#define __esi esi
#define __ebp ebp
#define __esp esp
#define __eip eip
#define __rax rax
#define __rbx rbx
#define __rcx rcx
#define __rdx rdx
#define __rdi rdi
#define __rsi rsi
#define __rbp rbp
#define __rsp rsp
#define __r8 r8
#define __r9 r9
#define __r10 r10
#define __r11 r11
#define __r12 r12
#define __r13 r13
#define __r14 r14
#define __r15 r15
#define __rip rip

#endif // LD64_MACH_I386_THREAD_STATUS_H_
