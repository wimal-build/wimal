// https://opensource.apple.com/source/xnu/xnu-1504.15.3/EXTERNAL_HEADERS/mach-o/reloc.h
#ifndef LD64_MACHO_RELOC_H_
#define LD64_MACHO_RELOC_H_

#include <stdint.h>

struct relocation_info {
    int32_t r_address;
    uint32_t r_symbolnum:24;
    uint32_t r_pcrel:1;
    uint32_t r_length:2;
    uint32_t r_extern:1;
    uint32_t r_type:4;
};

#define R_ABS 0

#define R_SCATTERED 0x80000000

struct scattered_relocation_info {
#ifdef __BIG_ENDIAN__
    uint32_t r_scattered: 1;
    uint32_t r_pcrel: 1;
    uint32_t r_length: 2;
    uint32_t r_type: 4;
    uint32_t r_address: 24;
    int32_t	r_value;
#endif // __BIG_ENDIAN__

#ifdef __LITTLE_ENDIAN__
    uint32_t r_address: 24;
    uint32_t r_type: 4;
    uint32_t r_length: 2;
    uint32_t r_pcrel: 1;
    uint32_t r_scattered: 1;
    int32_t r_value;
#endif // __LITTLE_ENDIAN__
};

enum reloc_type_generic {
    GENERIC_RELOC_VANILLA,
    GENERIC_RELOC_PAIR,
    GENERIC_RELOC_SECTDIFF,
    GENERIC_RELOC_PB_LA_PTR,
    GENERIC_RELOC_LOCAL_SECTDIFF,
    GENERIC_RELOC_TLV
};

#endif // _MACHO_RELOC_H_
