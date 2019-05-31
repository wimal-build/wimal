#ifndef WIMAL_ACTION_HPP
#define WIMAL_ACTION_HPP

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace wimal {

class Context;

class Action {
public:
    Action();
    virtual ~Action();

public:
    static void Run(const char *action, const Context *context);

protected:
    virtual void Run(const Context *context, std::vector<std::string> extraArgs);

protected:
    static const std::unordered_map<std::string, std::shared_ptr<Action>> actions;
};

}

#endif // WIMAL_ACTION_HPP
