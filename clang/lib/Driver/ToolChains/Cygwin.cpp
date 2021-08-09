//===--- Cygwin.cpp - CygwinToolChain Implementation ------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "Cygwin.h"
#include "InputInfo.h"
#include "CommonArgs.h"
#include "clang/Driver/Compilation.h"
#include "clang/Driver/Driver.h"
#include "clang/Driver/DriverDiagnostic.h"
#include "clang/Driver/Options.h"
#include "llvm/Option/ArgList.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/Path.h"
#include <system_error>

using namespace clang::diag;
using namespace clang::driver;
using namespace clang;
using namespace llvm::opt;

/// Cygwin Tools
void tools::Cygwin::Assembler::ConstructJob(Compilation &C, const JobAction &JA,
                                           const InputInfo &Output,
                                           const InputInfoList &Inputs,
                                           const ArgList &Args,
                                           const char *LinkingOutput) const {
  claimNoWarnArgs(Args);
  ArgStringList CmdArgs;

  if (getToolChain().getArch() == llvm::Triple::x86) {
    CmdArgs.push_back("--32");
  } else if (getToolChain().getArch() == llvm::Triple::x86_64) {
    CmdArgs.push_back("--64");
  }

  Args.AddAllArgValues(CmdArgs, options::OPT_Wa_COMMA, options::OPT_Xassembler);

  CmdArgs.push_back("-o");
  CmdArgs.push_back(Output.getFilename());

  for (const auto &II : Inputs)
    CmdArgs.push_back(II.getFilename());

  const char *Exec = Args.MakeArgString(getToolChain().GetProgramPath("as"));
  C.addCommand(std::make_unique<Command>(JA, *this, ResponseFileSupport::None(),
                                         Exec, CmdArgs, Inputs));

  if (Args.hasArg(options::OPT_gsplit_dwarf))
    SplitDebugInfo(getToolChain(), C, *this, JA, Args, Output,
                   SplitDebugName(JA, Args, Inputs[0], Output));
}

void tools::Cygwin::Linker::AddLibGCC(const ArgList &Args,
                                     ArgStringList &CmdArgs) const {
  // Make use of compiler-rt if --rtlib option is used
  ToolChain::RuntimeLibType RLT = getToolChain().GetRuntimeLibType(Args);
  bool Static = Args.hasArg(options::OPT_static_libgcc) ||
                Args.hasArg(options::OPT_static);
  if (RLT == ToolChain::RLT_Libgcc) {

    if (Static) {
      CmdArgs.push_back("-lgcc");
      CmdArgs.push_back("-lgcc_eh");
    } else {
      CmdArgs.push_back("-lgcc_s");
      CmdArgs.push_back("-lgcc");
    }
  } else {
    AddRunTimeLibs(getToolChain(), getToolChain().getDriver(), CmdArgs, Args);
    CmdArgs.push_back("-lunwind");
  }

  CmdArgs.push_back("-lcygwin");
}

