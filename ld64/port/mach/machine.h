// https://opensource.apple.com/source/xnu/xnu-4903.221.2/osfmk/mach/machine.h
#ifndef LD64_MACH_MACHINE_H_
#define LD64_MACH_MACHINE_H_

#include <llvm/Object/MachO.h>

#ifdef __APPLE__
#include_next <mach/machine.h>

#ifndef CPU_SUBTYPE_ARM64_E
#define CPU_SUBTYPE_ARM64_E 2
#endif // CPU_SUBTYPE_ARM64_E
#else // !__APPLE__

typedef int cpu_type_t;

typedef int cpu_subtype_t;

using llvm::MachO::CPU_ARCH_MASK;
using llvm::MachO::CPU_ARCH_ABI64;

using llvm::MachO::CPU_TYPE_X86;
using llvm::MachO::CPU_TYPE_I386;
using llvm::MachO::CPU_TYPE_X86_64;
using llvm::MachO::CPU_TYPE_ARM;
using llvm::MachO::CPU_TYPE_ARM64;

using llvm::MachO::CPU_SUBTYPE_MASK;

using llvm::MachO::CPU_SUBTYPE_I386_ALL;
using llvm::MachO::CPU_SUBTYPE_X86_ALL;
using llvm::MachO::CPU_SUBTYPE_X86_64_ALL;
using llvm::MachO::CPU_SUBTYPE_X86_64_H;

using llvm::MachO::CPU_SUBTYPE_ARM_ALL;
using llvm::MachO::CPU_SUBTYPE_ARM_V6;
using llvm::MachO::CPU_SUBTYPE_ARM_V7;
using llvm::MachO::CPU_SUBTYPE_ARM_V7S;
using llvm::MachO::CPU_SUBTYPE_ARM_V7K;
using llvm::MachO::CPU_SUBTYPE_ARM_V6M;
using llvm::MachO::CPU_SUBTYPE_ARM_V7M;
using llvm::MachO::CPU_SUBTYPE_ARM_V7EM;

using llvm::MachO::CPU_SUBTYPE_ARM64_ALL;

// https://opensource.apple.com/source/dyld/dyld-635.2/src/dyld.cpp
enum : uint32_t {
    CPU_SUBTYPE_ARM64_E = 2
};

#endif // __APPLE__

#endif // LD64_MACH_MACHINE_H_
