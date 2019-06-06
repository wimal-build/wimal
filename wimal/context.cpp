#include "context.hpp"

#include <iostream>

namespace wimal {

const std::vector<std::string> Context::targets = {
    "x64-linux",
    "x64-cygwin",
    "x64-macos",
    "arm-android",
    "a64-android",
    "x86-android",
    "x64-android",
    "arm-ios",
    "a64-ios",
    "x86-ios",
    "x64-ios",
};

const std::vector<std::string> Context::triples = {
    "x86_64-wimal-linux",
    "x86_64-wimal-cygwin",
    "x86_64-apple-darwin",
    "armv7-wimal-linux-androideabi",
    "aarch64-wimal-linux-android",
    "i686-wimal-linux-android",
    "x86_64-wimal-linux-android",
    "armv7-apple-darwin",
    "arm64-apple-darwin",
    "i386-apple-darwin",
    "x86_64-apple-darwin",
    "unsupported"
};

const std::vector<std::string> Context::hosts = {
    "x86_64-linux-gnu",
    "x86_64-pc-cygwin",
    "x86_64-apple-darwin",
    "armv7-none-linux-androideabi",
    "aarch64-none-linux-android",
    "i686-none-linux-android",
    "x86_64-none-linux-android",
    "armv7-apple-darwin",
    "arm64-apple-darwin",
    "i386-apple-darwin",
    "x86_64-apple-darwin",
    "unsupported"
};

Context::Context(int argc, char **argv) {
    for (int i = 1; i < argc; ++i) {
        args.emplace_back(argv[i]);
    }
    cwd = boost::filesystem::current_path();
    auto path = boost::filesystem::path(argv[0]);
    tool = path.filename().string();
    path = boost::filesystem::canonical(path);
    bin = path.parent_path();
    wimal = bin.parent_path();
    clang = wimal;
    if (tool == "wimal" && !args.empty()) {
        tool = args[0];
        args.erase(args.begin());
    }
    target = tool.substr(0, tool.find_last_of('-'));
    action = tool.substr(tool.find_last_of('-') + 1);
    sysroot = wimal / "sysroot" / target;
    toolchain = wimal / "toolchain" / target;
    auto it = std::find(targets.begin(), targets.end(), target.data());
    machine = it == targets.end() ? MACHINE_UNSUPPORTED : (Machine) (it - targets.begin());

    triple = triples[machine];
    host = hosts[machine];
}

Context::~Context() = default;
}