void tools::Cygwin::Linker::ConstructJob(Compilation &C, const JobAction &JA,
                                        const InputInfo &Output,
                                        const InputInfoList &Inputs,
                                        const ArgList &Args,
                                        const char *LinkingOutput) const {
  const ToolChain &TC = getToolChain();
  const Driver &D = TC.getDriver();
  // const SanitizerArgs &Sanitize = TC.getSanitizerArgs();

  ArgStringList CmdArgs;

  // Silence warning for "clang -g foo.o -o foo"
  Args.ClaimAllArgs(options::OPT_g_Group);
  // and "clang -emit-llvm foo.o -o foo"
  Args.ClaimAllArgs(options::OPT_emit_llvm);
  // and for "clang -w foo.o -o foo". Other warning options are already
  // handled somewhere else.
  Args.ClaimAllArgs(options::OPT_w);

  if (!D.SysRoot.empty())
    CmdArgs.push_back(Args.MakeArgString("--sysroot=" + D.SysRoot));

  if (Args.hasArg(options::OPT_s))
    CmdArgs.push_back("-s");

  CmdArgs.push_back("-m");
  switch (TC.getArch()) {
  case llvm::Triple::x86:
    CmdArgs.push_back("i386pe");
    break;
  case llvm::Triple::x86_64:
    CmdArgs.push_back("i386pep");
    break;
  default:
    llvm_unreachable("Unsupported target architecture.");
  }

  if (!Args.getLastArgValue(options::OPT_fuse_ld_EQ, "link").equals_lower("lld")) {
    if (TC.getArch() == llvm::Triple::x86) {
      CmdArgs.push_back("--wrap");
      CmdArgs.push_back("_Znwj");
      CmdArgs.push_back("--wrap");
      CmdArgs.push_back("_Znaj");
      CmdArgs.push_back("--wrap");
      CmdArgs.push_back("_ZnwjRKSt9nothrow_t");
      CmdArgs.push_back("--wrap");
      CmdArgs.push_back("_ZnajRKSt9nothrow_t");
    } else {
      CmdArgs.push_back("--wrap");
      CmdArgs.push_back("_Znwm");
      CmdArgs.push_back("--wrap");
      CmdArgs.push_back("_Znam");
      CmdArgs.push_back("--wrap");
      CmdArgs.push_back("_ZnwmRKSt9nothrow_t");
      CmdArgs.push_back("--wrap");
      CmdArgs.push_back("_ZnamRKSt9nothrow_t");
    }
    CmdArgs.push_back("--wrap");
    CmdArgs.push_back("_ZdlPv");
    CmdArgs.push_back("--wrap");
    CmdArgs.push_back("_ZdaPv");
    CmdArgs.push_back("--wrap");
    CmdArgs.push_back("_ZdlPvRKSt9nothrow_t");
    CmdArgs.push_back("--wrap");
    CmdArgs.push_back("_ZdaPvKSt9nothrow_t");
  }

  if (Args.hasArg(options::OPT_mwindows)) {
    CmdArgs.push_back("--subsystem");
    CmdArgs.push_back("windows");
  } else if (Args.hasArg(options::OPT_mconsole)) {
    CmdArgs.push_back("--subsystem");
    CmdArgs.push_back("console");
  }

  if (Args.hasArg(options::OPT_static))
    CmdArgs.push_back("-Bstatic");
  else {
    if (Args.hasArg(options::OPT_mdll))
      CmdArgs.push_back("--dll");
    else if (Args.hasArg(options::OPT_shared))
      CmdArgs.push_back("--shared");
    else if (Args.hasArg(options::OPT_rdynamic))
      CmdArgs.push_back("--export-all-symbols");
    CmdArgs.push_back("-Bdynamic");
    if (Args.hasArg(options::OPT_mdll) || Args.hasArg(options::OPT_shared)) {
      CmdArgs.push_back("-e");
      if (TC.getArch() == llvm::Triple::x86)
        CmdArgs.push_back("__cygwin_dll_entry@12");
      else
        CmdArgs.push_back("_cygwin_dll_entry");
      CmdArgs.push_back("--enable-auto-image-base");
    } else {
      if (TC.getArch() == llvm::Triple::x86)
        CmdArgs.push_back("--large-address-aware");
      CmdArgs.push_back("--tsaware");
    }
  }

  CmdArgs.push_back("-o");
  CmdArgs.push_back(Output.getFilename());

  Args.AddAllArgs(CmdArgs, options::OPT_e);
  // FIXME: add -N, -n flags
  Args.AddLastArg(CmdArgs, options::OPT_r);
  Args.AddLastArg(CmdArgs, options::OPT_s);
  Args.AddLastArg(CmdArgs, options::OPT_t);
  Args.AddAllArgs(CmdArgs, options::OPT_u_Group);
  Args.AddLastArg(CmdArgs, options::OPT_Z_Flag);

  if (!Args.hasArg(options::OPT_nostdlib, options::OPT_nostartfiles)) {
    if (Args.hasArg(options::OPT_shared) || Args.hasArg(options::OPT_mdll)) {
      CmdArgs.push_back(Args.MakeArgString(TC.GetFilePath("crtbeginS.o")));
    } else {
      CmdArgs.push_back(Args.MakeArgString(TC.GetFilePath("crt0.o")));
      if (Args.hasArg(options::OPT_pg))
        CmdArgs.push_back(Args.MakeArgString(TC.GetFilePath("gcrt0.o")));
      CmdArgs.push_back(Args.MakeArgString(TC.GetFilePath("crtbegin.o")));
    }
  }

  Args.AddAllArgs(CmdArgs, options::OPT_L);
  TC.AddFilePathLibArgs(Args, CmdArgs);
  AddLinkerInputs(TC, Inputs, Args, CmdArgs, JA);

  // TODO: Add ASan stuff here

  // TODO: Add profile stuff here

  if (TC.ShouldLinkCXXStdlib(Args)) {
    bool OnlyLibstdcxxStatic = Args.hasArg(options::OPT_static_libstdcxx) &&
                               !Args.hasArg(options::OPT_static);
    if (OnlyLibstdcxxStatic)
      CmdArgs.push_back("-Bstatic");
    TC.AddCXXStdlibLibArgs(Args, CmdArgs);
    if (OnlyLibstdcxxStatic)
      CmdArgs.push_back("-Bdynamic");
  }

  if (!Args.hasArg(options::OPT_nostdlib)) {
    if (!Args.hasArg(options::OPT_nodefaultlibs)) {
      if (Args.hasArg(options::OPT_static))
        CmdArgs.push_back("--start-group");

      if (Args.hasArg(options::OPT_fopenmp))
        CmdArgs.push_back("-lgomp");

      AddLibGCC(Args, CmdArgs);

      if (Args.hasArg(options::OPT_pg))
        CmdArgs.push_back("-lgmon");

      // Add system libraries.
      if (Args.hasArg(options::OPT_mwindows)) {
        CmdArgs.push_back("-lgdi32");
        CmdArgs.push_back("-lcomdlg32");
      }
      CmdArgs.push_back("-ladvapi32");
      CmdArgs.push_back("-lshell32");
      CmdArgs.push_back("-luser32");
      CmdArgs.push_back("-lkernel32");

      if (Args.hasArg(options::OPT_static))
        CmdArgs.push_back("--end-group");
    }

    if (!Args.hasArg(options::OPT_nostartfiles)) {
      // Add crtfastmath.o if available and fast math is enabled.
      TC.addFastMathRuntimeIfAvailable(Args, CmdArgs);

      if (!Args.hasArg(options::OPT_shared))
        CmdArgs.push_back(Args.MakeArgString(TC.GetFilePath("default-manifest.o")));
      CmdArgs.push_back(Args.MakeArgString(TC.GetFilePath("crtend.o")));
    }
  }
  const char *Exec = Args.MakeArgString(TC.GetLinkerPath());
  C.addCommand(std::make_unique<Command>(JA, *this,
                                         ResponseFileSupport::AtFileUTF8(),
                                         Exec, CmdArgs, Inputs));
}

