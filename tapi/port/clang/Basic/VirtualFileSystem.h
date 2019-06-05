#ifndef TAPI_CLANG_BASIC_VIRTUALFILESYSTEM_H_
#define TAPI_CLANG_BASIC_VIRTUALFILESYSTEM_H_

#include "llvm/Support/VirtualFileSystem.h"

namespace clang {

#ifdef TAPI_CORE_FILEMANAGER_CPP
using namespace ::llvm;
#else
namespace vfs {
    using FileSystem = ::llvm::vfs::FileSystem;
    using recursive_directory_iterator = ::llvm::vfs::recursive_directory_iterator;
}
#endif // TAPI_FILEMANAGER_CPP

#ifdef TAPI_CORE_PATH_CPP
#define getName path
#endif // TAPI_CORE_PATH_CPP

}

#define clearStatCaches clearStatCache
#define addStatCache setStatCache

#endif // TAPI_CLANG_BASIC_VIRTUALFILESYSTEM_H_
