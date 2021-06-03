// https://opensource.apple.com/source/xnu/xnu-4903.221.2/EXTERNAL_HEADERS/mach-o/fat.h
#ifndef LD64_MACH_O_FAT_H_
#define LD64_MACH_O_FAT_H_

struct fat_header {
    uint32_t magic;
    uint32_t nfat_arch;
};

struct fat_arch {
    uint32_t cputype;
    uint32_t cpusubtype;
    uint32_t offset;
    uint32_t size;
    uint32_t align;
};

#endif // LD64_MACH_O_FAT_H_
