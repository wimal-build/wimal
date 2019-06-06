// https://opensource.apple.com/source/xnu/xnu-4903.221.2/osfmk/mach/i386/_structs.h
#ifndef LD64_MACH_I386__STRUCTS_H_
#define LD64_MACH_I386__STRUCTS_H_

#include <stdint.h>

typedef struct {
    unsigned int __eax;
    unsigned int __ebx;
    unsigned int __ecx;
    unsigned int __edx;
    unsigned int __edi;
    unsigned int __esi;
    unsigned int __ebp;
    unsigned int __esp;
    unsigned int __ss;
    unsigned int __eflags;
    unsigned int __eip;
    unsigned int __cs;
    unsigned int __ds;
    unsigned int __es;
    unsigned int __fs;
    unsigned int __gs;
} _STRUCT_X86_THREAD_STATE32;

typedef struct {
    unsigned short __invalid: 1;
    unsigned short __denorm: 1;
    unsigned short __zdiv: 1;
    unsigned short __ovrfl: 1;
    unsigned short __undfl: 1;
    unsigned short __precis: 1;
    unsigned short : 2;
    unsigned short __pc: 2;
    unsigned short __rc: 2;
    unsigned short : 1;
    unsigned short : 3;
} _STRUCT_FP_CONTROL;

typedef struct {
    unsigned short __invalid: 1;
    unsigned short __denorm: 1;
    unsigned short __zdiv: 1;
    unsigned short __ovrfl: 1;
    unsigned short __undfl: 1;
    unsigned short __precis: 1;
    unsigned short __stkflt: 1;
    unsigned short __errsumm: 1;
    unsigned short __c0: 1;
    unsigned short __c1: 1;
    unsigned short __c2: 1;
    unsigned short __tos: 3;
    unsigned short __c3: 1;
    unsigned short __busy: 1;
} _STRUCT_FP_STATUS;

typedef struct {
    char __mmst_reg[10];
    char __mmst_rsrv[6];
} _STRUCT_MMST_REG;

typedef struct {
    char __xmm_reg[16];
} _STRUCT_XMM_REG;

typedef struct {
    char __ymm_reg[32];
} _STRUCT_YMM_REG;

typedef struct {
    char __zmm_reg[64];
} _STRUCT_ZMM_REG;

typedef struct {
    char __opmask_reg[8];
} _STRUCT_OPMASK_REG;

typedef struct {
    int __fpu_reserved[2];
    _STRUCT_FP_CONTROL __fpu_fcw;
    _STRUCT_FP_STATUS __fpu_fsw;
    uint8_t __fpu_ftw;
    uint8_t __fpu_rsrv1;
    uint16_t __fpu_fop;
    uint32_t __fpu_ip;
    uint16_t __fpu_cs;
    uint16_t __fpu_rsrv2;
    uint32_t __fpu_dp;
    uint16_t __fpu_ds;
    uint16_t __fpu_rsrv3;
    uint32_t __fpu_mxcsr;
    uint32_t __fpu_mxcsrmask;
    _STRUCT_MMST_REG __fpu_stmm0;
    _STRUCT_MMST_REG __fpu_stmm1;
    _STRUCT_MMST_REG __fpu_stmm2;
    _STRUCT_MMST_REG __fpu_stmm3;
    _STRUCT_MMST_REG __fpu_stmm4;
    _STRUCT_MMST_REG __fpu_stmm5;
    _STRUCT_MMST_REG __fpu_stmm6;
    _STRUCT_MMST_REG __fpu_stmm7;
    _STRUCT_XMM_REG __fpu_xmm0;
    _STRUCT_XMM_REG __fpu_xmm1;
    _STRUCT_XMM_REG __fpu_xmm2;
    _STRUCT_XMM_REG __fpu_xmm3;
    _STRUCT_XMM_REG __fpu_xmm4;
    _STRUCT_XMM_REG __fpu_xmm5;
    _STRUCT_XMM_REG __fpu_xmm6;
    _STRUCT_XMM_REG __fpu_xmm7;
    char __fpu_rsrv4[14 * 16];
    int __fpu_reserved1;
} _STRUCT_X86_FLOAT_STATE32;

