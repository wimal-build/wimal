// https://opensource.apple.com/source/xnu/xnu-4903.221.2/osfmk/mach/machine.h
#ifndef LD64_MACH_MACHINE_H_
#define LD64_MACH_MACHINE_H_

#import <mach/machine/vm_types.h>
#import <mach/boolean.h>

typedef int cpu_type_t;

typedef int cpu_subtype_t;

#define CPU_ARCH_ABI64 0x01000000

#define CPU_TYPE_X86 ((cpu_type_t) 7)
#define CPU_TYPE_I386 CPU_TYPE_X86
#define CPU_TYPE_X86_64 (CPU_TYPE_X86 | CPU_ARCH_ABI64)

#define CPU_TYPE_ARM ((cpu_type_t) 12)

#define CPU_SUBTYPE_MASK 0xff000000

#define CPU_SUBTYPE_X86_ALL ((cpu_subtype_t) 3)
#define CPU_SUBTYPE_X86_64_ALL ((cpu_subtype_t) 3)

#define CPU_SUBTYPE_INTEL(f, m) ((cpu_subtype_t) (f) + ((m) << 4))

#define CPU_SUBTYPE_I386_ALL CPU_SUBTYPE_INTEL(3, 0)

#define CPU_SUBTYPE_ARM_ALL ((cpu_subtype_t) 0)
#define CPU_SUBTYPE_ARM_V6 ((cpu_subtype_t) 6)

// https://opensource.apple.com/source/dyld/dyld-635.2/src/dyld.cpp
#define CPU_SUBTYPE_ARM64_E ((cpu_subtype_t) 2)

#endif // LD64_MACH_MACHINE_H_
