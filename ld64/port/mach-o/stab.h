// https://opensource.apple.com/source/xnu/xnu-1504.15.3/EXTERNAL_HEADERS/mach-o/stab.h
#ifndef LD64_MACHO_STAB_H_
#define LD64_MACHO_STAB_H_

#define N_GSYM 0x20
#define N_FNAME 0x22
#define N_FUN 0x24
#define N_STSYM 0x26
#define N_LCSYM 0x28
#define N_BNSYM 0x2e
#define N_AST 0x32
#define N_OPT 0x3c
#define N_RSYM 0x40
#define N_SLINE 0x44
#define N_ENSYM 0x4e
#define N_SSYM 0x60
#define N_SO 0x64
#define N_OSO 0x66
#define N_LSYM 0x80
#define N_BINCL 0x82
#define N_SOL 0x84
#define N_PARAMS 0x86
#define N_VERSION 0x88
#define N_OLEVEL 0x8A
#define N_PSYM 0xa0
#define N_EINCL 0xa2
#define N_ENTRY 0xa4
#define N_LBRAC 0xc0
#define N_EXCL 0xc2
#define N_RBRAC 0xe0
#define N_BCOMM 0xe2
#define N_ECOMM 0xe4
#define N_ECOML 0xe8
#define N_LENG 0xfe
#define N_PC 0x30

#endif // LD64_MACHO_STAB_H_
