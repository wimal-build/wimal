#include "cmakebuild.hpp"

#include <unistd.h>

#include "context.hpp"
#include "export.hpp"

namespace wimal {

void CmakeBuild::Run(const Context *context, std::vector<std::string> extraArgs) {
    Export(context);

    std::string systemName = "Linux";
    switch (context->machine) {
        case Context::MACHINE_ARM_IOS:
        case Context::MACHINE_A64_IOS:
        case Context::MACHINE_X86_IOS:
        case Context::MACHINE_X64_IOS:
        case Context::MACHINE_X64_MACOS:
            systemName = "Darwin";
            break;
        default: {
            break;
        }
    }

    std::vector<std::string> args = {
        "cmake",
        "-DCMAKE_C_COMPILER_ID=Clang",
        "-DCMAKE_CXX_COMPILER_ID=Clang",
        "-DCMAKE_BUILD_TYPE=Release",
        "-DCMAKE_OSX_SYSROOT=" + systemName,
        "-DCMAKE_C_COMPILER=" + (context->bin / (context->target + "-cc")).string(),
        "-DCMAKE_CXX_COMPILER=" + (context->bin / (context->target + "-c++")).string(),
        "-DCMAKE_AR=" + (context->bin / (context->target + "-ar")).string(),
        "-DCMAKE_LINKER=" + (context->bin / (context->target + "-ld")).string(),
        "-DCMAKE_RANLIB=" + (context->bin / (context->target + "-ranlib")).string(),
        "-DCMAKE_STRIP=" + (context->bin / (context->target + "-strip")).string(),
        "-DCMAKE_INSTALL_PREFIX=" + (context->cwd / "targets").string(),
        "-DCMAKE_OSX_SYSROOT=" + context->sysroot.string(),
        "-DCMAKE_FIND_ROOT_PATH=" + context->sysroot.string(),
        "-DCMAKE_POSITION_INDEPENDENT_CODE=ON",
        "-DCMAKE_FIND_ROOT_PATH_MODE_PROGRAM=NEVER",
        "-DCMAKE_FIND_ROOT_PATH_MODE_LIBRARY=ONLY",
        "-DCMAKE_FIND_ROOT_PATH_MODE_INCLUDE=ONLY",
        "-DCMAKE_FIND_ROOT_PATH_MODE_PACKAGE=ONLY",
        "-DCMAKE_LINK_SEARCH_START_STATIC=1",
        "--no-warn-unused-cli"
    };
    std::vector<const char *> arguments;
    arguments.reserve(args.size() + context->args.size() + extraArgs.size() + 1);
    for (const auto &arg : args) {
        arguments.emplace_back(arg.data());
    }
    for (const auto &arg : context->args) {
        arguments.emplace_back(arg.data());
    }
    for (const auto &arg : extraArgs) {
        arguments.emplace_back(arg.data());
    }
    arguments.emplace_back(nullptr);
    execvp("cmake", (char *const *) arguments.data());
}

}
