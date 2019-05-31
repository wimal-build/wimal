#include "install.hpp"

#include <boost/filesystem.hpp>
#include <iostream>

#include "context.hpp"

namespace wimal {

void Install::Run(const Context *context, std::vector<std::string> extraArgs) {
    for (auto &target : context->targets) {
        for (auto &action : actions) {
            auto dest = context->bin / (target + "-" + action.first);
            std::cout << "Creating " << dest.string() << std::endl;
            boost::system::error_code ec;
            boost::filesystem::create_symlink("wimal", dest, ec);
        }
    }
}

}
