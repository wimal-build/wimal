#ifndef WIMAL_CONTEXT_HPP
#define WIMAL_CONTEXT_HPP

#include <boost/filesystem.hpp>
#include <string>
#include <vector>

namespace wimal {

class Context {
public:
    enum Machine {
        MACHINE_X64_LINUX,
        MACHINE_X64_CYGWIN,
        MACHINE_X64_MACOS,
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

public:
    Context(int argc, char **argv);
    ~Context();

public:
    boost::filesystem::path cwd;
    boost::filesystem::path bin;
    boost::filesystem::path wimal;
    boost::filesystem::path clang;
    boost::filesystem::path toolchain;
    boost::filesystem::path ndk;
    boost::filesystem::path sysroot;
    boost::filesystem::path gcc;
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