// Simplified from Generic_GCC::GCCInstallationDetector::ScanLibDirForGCCTriple.
static bool findGccVersion(StringRef LibDir, std::string &GccLibDir,
                           std::string &Ver) {
  auto Version = toolchains::Generic_GCC::GCCVersion::Parse("0.0.0");
  std::error_code EC;
  for (llvm::sys::fs::directory_iterator LI(LibDir, EC), LE; !EC && LI != LE;
       LI = LI.increment(EC)) {
    StringRef VersionText = llvm::sys::path::filename(LI->path());
    auto CandidateVersion =
        toolchains::Generic_GCC::GCCVersion::Parse(VersionText);
    if (CandidateVersion.Major == -1)
      continue;
    if (CandidateVersion <= Version)
      continue;
    Ver = std::string(VersionText);
    GccLibDir = LI->path();
  }
  return Ver.size();
}

void toolchains::Cygwin::findGccLibDir() {
  llvm::SmallVector<llvm::SmallString<32>, 2> Archs;
  Archs.emplace_back(getTriple().getArchName());
  Archs[0] += "-pc-cygwin";
  Archs.emplace_back("cygwin");
  if (Arch.empty())
    Arch = std::string(Archs[0].str());
  // lib: Arch Linux, Ubuntu, Windows
  // lib64: openSUSE Linux
  for (StringRef CandidateLib : {"lib", "lib64"}) {
    for (StringRef CandidateArch : Archs) {
      llvm::SmallString<1024> LibDir(Base);
      llvm::sys::path::append(LibDir, CandidateLib, "gcc", CandidateArch);
      if (findGccVersion(LibDir, GccLibDir, Ver)) {
        Arch = std::string(CandidateArch);
        return;
      }
    }
  }
}

