#include "invoke.hpp"

#include <unistd.h>

#include "context.hpp"

namespace wimal {

static const std::unordered_map<std::string, std::string> commandLinks = {
    {"dsymutil", "dsymutil"},
    {"ld", "ld.lld"},
    {"ar", "llvm-ar"},
    {"install_name_tool", "llvm-install-name-tool"},
    {"lipo", "llvm-lipo"},
    {"nm", "llvm-nm"},
    {"objcopy", "llvm-objcopy"},
    {"objdump", "llvm-objdump"},
    {"ranlib", "llvm-ranlib"},
    {"readelf", "llvm-readelf"},
    {"strip", "llvm-strip"},
    {"otool", "llvm-otool"},
    {"arm-ios-ld", "ld64.lld"},
    {"a64-ios-ld", "ld64.lld"},
    {"x86-ios-ld", "ld64.lld"},
    {"x64-ios-ld", "ld64.lld"},
    {"a64-macos-ld", "ld64.lld"},
    {"x64-macos-ld", "ld64.lld"},
};

void Invoke::Run(const Context *context, std::vector<std::string> extraArgs) {
  std::vector<const char *> arguments;
  arguments.reserve(context->args.size() + extraArgs.size() + 2);
  auto it = commandLinks.find(context->target + "-" + context->action);
  if (it == commandLinks.end()) {
    it = commandLinks.find(context->action);
  }
  if (it == commandLinks.end()) {
    return;
  }
  auto command = context->bin / it->second;
  auto filename = command.filename().string();
  arguments.emplace_back(filename.data());
  for (const auto &arg : context->args) {
    arguments.emplace_back(arg.data());
  }
  for (const auto &arg : extraArgs) {
    arguments.emplace_back(arg.data());
  }
  arguments.emplace_back(nullptr);
  execvp(command.string().data(), const_cast<char *const *>(arguments.data()));
}

} // namespace wimal
