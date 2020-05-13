#ifndef TAPI_CLANG_AST_DECLOBJC_H_
#define TAPI_CLANG_AST_DECLOBJC_H_

#include_next "clang/AST/DeclObjC.h"

#include "tapi/Defines.h"

TAPI_NAMESPACE_INTERNAL_BEGIN

namespace clang {

using ObjCIvarDecl = ::clang::ObjCIvarDecl;
using ObjCPropertyDecl = ::clang::ObjCPropertyDecl;
using PresumedLoc = ::clang::PresumedLoc;

} // namespace clang

TAPI_NAMESPACE_INTERNAL_END

#endif // TAPI_CLANG_AST_DECLOBJC_H_
