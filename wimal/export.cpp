#include "export.hpp"

#include <cstdlib>
#include <cstring>

#include "context.hpp"

namespace wimal {

void Export(const Context *context) {
  std::vector<std::pair<std::string, std::string>> environments = {
      {
          "CC",
          (context->bin / (context->target + "-cc")).string(),
      },
      {
          "CXX",
          (context->bin / (context->target + "-c++")).string(),
      },
      {
          "CPP",
          (context->bin / (context->target + "-cpp")).string(),
      },
      {
          "AR",
          (context->bin / (context->target + "-ar")).string(),
      },
      {
          "LD",
          (context->bin / (context->target + "-ld")).string(),
      },
      {
          "NM",
          (context->bin / (context->target + "-nm")).string(),
      },
      {
          "RANLIB",
          (context->bin / (context->target + "-ranlib")).string(),
      },
      {
          "STRIP",
          (context->bin / (context->target + "-strip")).string(),
      },
      {
          "OBJCOPY",
          (context->bin / (context->target + "-objcopy")).string(),
      },
      {
          "INSTALL_NAME_TOOL",
          (context->toolchain / "install_name_tool").string(),
      },
      {
          "SYSROOT",
          context->sysroot.string(),
      },
      {
          "TARGET",
          context->target,
      },
      {
          "HOST",
          context->host,
      },
      {
          "PKG_CONFIG_SYSROOT_DIR",
          context->sysroot.string(),
      },
      {
          "PKG_CONFIG_DIR",
          "",
      },
      {
          "PKG_CONFIG_LIBDIR",
          ((context->sysroot / "usr" / "lib" / "pkgconfig").string() + ":" +
           (context->sysroot / "usr" / "share" / "pkgconfig").string() + ":" +
           (context->sysroot / "usr" / "lib" / context->host / "pkgconfig")
               .string()),
      },
  };
  for (auto &kv : environments) {
    auto off = getenv((std::string("NO") + kv.first).data());
    if (!off || strlen(off) == 0) {
#ifdef _WIN32
      _putenv_s(kv.first.data(), kv.second.data());
#else
      setenv(kv.first.data(), kv.second.data(), 1);
#endif
    }
  }
}

} // namespace wimal
