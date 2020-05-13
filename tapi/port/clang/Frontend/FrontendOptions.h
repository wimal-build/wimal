#ifndef LLVM_CLANG_FRONTEND_FRONTENDOPTIONS_H
#define LLVM_CLANG_FRONTEND_FRONTENDOPTIONS_H

namespace clang {

class InputKind {
  public:
  enum Language : uint8_t {
    Unknown,
    Asm,
    LLVM_IR,
    C,
    CXX,
    ObjC,
    ObjCXX,
    OpenCL,
    CUDA,
    RenderScript,
    HIP,
  };
};

} // namespace clang

#endif // LLVM_CLANG_FRONTEND_FRONTENDOPTIONS_H
