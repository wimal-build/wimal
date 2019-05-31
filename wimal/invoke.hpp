#ifndef WIMAL_INVOKE_HPP
#define WIMAL_INVOKE_HPP

#include "action.hpp"

namespace wimal {

class Invoke : public Action {
    void Run(const Context *context, std::vector<std::string> extraArgs) override;
};

}

#endif // WIMAL_INVOKE_HPP
