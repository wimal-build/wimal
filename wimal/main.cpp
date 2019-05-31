#include "main.hpp"

#include "action.hpp"
#include "context.hpp"

int main(int argc, char **argv) {
    wimal::Context context(argc, argv);
    wimal::Action::Run(context.action.data(), &context);
    return 0;
}
