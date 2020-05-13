#ifndef PORT_TAPI_CORE_REGISTRY_H_
#define PORT_TAPI_CORE_REGISTRY_H_

#include <memory>

#include_next "tapi/Core/Registry.h"

namespace {

template <class T, class... Args>
std::unique_ptr<T> make_unique(Args &&... args) {
  return std::make_unique<T>(args...);
}

} // namespace

#endif // PORT_TAPI_CORE_REGISTRY_H_
