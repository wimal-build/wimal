#ifdef __APPLE__
#include_next <Block.h>
#else // !__APPLE__
// Use blocks runtime from compiler-rt.
// http://releases.llvm.org/8.0.0/compiler-rt-8.0.0.src.tar.xz
#include "BlocksRuntime/Block.h"
#endif // __APPLE__