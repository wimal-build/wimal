#ifndef CCTOOLS_INSTALL_HPP
#define CCTOOLS_INSTALL_HPP

#include "action.hpp"

namespace wimal {

class Install : public Action {
  void Run(const Context *context, std::vector<std::string> extraArgs) override;
};

} // namespace wimal

#endif //CCTOOLS_INSTALL_HPP
