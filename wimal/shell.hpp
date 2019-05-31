#ifndef WIMAL_SHELL_HPP
#define WIMAL_SHELL_HPP

#include "action.hpp"

namespace wimal {

class Shell : public Action {
    void Run(const Context *context, std::vector<std::string> extraArgs) override;
};

}

#endif // WIMAL_SHELL_HPP