llvm::ErrorOr<std::string> toolchains::Cygwin::findGcc() {
  llvm::SmallVector<llvm::SmallString<32>, 2> Gccs;
  Gccs.emplace_back(getTriple().getArchName());
  Gccs[0] += "-pc-cygwin-gcc";
  Gccs.emplace_back("cygwin-gcc");
  // Please do not add "gcc" here
  for (StringRef CandidateGcc : Gccs)
    if (llvm::ErrorOr<std::string> GPPName = llvm::sys::findProgramByName(CandidateGcc))
      return GPPName;
  return make_error_code(std::errc::no_such_file_or_directory);
}

llvm::ErrorOr<std::string> toolchains::Cygwin::findClangRelativeSysroot() {
  llvm::SmallVector<llvm::SmallString<32>, 2> Subdirs;
  Subdirs.emplace_back(getTriple().str());
  Subdirs.emplace_back(getTriple().getArchName());
  Subdirs[1] += "-pc-cygwin";
  StringRef ClangRoot =
      llvm::sys::path::parent_path(getDriver().getInstalledDir());
  StringRef Sep = llvm::sys::path::get_separator();
  for (StringRef CandidateSubdir : Subdirs) {
    if (llvm::sys::fs::is_directory(ClangRoot + Sep + CandidateSubdir)) {
      Arch = std::string(CandidateSubdir);
      return (ClangRoot + Sep + CandidateSubdir).str();
    }
  }
  return make_error_code(std::errc::no_such_file_or_directory);
}

toolchains::Cygwin::Cygwin(const Driver &D, const llvm::Triple &Triple,
                         const ArgList &Args)
    : ToolChain(D, Triple, Args), CudaInstallation(D, Triple, Args) {
  getProgramPaths().push_back(getDriver().getInstalledDir());

  // Look for <clang-bin>/../<triplet>; if found, use <clang-bin>/.. as the
  // base as it could still be a base for a gcc setup with libgcc.
  if (llvm::ErrorOr<std::string> TargetSubdir = findClangRelativeSysroot())
    Base = std::string(llvm::sys::path::parent_path(TargetSubdir.get()));
  else if (llvm::ErrorOr<std::string> GPPName = findGcc())
    Base = std::string(llvm::sys::path::parent_path(
        llvm::sys::path::parent_path(GPPName.get())));
  else
    Base = std::string(
        llvm::sys::path::parent_path(getDriver().getInstalledDir()));

  Base += llvm::sys::path::get_separator();
  findGccLibDir();
  // GccLibDir must precede Base/lib so that the
  // correct crtbegin.o ,cetend.o would be found.
  getFilePaths().push_back(GccLibDir);
  getFilePaths().push_back(
      (Base + Arch + llvm::sys::path::get_separator() + "lib").str());
  getFilePaths().push_back(getDriver().SysRoot + "/usr/lib");
  getFilePaths().push_back(getDriver().SysRoot + "/usr/lib/w32api");
}

bool toolchains::Cygwin::IsIntegratedAssemblerDefault() const { return true; }

Tool *toolchains::Cygwin::getTool(Action::ActionClass AC) const {
  switch (AC) {
  case Action::PreprocessJobClass:
    if (!Preprocessor)
      Preprocessor.reset(new tools::gcc::Preprocessor(*this));
    return Preprocessor.get();
  case Action::CompileJobClass:
    if (!Compiler)
      Compiler.reset(new tools::gcc::Compiler(*this));
    return Compiler.get();
  default:
    return ToolChain::getTool(AC);
  }
}

Tool *toolchains::Cygwin::buildAssembler() const {
  return new tools::Cygwin::Assembler(*this);
}

Tool *toolchains::Cygwin::buildLinker() const {
  return new tools::Cygwin::Linker(*this);
}

bool toolchains::Cygwin::IsUnwindTablesDefault(const ArgList &Args) const {
  return getArch() == llvm::Triple::x86_64;
}

bool toolchains::Cygwin::isPICDefault() const {
  return getArch() == llvm::Triple::x86_64;
}

bool toolchains::Cygwin::isPIEDefault() const { return false; }

bool toolchains::Cygwin::isPICDefaultForced() const {
  return getArch() == llvm::Triple::x86_64;
}

