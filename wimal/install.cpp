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
        {"lld", "-ld"},
        {"dsymutil", "-dsymutil"},
        {"llvm-lipo", "-lipo"},
        {"llvm-install-name-tool", "-install_name_tool"}
    };
    for (std::size_t i = 0; i < context->targets.size(); ++i) {
        auto &target = context->targets[i];
        auto &triple = context->triples[i];
        auto toolchain = context->wimal / "toolchain";
        if (!boost::filesystem::is_directory(toolchain)) {
            std::cout << "Creating " << toolchain << std::endl;
            boost::filesystem::create_directory(toolchain, ec);
        }
        auto path = toolchain / target;
        if (!boost::filesystem::is_directory(path)) {
            std::cout << "Creating " << path << std::endl;
            boost::filesystem::create_directory(path, ec);
        }
        for (auto &link : llvm) {
            auto src = boost::filesystem::relative(context->bin / link.src, path);
            auto dst = path / (triple + link.dst);
            std::cout << "Linking " << dst << " -> " << src << std::endl;
            boost::filesystem::create_symlink(src, path / (triple + link.dst), ec);
        }
    }
}

}