typedef struct {
    int __fpu_reserved[2];
    _STRUCT_FP_CONTROL __fpu_fcw;
    _STRUCT_FP_STATUS __fpu_fsw;
    uint8_t __fpu_ftw;
    uint8_t __fpu_rsrv1;
    uint16_t __fpu_fop;
    uint32_t __fpu_ip;
    uint16_t __fpu_cs;
    uint16_t __fpu_rsrv2;
    uint32_t __fpu_dp;
    uint16_t __fpu_ds;
    uint16_t __fpu_rsrv3;
    uint32_t __fpu_mxcsr;
    uint32_t __fpu_mxcsrmask;
    _STRUCT_MMST_REG __fpu_stmm0;
    _STRUCT_MMST_REG __fpu_stmm1;
    _STRUCT_MMST_REG __fpu_stmm2;
    _STRUCT_MMST_REG __fpu_stmm3;
    _STRUCT_MMST_REG __fpu_stmm4;
    _STRUCT_MMST_REG __fpu_stmm5;
    _STRUCT_MMST_REG __fpu_stmm6;
    _STRUCT_MMST_REG __fpu_stmm7;
    _STRUCT_XMM_REG __fpu_xmm0;
    _STRUCT_XMM_REG __fpu_xmm1;
    _STRUCT_XMM_REG __fpu_xmm2;
    _STRUCT_XMM_REG __fpu_xmm3;
    _STRUCT_XMM_REG __fpu_xmm4;
    _STRUCT_XMM_REG __fpu_xmm5;
    _STRUCT_XMM_REG __fpu_xmm6;
    _STRUCT_XMM_REG __fpu_xmm7;
    char __fpu_rsrv4[14 * 16];
    int __fpu_reserved1;
    char __avx_reserved1[64];
    _STRUCT_XMM_REG __fpu_ymmh0;
    _STRUCT_XMM_REG __fpu_ymmh1;
    _STRUCT_XMM_REG __fpu_ymmh2;
    _STRUCT_XMM_REG __fpu_ymmh3;
    _STRUCT_XMM_REG __fpu_ymmh4;
    _STRUCT_XMM_REG __fpu_ymmh5;
    _STRUCT_XMM_REG __fpu_ymmh6;
    _STRUCT_XMM_REG __fpu_ymmh7;
} _STRUCT_X86_AVX_STATE32;

