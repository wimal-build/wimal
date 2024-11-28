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
  for (std::size_t i = 0; i < context->targets.size(); ++i) {
    auto &target = context->targets[i];
    auto toolchain = context->wimal / "toolchain";
    if (!ghc::filesystem::is_directory(toolchain)) {
      std::cout << "Creating " << toolchain << std::endl;
      ghc::filesystem::create_directory(toolchain, ec);
    }
    auto path = toolchain / target;
    if (!ghc::filesystem::is_directory(path)) {
      std::cout << "Creating " << path << std::endl;
      ghc::filesystem::create_directory(path, ec);
    }
    for (auto &toolchain : Context::toolchains) {
      auto src = ghc::filesystem::relative(context->bin / "wimal", path);
      auto dst = path / toolchain;
      std::cout << "Linking " << dst << " -> " << src << std::endl;
      ghc::filesystem::create_symlink(src, dst, ec);
    }
  }
}

} // namespace wimal
