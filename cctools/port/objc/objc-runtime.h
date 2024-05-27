#ifdef __APPLE__
#include_next <objc/objc-runtime.h>
#endif // __APPLE__

// https://opensource.apple.com/source/objc4/objc4-750.1/runtime/runtime.h
#ifndef CLS_GETINFO
#define CLS_GETINFO(cls,infomask) ((cls)->info & (infomask))
#endif // CLS_GETINFO

#ifndef CLS_CLASS
#define CLS_CLASS 0x1
#endif // CLS_CLASS

#ifndef CLS_META
#define CLS_META 0x2
#endif // CLS_META
