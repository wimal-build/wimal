#include "autobuild.hpp"

#include <unistd.h>

#include "context.hpp"
#include "export.hpp"

namespace wimal {

void AutoBuild::Run(const Context *context, std::vector<std::string> extraArgs) {
    Export(context);

    std::vector<std::string> args = {
        "--host=" + context->host,
        "--enable-static",
        "--disable-shared",
        "--with-pic",
        "--prefix=" + (context->cwd / "targets").string(),
        "--with-sysroot=" + context->sysroot.string()
    };

    std::vector<const char *> arguments;
    arguments.reserve(args.size() + context->args.size() + extraArgs.size() + 2);
    arguments.emplace_back("bash");
    for (const auto &arg : context->args) {
        arguments.emplace_back(arg.data());
    }
    for (const auto &arg : extraArgs) {
        arguments.emplace_back(arg.data());
    }
    for (const auto &arg : args) {
        arguments.emplace_back(arg.data());
    }
    arguments.emplace_back(nullptr);
    execvp("bash", (char *const *) arguments.data());
}

}
