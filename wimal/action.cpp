#include "action.hpp"

#include <iostream>

#include "bear.hpp"
#include "cc.hpp"
#include "context.hpp"
#include "install.hpp"
#include "invoke.hpp"

namespace wimal {

const std::unordered_map<std::string, std::shared_ptr<Action>> Action::actions{
    {"cc", std::make_shared<Cc>()},
    {"c++", std::make_shared<Cc>()},
    {"cpp", std::make_shared<Cc>()},
    {"ar", std::make_shared<Invoke>()},
    {"ld", std::make_shared<Invoke>()},
    {"lipo", std::make_shared<Invoke>()},
    {"nm", std::make_shared<Invoke>()},
    {"objcopy", std::make_shared<Invoke>()},
    {"objdump", std::make_shared<Invoke>()},
    {"ranlib", std::make_shared<Invoke>()},
    {"strip", std::make_shared<Invoke>()},
    {"readelf", std::make_shared<Invoke>()},
    {"dsymutil", std::make_shared<Invoke>()},
    {"install_name_tool", std::make_shared<Invoke>()},
    {"bear", std::make_shared<Bear>()},
};

Action::Action() = default;

Action::~Action() = default;

void Action::Run(const char *action, const Context *context) {
  if (strcmp(action, "install") == 0) {
    Install install;
    ((Action &) install).Run(context, {});
    return;
  }
  auto it = actions.find(action);
  if (it != actions.end()) {
    it->second->Run(context, {});
  } else {
    Action help;
    help.Run(context, {});
  }
}

void Action::Run(const Context *context, std::vector<std::string> extraArgs) {
  extraArgs.clear();

  std::cout << "Targets:" << std::endl;
  for (auto &target : context->targets) {
    std::cout << "- " << target << std::endl;
  }
  std::cout << std::endl;
  std::cout << "Actions:" << std::endl;
  for (auto &action : actions) {
    std::cout << "- " << action.first << std::endl;
  }
}

} // namespace wimal
