//===- tapi/Core/Architecture.cpp - Architecture ----------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief Implements the architecture.
///
//===----------------------------------------------------------------------===//

#include "tapi/Core/Architecture.h"
#include "tapi/Core/LLVM.h"
#include "tapi/Defines.h"
#include "clang/Basic/Diagnostic.h"
#include "llvm/ADT/StringSwitch.h"
#include "llvm/BinaryFormat/MachO.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

TAPI_NAMESPACE_INTERNAL_BEGIN

Architecture getArchType(uint32_t CPUType, uint32_t CPUSubType) {
#define ARCHINFO(arch, type, subtype)                                          \
  if (CPUType == (type) &&                                                     \
      (CPUSubType & ~MachO::CPU_SUBTYPE_MASK) == (subtype))                    \
    return Architecture::arch;
#include "tapi/Core/Architecture.def"
#undef ARCHINFO

  return Architecture::unknown;
}

Architecture getArchType(StringRef name) {
  return StringSwitch<Architecture>(name)
#define ARCHINFO(arch, type, subtype) .Case(#arch, Architecture::arch)
#include "tapi/Core/Architecture.def"
#undef ARCHINFO
      .Default(Architecture::unknown);
}

StringRef getArchName(Architecture arch) {
  switch (arch) {
#define ARCHINFO(arch, type, subtype)                                          \
  case Architecture::arch:                                                     \
    return #arch;
#include "tapi/Core/Architecture.def"
#undef ARCHINFO
  case Architecture::unknown:
    return "unknown";
  }
}

std::pair<uint32_t, uint32_t> getCPUType(Architecture arch) {
  switch (arch) {
#define ARCHINFO(arch, type, subtype)                                          \
  case Architecture::arch:                                                     \
    return std::make_pair(type, subtype);
#include "tapi/Core/Architecture.def"
#undef ARCHINFO
  case Architecture::unknown:
    return std::make_pair(0, 0);
  }
}

raw_ostream &operator<<(raw_ostream &os, Architecture arch) {
  os << getArchName(arch);
  return os;
}

const DiagnosticBuilder &operator<<(const DiagnosticBuilder &db,
                                    Architecture arch) {
  db.AddString(getArchName(arch));
  return db;
}

TAPI_NAMESPACE_INTERNAL_END
