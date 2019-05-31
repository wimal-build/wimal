#ifndef WIMAL_AUTOBUILD_HPP
#define WIMAL_AUTOBUILD_HPP

#include "action.hpp"

namespace wimal {

class AutoBuild : public Action {
    void Run(const Context *context, std::vector<std::string> extraArgs) override;
};

}

#endif // WIMAL_AUTOBUILD_HPP
