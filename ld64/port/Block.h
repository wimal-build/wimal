#ifdef __APPLE__
#include_next <Block.h>
#else // !__APPLE__
#include <objc/blocks_runtime.h>
#endif // __APPLE__