typedef struct {
    int __fpu_reserved[2];
    _STRUCT_FP_CONTROL __fpu_fcw;
    _STRUCT_FP_STATUS __fpu_fsw;
    uint8_t __fpu_ftw;
    uint8_t __fpu_rsrv1;
    uint16_t __fpu_fop;
    uint32_t __fpu_ip;
    uint16_t __fpu_cs;
    uint16_t __fpu_rsrv2;
    uint32_t __fpu_dp;
    uint16_t __fpu_ds;
    uint16_t __fpu_rsrv3;
    uint32_t __fpu_mxcsr;
    uint32_t __fpu_mxcsrmask;
    _STRUCT_MMST_REG __fpu_stmm0;
    _STRUCT_MMST_REG __fpu_stmm1;
    _STRUCT_MMST_REG __fpu_stmm2;
    _STRUCT_MMST_REG __fpu_stmm3;
    _STRUCT_MMST_REG __fpu_stmm4;
    _STRUCT_MMST_REG __fpu_stmm5;
    _STRUCT_MMST_REG __fpu_stmm6;
    _STRUCT_MMST_REG __fpu_stmm7;
    _STRUCT_XMM_REG __fpu_xmm0;
    _STRUCT_XMM_REG __fpu_xmm1;
    _STRUCT_XMM_REG __fpu_xmm2;
    _STRUCT_XMM_REG __fpu_xmm3;
    _STRUCT_XMM_REG __fpu_xmm4;
    _STRUCT_XMM_REG __fpu_xmm5;
    _STRUCT_XMM_REG __fpu_xmm6;
    _STRUCT_XMM_REG __fpu_xmm7;
    char __fpu_rsrv4[14 * 16];
    int __fpu_reserved1;
    char __avx_reserved1[64];
    _STRUCT_XMM_REG __fpu_ymmh0;
    _STRUCT_XMM_REG __fpu_ymmh1;
    _STRUCT_XMM_REG __fpu_ymmh2;
    _STRUCT_XMM_REG __fpu_ymmh3;
    _STRUCT_XMM_REG __fpu_ymmh4;
    _STRUCT_XMM_REG __fpu_ymmh5;
    _STRUCT_XMM_REG __fpu_ymmh6;
    _STRUCT_XMM_REG __fpu_ymmh7;
    _STRUCT_OPMASK_REG __fpu_k0;
    _STRUCT_OPMASK_REG __fpu_k1;
    _STRUCT_OPMASK_REG __fpu_k2;
    _STRUCT_OPMASK_REG __fpu_k3;
    _STRUCT_OPMASK_REG __fpu_k4;
    _STRUCT_OPMASK_REG __fpu_k5;
    _STRUCT_OPMASK_REG __fpu_k6;
    _STRUCT_OPMASK_REG __fpu_k7;
    _STRUCT_YMM_REG __fpu_zmmh0;
    _STRUCT_YMM_REG __fpu_zmmh1;
    _STRUCT_YMM_REG __fpu_zmmh2;
    _STRUCT_YMM_REG __fpu_zmmh3;
    _STRUCT_YMM_REG __fpu_zmmh4;
    _STRUCT_YMM_REG __fpu_zmmh5;
    _STRUCT_YMM_REG __fpu_zmmh6;
    _STRUCT_YMM_REG __fpu_zmmh7;
} _STRUCT_X86_AVX512_STATE32;

typedef struct {
    uint16_t __trapno;
    uint16_t __cpu;
    uint32_t __err;
    uint32_t __faultvaddr;
} _STRUCT_X86_EXCEPTION_STATE32;

typedef struct {
    unsigned int __dr0;
    unsigned int __dr1;
    unsigned int __dr2;
    unsigned int __dr3;
    unsigned int __dr4;
    unsigned int __dr5;
    unsigned int __dr6;
    unsigned int __dr7;
} _STRUCT_X86_DEBUG_STATE32;

typedef struct _STRUCT_X86_THREAD_STATE64 {
    uint64_t __rax;
    uint64_t __rbx;
    uint64_t __rcx;
    uint64_t __rdx;
    uint64_t __rdi;
    uint64_t __rsi;
    uint64_t __rbp;
    uint64_t __rsp;
    uint64_t __r8;
    uint64_t __r9;
    uint64_t __r10;
    uint64_t __r11;
    uint64_t __r12;
    uint64_t __r13;
    uint64_t __r14;
    uint64_t __r15;
    uint64_t __rip;
    uint64_t __rflags;
    uint64_t __cs;
    uint64_t __fs;
    uint64_t __gs;
} _STRUCT_X86_THREAD_STATE64;

