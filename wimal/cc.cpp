#include "cc.hpp"

#include <unistd.h>

#include "context.hpp"

namespace wimal {

static inline std::string CcForAction(const std::string &action) {
    if (action == "cc") {
        return "clang";
    } else if (action == "c++") {
        return "clang++";
    } else if (action == "cpp") {
        return "clang-cpp";
    } else {
        abort();
    }
}

void Cc::Run(const Context *context, std::vector<std::string> extraArgs) {
    auto gcc = context->sysroot / "usr";
    auto cc = context->clang / "bin" / CcForAction(context->action);
    auto filename = cc.filename();
    std::vector<std::string> args = {
        cc.filename().string(),
        "-target", context->triple,
        "--sysroot", context->sysroot.string(),
        "--prefix", context->toolchain.string(),
        "-Qunused-arguments",
        "-stdlib=libc++"
    };
    switch (context->machine) {
        case Context::MACHINE_ARM_ANDROID:
        case Context::MACHINE_X86_ANDROID:
            args.emplace_back("-D__ANDROID_API__=17");
            break;
        case Context::MACHINE_A64_ANDROID:
        case Context::MACHINE_X64_ANDROID:
            args.emplace_back("-D__ANDROID_API__=21");
            break;
        default: {
            break;
        }
    }
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
    execvp(cc.string().data(), (char *const *) arguments.data());
}

}
