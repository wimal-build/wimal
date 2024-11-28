#ifndef WIMAL_BEAR_HPP
#define WIMAL_BEAR_HPP

#include "action.hpp"

namespace wimal {

class Bear : public Action {
  void Run(const Context *context, std::vector<std::string> extraArgs) override;
};

} // namespace wimal

#endif // WIMAL_BEAR_HPP
