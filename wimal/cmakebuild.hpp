#ifndef WIMAL_CMAKEBUILD_HPP
#define WIMAL_CMAKEBUILD_HPP

#include "action.hpp"

namespace wimal {

class CmakeBuild : public Action {
    void Run(const Context *context, std::vector<std::string> extraArgs) override;
};

}

#endif // WIMAL_CMAKEBUILD_HPP
