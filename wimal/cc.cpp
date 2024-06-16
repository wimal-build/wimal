#include "cc.hpp"

#include <json/json.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <unordered_set>

#include "context.hpp"

namespace wimal {

static const std::vector<std::unordered_set<std::string>> kFlagsByNumArgs = {
    {},
    {
        "--analyzer-output",
        "--autocomplete",
        "--config",
        "--cuda-include-ptx",
        "--dyld-prefix",
        "--gcc-toolchain",
        "--gpu-instrument-lib",
        "--gpu-max-threads-per-block",
        "--hip-version",
        "--language",
        "--no-cuda-include-ptx",
        "--output",
        "--prefix",
        "--serialize-diagnostics",
        "--sysroot",
        "--sysroot",
        "--unwindlib",
        "-A",
        "-B",
        "-D",
        "-I",
        "-L",
        "-MF",
        "-MQ",
        "-MT",
        "-T",
        "-U",
        "-Xanalyzer",
        "-Xassembler",
        "-Xassembler",
        "-Xclang",
        "-Xlinker",
        "-Xopenmp-target",
        "-Xpreprocessor",
        "-Xpreprocessor",
        "-Z",
        "-allowable_client",
        "-arch",
        "-arch_only",
        "-arcmt-migrate-report-output",
        "-aux-info",
        "-bundle_loader",
        "-cuid",
        "-current_version",
        "-dependency-dot",
        "-dependency-file",
        "-dsym-dir",
        "-dumpbase",
        "-dumpbase-ext",
        "-dumpdir",
        "-dylib_file",
        "-dylinker_install_name",
        "-e",
        "-entry",
        "-exported_symbols_list",
        "-faligned-new",
        "-ffile-prefix-map",
        "-flinker-output",
        "-force_load",
        "-fplugin",
        "-framework",
        "-fuse-ld",
        "-idirafter",
        "-imacros",
        "-image_base",
        "-imultilib",
        "-include",
        "-init",
        "-install_name",
        "-interface-stub-version",
        "-iplugindir",
        "-iprefix",
        "-iquote",
        "-isysroot",
        "-isystem",
        "-iwithprefix",
        "-iwithprefixbefore",
        "-l",
        "-mllvm",
        "-module-dependency-dir",
        "-o",
        "-seg1addr",
        "-serialize-diagnostics",
        "-specs",
        "-std",
        "-target",
        "-u",
        "-umbrella",
        "-unexported_symbols_list",
        "-unwindlib",
        "-wrapper",
        "-x",
        "-z",
    },
    {
        "-segaddr",
    },
    {
        "-segcreate",
        "-segprot",
    },
};
static const std::vector<std::vector<std::string>> kFlagPrefixesByNumArgs = {
    {},
    {
        "-Xarch",
        "-Xcuda",
        "-Xopenmp-target=",
        "-lazy",
        "-multiply_defined",
        "-seg_",
    },
    {},
    {
        "-sect",
    },
};

static inline void BearReport(const Context *context, const char *cc, const std::vector<char *> &arguments) {
    auto env = getenv("WIMAL_BEAR_PORT");
    if (!env) {
        return;
    }
    auto port = std::stoi(env);
    // Parse filename
    std::string filename;
    size_t skip = 1;
    for (auto arg : arguments) {
        if (!arg) {
            break;
        }
        if (skip) {
            --skip;
            continue;
        }
        if (arg[0] != '-') {
            filename.assign(arg);
        }
        std::string flag(arg);
        for (size_t i = 1; i < kFlagsByNumArgs.size(); ++i) {
            if (kFlagsByNumArgs[i].find(flag) != kFlagsByNumArgs[i].end()) {
                skip = i;
                break;
            }
        }
        for (size_t i = 1; !skip && i < kFlagPrefixesByNumArgs.size(); ++i) {
            for (auto &prefix : kFlagPrefixesByNumArgs[i]) {
                if (flag.size() <= prefix.size()) {
                    continue;
                }
                if (strncmp(flag.data(), prefix.data(), prefix.size()) == 0) {
                    skip = i;
                    break;
                }
            }
        }
    }
    if (filename.empty()) {
        return;
    }
    ghc::filesystem::path file(filename);
    if (!file.is_absolute()) {
        file = context->cwd / file;
    }
    Json::Value object;
    object["directory"] = context->cwd.string();
    object["file"] = file.lexically_normal().string();
    auto &iArguments = object["arguments"];
    iArguments.append(Json::Value(cc));
    for (size_t i = 1; i < arguments.size(); ++i) {
        if (arguments[i]) {
            iArguments.append(arguments[i]);
        }
    }
    auto data = object.toStyledString();
    auto fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (fd == -1) {
        return;
    }
    sockaddr_in address{};
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    address.sin_port = htons(port);
    sendto(fd, data.data(), data.size(), 0, (sockaddr *) &address, sizeof(address));
    close(fd);
}

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
        "-nostdinc++",
        "-cxx-isystem" + (context->clang / "include" / "c++" / "v1").string(),
        "--prefix", context->toolchain.string(),
        "-Qunused-arguments",
        "-stdlib=libc++"
    };
    // Define the api levels for android and darwin targets.
    switch (context->machine) {
        case Context::MACHINE_ARM_ANDROID:
        case Context::MACHINE_X86_ANDROID:
            args.emplace_back("-DANDROID");
            args.emplace_back("-D__ANDROID_API__=21");
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
    std::vector<char *> arguments;
    arguments.reserve(args.size() + context->args.size() + extraArgs.size() + 1);
    for (const auto &arg : args) {
        arguments.emplace_back(const_cast<char *>(arg.data()));
    }
    for (const auto &arg : context->args) {
        arguments.emplace_back(const_cast<char *>(arg.data()));
    }
    for (const auto &arg : extraArgs) {
        arguments.emplace_back(const_cast<char *>(arg.data()));
    }
    arguments.emplace_back(nullptr);
    BearReport(context, cc.string().data(), arguments);
    execvp(cc.c_str(), arguments.data());
}

}
