#ifndef WIMAL_CONTEXT_HPP
#define WIMAL_CONTEXT_HPP

#include <string>
#include <vector>

#include "filesystem.hpp"

namespace wimal {

class Context {
public:
    enum Machine {
        MACHINE_X64_LINUX,
        MACHINE_A64_LINUX,
        MACHINE_X64_CYGWIN,
        MACHINE_X64_MACOS,
        MACHINE_A64_MACOS,
        MACHINE_ARM_ANDROID,
        MACHINE_A64_ANDROID,
        MACHINE_X86_ANDROID,
        MACHINE_X64_ANDROID,
        MACHINE_ARM_IOS,
        MACHINE_A64_IOS,
        MACHINE_X86_IOS,
        MACHINE_X64_IOS,
        MACHINE_UNSUPPORTED
    };

public:
    static const std::vector<std::string> targets;
    static const std::vector<std::string> triples;
    static const std::vector<std::string> hosts;

public:
    Context(int argc, char **argv);
    ~Context();

public:
    ghc::filesystem::path cwd;
    ghc::filesystem::path bin;
    ghc::filesystem::path wimal;
    ghc::filesystem::path clang;
    ghc::filesystem::path toolchain;
    ghc::filesystem::path sysroot;
    Machine machine;
    std::string tool;
    std::string target;
    std::string action;
    std::string triple;
    std::string host;
    std::vector<std::string> args;
};

}

#endif // WIMAL_CONTEXT_HPP
