#include "invoke.hpp"

#include <unistd.h>

#include "context.hpp"

namespace wimal {

void Invoke::Run(const Context *context, std::vector<std::string> extraArgs) {
    std::vector<const char *> arguments;
    arguments.reserve(context->args.size() + extraArgs.size() + 2);
    auto command = context->toolchain / context->action;
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

}
