// https://opensource.apple.com/source/xnu/xnu-4903.221.2/osfmk/mach/i386/_structs.h
#ifndef CCTOOLS_MACH_I386__STRUCTS_H_
#define CCTOOLS_MACH_I386__STRUCTS_H_

#ifndef __APPLE__
#define __uint8_t uint8_t
#define __uint16_t uint16_t
#define __uint32_t uint32_t
#define __uint64_t uint64_t
#endif // __APPLE__

#include_next <mach/i386/_structs.h>

#ifndef _STRUCT_OPMASK_REG
#define _STRUCT_OPMASK_REG struct opmask_reg
_STRUCT_OPMASK_REG {
    char opmask_reg[8];
};
#endif // _STRUCT_OPMASK_REG

#ifndef _STRUCT_YMM_REG
#define _STRUCT_YMM_REG struct ymm_reg
_STRUCT_YMM_REG {
    char ymm_reg[32];
};
#endif // _STRUCT_YMM_REG

#ifndef _STRUCT_ZMM_REG
#define _STRUCT_ZMM_REG struct zmm_reg
_STRUCT_ZMM_REG {
    char zmm_reg[64];
};
#endif // _STRUCT_ZMM_REG

#ifndef _STRUCT_X86_AVX512_STATE32
#define _STRUCT_X86_AVX512_STATE32 struct i386_avx512_state
_STRUCT_X86_AVX512_STATE32 {
    int __fpu_reserved[2];
    _STRUCT_FP_CONTROL __fpu_fcw;
    _STRUCT_FP_STATUS __fpu_fsw;
    __uint8_t __fpu_ftw;
    __uint8_t __fpu_rsrv1;
    __uint16_t __fpu_fop;
    __uint32_t __fpu_ip;
    __uint16_t __fpu_cs;
    __uint16_t __fpu_rsrv2;
    __uint32_t __fpu_dp;
    __uint16_t __fpu_ds;
    __uint16_t __fpu_rsrv3;
    __uint32_t __fpu_mxcsr;
    __uint32_t __fpu_mxcsrmask;
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
};
#endif // _STRUCT_X86_AVX512_STATE32

