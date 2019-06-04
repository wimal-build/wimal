//===- tapi/Core/Architecture.h - Architecture ------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief Defines architecture enum.
///
//===----------------------------------------------------------------------===//

#ifndef TAPI_CORE_ARCHITECTURE_H
#define TAPI_CORE_ARCHITECTURE_H

#include "tapi/Core/LLVM.h"
#include "tapi/Defines.h"
#include "llvm/ADT/StringRef.h"

TAPI_NAMESPACE_INTERNAL_BEGIN

enum class Architecture : uint8_t {
#define ARCHINFO(arch, type, subtype) arch,
#include "tapi/Core/Architecture.def"
#undef ARCHINFO
  unknown, // this has to go last.
};

Architecture getArchType(uint32_t CPUType, uint32_t CPUSubType);
Architecture getArchType(StringRef name);
StringRef getArchName(Architecture arch);
std::pair<uint32_t, uint32_t> getCPUType(Architecture arch);

raw_ostream &operator<<(raw_ostream &os, Architecture arch);

const DiagnosticBuilder &operator<<(const DiagnosticBuilder &db,
                                    Architecture arch);

TAPI_NAMESPACE_INTERNAL_END

#endif // TAPI_CORE_ARCHITECTURE_H
