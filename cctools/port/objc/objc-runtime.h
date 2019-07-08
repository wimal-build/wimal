#ifdef __APPLE__
#include_next <objc/objc-runtime.h>
#else // !__APPLE__
// https://opensource.apple.com/source/objc4/objc4-750.1/runtime/runtime.h
#define CLS_GETINFO(cls,infomask) ((cls)->info & (infomask))
#define CLS_CLASS 0x1
#define CLS_META 0x2
#endif // __APPLE__