#ifndef _STRUCT_X86_AVX512_STATE64
#define _STRUCT_X86_AVX512_STATE64 struct x86_avx512_state64
_STRUCT_X86_AVX512_STATE64 {
    int fpu_reserved[2];
    _STRUCT_FP_CONTROL fpu_fcw;
    _STRUCT_FP_STATUS fpu_fsw;
    __uint8_t fpu_ftw;
    __uint8_t fpu_rsrv1;
    __uint16_t fpu_fop;

    __uint32_t fpu_ip;
    __uint16_t fpu_cs;

    __uint16_t fpu_rsrv2;

    __uint32_t fpu_dp;
    __uint16_t fpu_ds;

    __uint16_t fpu_rsrv3;
    __uint32_t fpu_mxcsr;
    __uint32_t fpu_mxcsrmask;
    _STRUCT_MMST_REG fpu_stmm0;
    _STRUCT_MMST_REG fpu_stmm1;
    _STRUCT_MMST_REG fpu_stmm2;
    _STRUCT_MMST_REG fpu_stmm3;
    _STRUCT_MMST_REG fpu_stmm4;
    _STRUCT_MMST_REG fpu_stmm5;
    _STRUCT_MMST_REG fpu_stmm6;
    _STRUCT_MMST_REG fpu_stmm7;
    _STRUCT_XMM_REG fpu_xmm0;
    _STRUCT_XMM_REG fpu_xmm1;
    _STRUCT_XMM_REG fpu_xmm2;
    _STRUCT_XMM_REG fpu_xmm3;
    _STRUCT_XMM_REG fpu_xmm4;
    _STRUCT_XMM_REG fpu_xmm5;
    _STRUCT_XMM_REG fpu_xmm6;
    _STRUCT_XMM_REG fpu_xmm7;
    _STRUCT_XMM_REG fpu_xmm8;
    _STRUCT_XMM_REG fpu_xmm9;
    _STRUCT_XMM_REG fpu_xmm10;
    _STRUCT_XMM_REG fpu_xmm11;
    _STRUCT_XMM_REG fpu_xmm12;
    _STRUCT_XMM_REG fpu_xmm13;
    _STRUCT_XMM_REG fpu_xmm14;
    _STRUCT_XMM_REG fpu_xmm15;
    char fpu_rsrv4[6 * 16];
    int fpu_reserved1;
    char avx_reserved1[64];
    _STRUCT_XMM_REG fpu_ymmh0;
    _STRUCT_XMM_REG fpu_ymmh1;
    _STRUCT_XMM_REG fpu_ymmh2;
    _STRUCT_XMM_REG fpu_ymmh3;
    _STRUCT_XMM_REG fpu_ymmh4;
    _STRUCT_XMM_REG fpu_ymmh5;
    _STRUCT_XMM_REG fpu_ymmh6;
    _STRUCT_XMM_REG fpu_ymmh7;
    _STRUCT_XMM_REG fpu_ymmh8;
    _STRUCT_XMM_REG fpu_ymmh9;
    _STRUCT_XMM_REG fpu_ymmh10;
    _STRUCT_XMM_REG fpu_ymmh11;
    _STRUCT_XMM_REG fpu_ymmh12;
    _STRUCT_XMM_REG fpu_ymmh13;
    _STRUCT_XMM_REG fpu_ymmh14;
    _STRUCT_XMM_REG fpu_ymmh15;
    _STRUCT_OPMASK_REG fpu_k0;
    _STRUCT_OPMASK_REG fpu_k1;
    _STRUCT_OPMASK_REG fpu_k2;
    _STRUCT_OPMASK_REG fpu_k3;
    _STRUCT_OPMASK_REG fpu_k4;
    _STRUCT_OPMASK_REG fpu_k5;
    _STRUCT_OPMASK_REG fpu_k6;
    _STRUCT_OPMASK_REG fpu_k7;
    _STRUCT_YMM_REG fpu_zmmh0;
    _STRUCT_YMM_REG fpu_zmmh1;
    _STRUCT_YMM_REG fpu_zmmh2;
    _STRUCT_YMM_REG fpu_zmmh3;
    _STRUCT_YMM_REG fpu_zmmh4;
    _STRUCT_YMM_REG fpu_zmmh5;
    _STRUCT_YMM_REG fpu_zmmh6;
    _STRUCT_YMM_REG fpu_zmmh7;
    _STRUCT_YMM_REG fpu_zmmh8;
    _STRUCT_YMM_REG fpu_zmmh9;
    _STRUCT_YMM_REG fpu_zmmh10;
    _STRUCT_YMM_REG fpu_zmmh11;
    _STRUCT_YMM_REG fpu_zmmh12;
    _STRUCT_YMM_REG fpu_zmmh13;
    _STRUCT_YMM_REG fpu_zmmh14;
    _STRUCT_YMM_REG fpu_zmmh15;
    _STRUCT_ZMM_REG fpu_zmm16;
    _STRUCT_ZMM_REG fpu_zmm17;
    _STRUCT_ZMM_REG fpu_zmm18;
    _STRUCT_ZMM_REG fpu_zmm19;
    _STRUCT_ZMM_REG fpu_zmm20;
    _STRUCT_ZMM_REG fpu_zmm21;
    _STRUCT_ZMM_REG fpu_zmm22;
    _STRUCT_ZMM_REG fpu_zmm23;
    _STRUCT_ZMM_REG fpu_zmm24;
    _STRUCT_ZMM_REG fpu_zmm25;
    _STRUCT_ZMM_REG fpu_zmm26;
    _STRUCT_ZMM_REG fpu_zmm27;
    _STRUCT_ZMM_REG fpu_zmm28;
    _STRUCT_ZMM_REG fpu_zmm29;
    _STRUCT_ZMM_REG fpu_zmm30;
    _STRUCT_ZMM_REG fpu_zmm31;
};
#endif // _STRUCT_X86_AVX512_STATE64

#endif // CCTOOLS_MACH_I386__STRUCTS_H_