typedef struct {
    int __fpu_reserved[2];
    _STRUCT_FP_CONTROL __fpu_fcw;
    _STRUCT_FP_STATUS __fpu_fsw;
    uint8_t __fpu_ftw;
    uint8_t __fpu_rsrv1;
    uint16_t __fpu_fop;

    uint32_t __fpu_ip;
    uint16_t __fpu_cs;

    uint16_t __fpu_rsrv2;

    uint32_t __fpu_dp;
    uint16_t __fpu_ds;

    uint16_t __fpu_rsrv3;
    uint32_t __fpu_mxcsr;
    uint32_t __fpu_mxcsrmask;
    _STRUCT_MMST_REG __fpu_stmm0;
    _STRUCT_MMST_REG __fpu_stmm1;
    _STRUCT_MMST_REG __fpu_stmm2;
    _STRUCT_MMST_REG __fpu_stmm3;
    _STRUCT_MMST_REG __fpu_stmm4;
    _STRUCT_MMST_REG __fpu_stmm5;
    _STRUCT_MMST_REG __fpu_stmm6;
    _STRUCT_MMST_REG __fpu_stmm7;
    _STRUCT_XMM_REG __fpu_xmm0;
    _STRUCT_XMM_REG __fpu_xmm1;
    _STRUCT_XMM_REG __fpu_xmm2;
    _STRUCT_XMM_REG __fpu_xmm3;
    _STRUCT_XMM_REG __fpu_xmm4;
    _STRUCT_XMM_REG __fpu_xmm5;
    _STRUCT_XMM_REG __fpu_xmm6;
    _STRUCT_XMM_REG __fpu_xmm7;
    _STRUCT_XMM_REG __fpu_xmm8;
    _STRUCT_XMM_REG __fpu_xmm9;
    _STRUCT_XMM_REG __fpu_xmm10;
    _STRUCT_XMM_REG __fpu_xmm11;
    _STRUCT_XMM_REG __fpu_xmm12;
    _STRUCT_XMM_REG __fpu_xmm13;
    _STRUCT_XMM_REG __fpu_xmm14;
    _STRUCT_XMM_REG __fpu_xmm15;
    char __fpu_rsrv4[6 * 16];
    int __fpu_reserved1;
} _STRUCT_X86_FLOAT_STATE64;

typedef struct {
    int __fpu_reserved[2];
    _STRUCT_FP_CONTROL __fpu_fcw;
    _STRUCT_FP_STATUS __fpu_fsw;
    uint8_t __fpu_ftw;
    uint8_t __fpu_rsrv1;
    uint16_t __fpu_fop;

    uint32_t __fpu_ip;
    uint16_t __fpu_cs;

    uint16_t __fpu_rsrv2;

    uint32_t __fpu_dp;
    uint16_t __fpu_ds;

    uint16_t __fpu_rsrv3;
    uint32_t __fpu_mxcsr;
    uint32_t __fpu_mxcsrmask;
    _STRUCT_MMST_REG __fpu_stmm0;
    _STRUCT_MMST_REG __fpu_stmm1;
    _STRUCT_MMST_REG __fpu_stmm2;
    _STRUCT_MMST_REG __fpu_stmm3;
    _STRUCT_MMST_REG __fpu_stmm4;
    _STRUCT_MMST_REG __fpu_stmm5;
    _STRUCT_MMST_REG __fpu_stmm6;
    _STRUCT_MMST_REG __fpu_stmm7;
    _STRUCT_XMM_REG __fpu_xmm0;
    _STRUCT_XMM_REG __fpu_xmm1;
    _STRUCT_XMM_REG __fpu_xmm2;
    _STRUCT_XMM_REG __fpu_xmm3;
    _STRUCT_XMM_REG __fpu_xmm4;
    _STRUCT_XMM_REG __fpu_xmm5;
    _STRUCT_XMM_REG __fpu_xmm6;
    _STRUCT_XMM_REG __fpu_xmm7;
    _STRUCT_XMM_REG __fpu_xmm8;
    _STRUCT_XMM_REG __fpu_xmm9;
    _STRUCT_XMM_REG __fpu_xmm10;
    _STRUCT_XMM_REG __fpu_xmm11;
    _STRUCT_XMM_REG __fpu_xmm12;
    _STRUCT_XMM_REG __fpu_xmm13;
    _STRUCT_XMM_REG __fpu_xmm14;
    _STRUCT_XMM_REG __fpu_xmm15;
    char __fpu_rsrv4[6 * 16];
    int __fpu_reserved1;
    char __avx_reserved1[64];
    _STRUCT_XMM_REG __fpu_ymmh0;
    _STRUCT_XMM_REG __fpu_ymmh1;
    _STRUCT_XMM_REG __fpu_ymmh2;
    _STRUCT_XMM_REG __fpu_ymmh3;
    _STRUCT_XMM_REG __fpu_ymmh4;
    _STRUCT_XMM_REG __fpu_ymmh5;
    _STRUCT_XMM_REG __fpu_ymmh6;
    _STRUCT_XMM_REG __fpu_ymmh7;
    _STRUCT_XMM_REG __fpu_ymmh8;
    _STRUCT_XMM_REG __fpu_ymmh9;
    _STRUCT_XMM_REG __fpu_ymmh10;
    _STRUCT_XMM_REG __fpu_ymmh11;
    _STRUCT_XMM_REG __fpu_ymmh12;
    _STRUCT_XMM_REG __fpu_ymmh13;
    _STRUCT_XMM_REG __fpu_ymmh14;
    _STRUCT_XMM_REG __fpu_ymmh15;
} _STRUCT_X86_AVX_STATE64;

