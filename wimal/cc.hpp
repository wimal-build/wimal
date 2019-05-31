#ifndef WIMAL_CC_HPP
#define WIMAL_CC_HPP

#include "action.hpp"

namespace wimal {

class Cc : public Action {
    void Run(const Context *context, std::vector<std::string> extraArgs) override;
};

}

#endif // WIMAL_CC_HPP