llvm::ExceptionHandling
toolchains::Cygwin::GetExceptionModel(const ArgList &Args) const {
  if (getArch() == llvm::Triple::x86_64)
    return llvm::ExceptionHandling::WinEH;
  return llvm::ExceptionHandling::DwarfCFI;
}

void toolchains::Cygwin::AddCudaIncludeArgs(const ArgList &DriverArgs,
                                           ArgStringList &CC1Args) const {
  CudaInstallation.AddCudaIncludeArgs(DriverArgs, CC1Args);
}

void toolchains::Cygwin::printVerboseInfo(raw_ostream &OS) const {
  CudaInstallation.print(OS);
}

void toolchains::Cygwin::AddClangSystemIncludeArgs(const ArgList &DriverArgs,
                                                  ArgStringList &CC1Args) const {
  if (DriverArgs.hasArg(options::OPT_nostdinc))
    return;

  if (!DriverArgs.hasArg(options::OPT_nobuiltininc)) {
    SmallString<1024> P(getDriver().ResourceDir);
    llvm::sys::path::append(P, "include");
    addSystemInclude(DriverArgs, CC1Args, P.str());
  }

  if (!DriverArgs.hasArg(options::OPT_nostdlibinc))
    addSystemInclude(DriverArgs, CC1Args, getDriver().SysRoot + "/usr/local/include");

  if (!DriverArgs.hasArg(options::OPT_nobuiltininc)) {
    SmallString<1024> P(getDriver().ResourceDir);
    llvm::sys::path::append(P, "include");
    addSystemInclude(DriverArgs, CC1Args, P.str());
  }

  if (DriverArgs.hasArg(options::OPT_nostdlibinc))
    return;

  addSystemInclude(DriverArgs, CC1Args,
                   Base + Arch + llvm::sys::path::get_separator() + "include");
  addSystemInclude(DriverArgs, CC1Args, getDriver().SysRoot + "/usr/include");
  addSystemInclude(DriverArgs, CC1Args, getDriver().SysRoot + "/usr/include/w32api");
}

void toolchains::Cygwin::AddClangCXXStdlibIncludeArgs(
    const ArgList &DriverArgs, ArgStringList &CC1Args) const {
  if (DriverArgs.hasArg(options::OPT_nostdlibinc) ||
      DriverArgs.hasArg(options::OPT_nostdincxx))
    return;

  StringRef Slash = llvm::sys::path::get_separator();

  switch (GetCXXStdlibType(DriverArgs)) {
  case ToolChain::CST_Libcxx:
    addSystemInclude(DriverArgs, CC1Args,
                     Base + "include" + Slash + "c++" + Slash + "v1");
    break;

  case ToolChain::CST_Libstdcxx:
    llvm::SmallVector<llvm::SmallString<1024>, 4> CppIncludeBases;
    CppIncludeBases.emplace_back(Base);
    llvm::sys::path::append(CppIncludeBases[0], Arch, "include", "c++");
    CppIncludeBases.emplace_back(Base);
    llvm::sys::path::append(CppIncludeBases[1], Arch, "include", "c++", Ver);
    CppIncludeBases.emplace_back(Base);
    llvm::sys::path::append(CppIncludeBases[2], "include", "c++", Ver);
    CppIncludeBases.emplace_back(GccLibDir);
    llvm::sys::path::append(CppIncludeBases[3], "include", "c++");
    for (auto &CppIncludeBase : CppIncludeBases) {
      addSystemInclude(DriverArgs, CC1Args, CppIncludeBase);
      CppIncludeBase += Slash;
      addSystemInclude(DriverArgs, CC1Args, CppIncludeBase + Arch);
      addSystemInclude(DriverArgs, CC1Args, CppIncludeBase + "backward");
    }
    break;
  }
}

void toolchains::Cygwin::AddCXXStdlibLibArgs(const ArgList &Args,
                                    ArgStringList &CmdArgs) const {
  switch (GetCXXStdlibType(Args)) {
  case ToolChain::CST_Libcxx:
    CmdArgs.push_back("-lc++");
    CmdArgs.push_back("-lc++abi");
    break;
  case ToolChain::CST_Libstdcxx:
    CmdArgs.push_back("-lstdc++");
    CmdArgs.push_back("-liconv");
    break;
  }
}
