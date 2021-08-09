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
    auto cc = context->clang / "bin" / CcForAction(context->action);
    auto filename = cc.filename();
    std::vector<std::string> args = {
        cc.filename().string(),
        "-target", context->triple,
        "--sysroot", context->sysroot.string(),
        // Avoid clang using system c++ include path.
        "--prefix", context->toolchain.string(),
        "-Qunused-arguments"
    };
    if (context->machine != Context::MACHINE_X64_MINGW) {
        args.insert(
            args.end(), {
                "-nostdinc++",
                "-cxx-isystem" + (context->sysroot / "usr" / "include" / "c++" / "v1").string(),
                "-stdlib=libc++"
            }
        );
    }
    // Define the api levels for android and darwin targets.
    switch (context->machine) {
        case Context::MACHINE_ARM_ANDROID:
        case Context::MACHINE_X86_ANDROID:
            args.emplace_back("-DANDROID");
            args.emplace_back("-D__ANDROID_API__=17");
            break;
        case Context::MACHINE_A64_ANDROID:
        case Context::MACHINE_X64_ANDROID:
            args.emplace_back("-DANDROID");
            args.emplace_back("-D__ANDROID_API__=21");
            break;
        case Context::MACHINE_X64_MACOS:
        case Context::MACHINE_A64_MACOS:
            args.emplace_back("-mmacosx-version-min=10.10");
            break;
        case Context::MACHINE_ARM_IOS:
        case Context::MACHINE_A64_IOS:
            args.emplace_back("-miphoneos-version-min=9.0");
            break;
        case Context::MACHINE_X86_IOS:
        case Context::MACHINE_X64_IOS:
            args.emplace_back("-mios-simulator-version-min=9.0");
            break;
        default: {
            break;
        }
    }
    // Fix the compilation error: "_Float16 is not supported on this target".
    // See: https://clang.llvm.org/docs/LanguageExtensions.html#half-precision-floating-point
    switch (context->machine) {
        case Context::MACHINE_X86_ANDROID:
        case Context::MACHINE_X64_ANDROID:
            args.emplace_back("-U__FLT16_MANT_DIG__");
            break;
        default: {
            break;
        }
    }
    // Fix debuging on android.
    // See: https://github.com/android-ndk/ndk/issues/885
    switch (context->machine) {
        case Context::MACHINE_ARM_ANDROID:
        case Context::MACHINE_A64_ANDROID:
        case Context::MACHINE_X86_ANDROID:
        case Context::MACHINE_X64_ANDROID:
            args.emplace_back("-Wl,--build-id=sha1");
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
        if (context->machine == Context::MACHINE_X64_MINGW) {
            if (arg == "-fPIC") {
                continue;
            }
        }
        arguments.emplace_back(arg.data());
    }
    for (const auto &arg : extraArgs) {
        arguments.emplace_back(arg.data());
    }
    arguments.emplace_back(nullptr);
    execvp(cc.string().data(), const_cast<char *const *>(arguments.data()));
}

}
