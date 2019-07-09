#include "install.hpp"

#include <boost/filesystem.hpp>
#include <iostream>

#include "context.hpp"

namespace wimal {

void Install::Run(const Context *context, std::vector<std::string> extraArgs) {
    boost::system::error_code ec;
    for (auto &target : context->targets) {
        for (auto &action : actions) {
            auto dst = context->bin / (target + "-" + action.first);
            std::cout << "Creating " << dst << std::endl;
            boost::filesystem::create_symlink("wimal", dst, ec);
        }
    }
    struct link {
        const char *src;
        const char *dst;
    };
    static const std::vector<link> llvm = {
        {"llvm-ar", "-ar"},
        {"llvm-nm", "-nm"},
        {"llvm-objcopy", "-objcopy"},
        {"llvm-objdump", "-objdump"},
        {"llvm-ranlib", "-ranlib"},
        {"llvm-strip", "-strip"},
        {"llvm-readelf", "-readelf"},
        {"lld", "-ld"}
    };
    static const std::vector<link> cctools = {
        {"apple-ar", "-ar"},
        {"apple-nm", "-lipo"},
        {"apple-ranlib", "-ranlib"},
        {"apple-strip", "-strip"},
        {"apple-lipo", "-lipo"},
        {"apple-ld", "-ld"},
        {"apple-install_name_tool", "-install_name_tool"},
        {"dsymutil", "-dsymutil"}
    };
    for (std::size_t i = 0; i < context->targets.size(); ++i) {
        auto &target = context->targets[i];
        auto &triple = context->triples[i];
        auto toolchain = context->wimal / "toolchain";
        bool apple = target.find("-ios") != target.npos || target.find("-macos") != target.npos;
        if (!boost::filesystem::is_directory(toolchain)) {
            std::cout << "Creating " << toolchain << std::endl;
            boost::filesystem::create_directory(toolchain, ec);
        }
        auto path = toolchain / target;
        if (!boost::filesystem::is_directory(path)) {
            std::cout << "Creating " << path << std::endl;
            boost::filesystem::create_directory(path, ec);
        }
        auto &links = apple ? cctools : llvm;
        for (auto &link : links) {
            auto src = boost::filesystem::relative(context->bin / link.src, path);
            auto dst = path / (triple + link.dst);
            std::cout << "Linking " << dst << " -> " << src << std::endl;
            boost::filesystem::create_symlink(src, path / (triple + link.dst), ec);
        }
    }
}

}
