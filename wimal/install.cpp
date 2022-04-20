#include "install.hpp"

#include <iostream>

#include "context.hpp"

namespace wimal {

void Install::Run(const Context *context, std::vector<std::string> extraArgs) {
    std::error_code ec;
    for (auto &target : context->targets) {
        for (auto &action : actions) {
            auto dst = context->bin / (target + "-" + action.first);
            std::cout << "Creating " << dst << std::endl;
            ghc::filesystem::create_symlink("wimal", dst, ec);
        }
    }
    struct link {
        const char *src;
        const char *dst;
    };
    static const std::vector<link> llvm = {
        {"dsymutil", "dsymutil"},
        {"lld", "ld"},
        {"llvm-ar", "ar"},
        {"llvm-install-name-tool", "install_name_tool"},
        {"llvm-lipo", "lipo"},
        {"llvm-nm", "nm"},
        {"llvm-objcopy", "objcopy"},
        {"llvm-objdump", "objdump"},
        {"llvm-ranlib", "ranlib"},
        {"llvm-readelf", "readelf"},
        {"llvm-strip", "strip"},
    };
    static const std::vector<link> cctools = {
        {"apple-ar", "ar"},
        {"apple-install-name-tool", "install_name_tool"},
        {"apple-ld", "ld"},
        {"apple-lipo", "lipo"},
        {"apple-nm", "nm"},
        {"apple-ranlib", "ranlib"},
        {"apple-readelf", "readelf"},
        {"apple-strip", "strip"},
        {"dsymutil", "dsymutil"},
        {"llvm-objcopy", "objcopy"},
        {"llvm-objdump", "objdump"},
    };
    for (std::size_t i = 0; i < context->targets.size(); ++i) {
        auto &target = context->targets[i];
        auto &triple = context->triples[i];
        auto toolchain = context->wimal / "toolchain";
        bool apple = target.find("-ios") != target.npos || target.find("-macos") != target.npos;
        if (!ghc::filesystem::is_directory(toolchain)) {
            std::cout << "Creating " << toolchain << std::endl;
            ghc::filesystem::create_directory(toolchain, ec);
        }
        auto path = toolchain / target;
        if (!ghc::filesystem::is_directory(path)) {
            std::cout << "Creating " << path << std::endl;
            ghc::filesystem::create_directory(path, ec);
        }
        auto &links = apple ? cctools : llvm;
        for (auto &link : links) {
            auto src = ghc::filesystem::relative(context->bin / link.src, path);
            auto dst = path / link.dst;
            std::cout << "Linking " << dst << " -> " << src << std::endl;
            ghc::filesystem::create_symlink(src, dst, ec);
        }
    }
}

}