typedef struct {
    int __fpu_reserved[2];
    _STRUCT_FP_CONTROL __fpu_fcw;
    _STRUCT_FP_STATUS __fpu_fsw;
    uint8_t __fpu_ftw;
    uint8_t __fpu_rsrv1;
    uint16_t __fpu_fop;

    uint32_t __fpu_ip;
    uint16_t __fpu_cs;

    uint16_t __fpu_rsrv2;

    uint32_t __fpu_dp;
    uint16_t __fpu_ds;

    uint16_t __fpu_rsrv3;
    uint32_t __fpu_mxcsr;
    uint32_t __fpu_mxcsrmask;
    _STRUCT_MMST_REG __fpu_stmm0;
    _STRUCT_MMST_REG __fpu_stmm1;
    _STRUCT_MMST_REG __fpu_stmm2;
    _STRUCT_MMST_REG __fpu_stmm3;
    _STRUCT_MMST_REG __fpu_stmm4;
    _STRUCT_MMST_REG __fpu_stmm5;
    _STRUCT_MMST_REG __fpu_stmm6;
    _STRUCT_MMST_REG __fpu_stmm7;
    _STRUCT_XMM_REG __fpu_xmm0;
    _STRUCT_XMM_REG __fpu_xmm1;
    _STRUCT_XMM_REG __fpu_xmm2;
    _STRUCT_XMM_REG __fpu_xmm3;
    _STRUCT_XMM_REG __fpu_xmm4;
    _STRUCT_XMM_REG __fpu_xmm5;
    _STRUCT_XMM_REG __fpu_xmm6;
    _STRUCT_XMM_REG __fpu_xmm7;
    _STRUCT_XMM_REG __fpu_xmm8;
    _STRUCT_XMM_REG __fpu_xmm9;
    _STRUCT_XMM_REG __fpu_xmm10;
    _STRUCT_XMM_REG __fpu_xmm11;
    _STRUCT_XMM_REG __fpu_xmm12;
    _STRUCT_XMM_REG __fpu_xmm13;
    _STRUCT_XMM_REG __fpu_xmm14;
    _STRUCT_XMM_REG __fpu_xmm15;
    char __fpu_rsrv4[6 * 16];
    int __fpu_reserved1;
    char __avx_reserved1[64];
    _STRUCT_XMM_REG __fpu_ymmh0;
    _STRUCT_XMM_REG __fpu_ymmh1;
    _STRUCT_XMM_REG __fpu_ymmh2;
    _STRUCT_XMM_REG __fpu_ymmh3;
    _STRUCT_XMM_REG __fpu_ymmh4;
    _STRUCT_XMM_REG __fpu_ymmh5;
    _STRUCT_XMM_REG __fpu_ymmh6;
    _STRUCT_XMM_REG __fpu_ymmh7;
    _STRUCT_XMM_REG __fpu_ymmh8;
    _STRUCT_XMM_REG __fpu_ymmh9;
    _STRUCT_XMM_REG __fpu_ymmh10;
    _STRUCT_XMM_REG __fpu_ymmh11;
    _STRUCT_XMM_REG __fpu_ymmh12;
    _STRUCT_XMM_REG __fpu_ymmh13;
    _STRUCT_XMM_REG __fpu_ymmh14;
    _STRUCT_XMM_REG __fpu_ymmh15;
    _STRUCT_OPMASK_REG __fpu_k0;
    _STRUCT_OPMASK_REG __fpu_k1;
    _STRUCT_OPMASK_REG __fpu_k2;
    _STRUCT_OPMASK_REG __fpu_k3;
    _STRUCT_OPMASK_REG __fpu_k4;
    _STRUCT_OPMASK_REG __fpu_k5;
    _STRUCT_OPMASK_REG __fpu_k6;
    _STRUCT_OPMASK_REG __fpu_k7;
    _STRUCT_YMM_REG __fpu_zmmh0;
    _STRUCT_YMM_REG __fpu_zmmh1;
    _STRUCT_YMM_REG __fpu_zmmh2;
    _STRUCT_YMM_REG __fpu_zmmh3;
    _STRUCT_YMM_REG __fpu_zmmh4;
    _STRUCT_YMM_REG __fpu_zmmh5;
    _STRUCT_YMM_REG __fpu_zmmh6;
    _STRUCT_YMM_REG __fpu_zmmh7;
    _STRUCT_YMM_REG __fpu_zmmh8;
    _STRUCT_YMM_REG __fpu_zmmh9;
    _STRUCT_YMM_REG __fpu_zmmh10;
    _STRUCT_YMM_REG __fpu_zmmh11;
    _STRUCT_YMM_REG __fpu_zmmh12;
    _STRUCT_YMM_REG __fpu_zmmh13;
    _STRUCT_YMM_REG __fpu_zmmh14;
    _STRUCT_YMM_REG __fpu_zmmh15;
    _STRUCT_ZMM_REG __fpu_zmm16;
    _STRUCT_ZMM_REG __fpu_zmm17;
    _STRUCT_ZMM_REG __fpu_zmm18;
    _STRUCT_ZMM_REG __fpu_zmm19;
    _STRUCT_ZMM_REG __fpu_zmm20;
    _STRUCT_ZMM_REG __fpu_zmm21;
    _STRUCT_ZMM_REG __fpu_zmm22;
    _STRUCT_ZMM_REG __fpu_zmm23;
    _STRUCT_ZMM_REG __fpu_zmm24;
    _STRUCT_ZMM_REG __fpu_zmm25;
    _STRUCT_ZMM_REG __fpu_zmm26;
    _STRUCT_ZMM_REG __fpu_zmm27;
    _STRUCT_ZMM_REG __fpu_zmm28;
    _STRUCT_ZMM_REG __fpu_zmm29;
    _STRUCT_ZMM_REG __fpu_zmm30;
    _STRUCT_ZMM_REG __fpu_zmm31;
} _STRUCT_X86_AVX512_STATE64;

typedef struct {
    uint16_t __trapno;
    uint16_t __cpu;
    uint32_t __err;
    uint64_t __faultvaddr;
} _STRUCT_X86_EXCEPTION_STATE64;

typedef struct {
    uint64_t __dr0;
    uint64_t __dr1;
    uint64_t __dr2;
    uint64_t __dr3;
    uint64_t __dr4;
    uint64_t __dr5;
    uint64_t __dr6;
    uint64_t __dr7;
} _STRUCT_X86_DEBUG_STATE64;

typedef struct {
    uint64_t __ctrs[16];
} _STRUCT_X86_CPMU_STATE64;

#endif // LD64_MACH_I386__STRUCTS_H_
