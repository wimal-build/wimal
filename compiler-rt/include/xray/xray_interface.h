//===- xray_interface.h -----------------------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file is a part of XRay, a dynamic runtime instrumentation system.
//
// APIs for controlling XRay functionality explicitly.
//===----------------------------------------------------------------------===//

#ifndef XRAY_XRAY_INTERFACE_H
#define XRAY_XRAY_INTERFACE_H

#include <cstddef>
#include <cstdint>

extern "C" {

/// Synchronize this with AsmPrinter::SledKind in LLVM.
enum XRayEntryType {
  ENTRY = 0,
  EXIT = 1,
  TAIL = 2,
  LOG_ARGS_ENTRY = 3,
  CUSTOM_EVENT = 4,
  TYPED_EVENT = 5,
};

/// Provide a function to invoke for when instrumentation points are hit. This
/// is a user-visible control surface that overrides the default implementation.
/// The function provided should take the following arguments:
///
///   - function id: an identifier that indicates the id of a function; this id
///                  is generated by xray; the mapping between the function id
///                  and the actual function pointer is available through
///                  __xray_table.
///   - entry type: identifies what kind of instrumentation point was
///                 encountered (function entry, function exit, etc.). See the
///                 enum XRayEntryType for more details.
///
/// The user handler must handle correctly spurious calls after this handler is
/// removed or replaced with another handler, because it would be too costly for
/// XRay runtime to avoid spurious calls.
/// To prevent circular calling, the handler function itself and all its
/// direct&indirect callees must not be instrumented with XRay, which can be
/// achieved by marking them all with: __attribute__((xray_never_instrument))
///
/// Returns 1 on success, 0 on error.
extern int __xray_set_handler(void (*entry)(int32_t, XRayEntryType));

/// This removes whatever the currently provided handler is. Returns 1 on
/// success, 0 on error.
extern int __xray_remove_handler();

/// Use XRay to log the first argument of each (instrumented) function call.
/// When this function exits, all threads will have observed the effect and
/// start logging their subsequent affected function calls (if patched).
///
/// Returns 1 on success, 0 on error.
extern int __xray_set_handler_arg1(void (*entry)(int32_t, XRayEntryType,
                                                 uint64_t));

/// Disables the XRay handler used to log first arguments of function calls.
/// Returns 1 on success, 0 on error.
extern int __xray_remove_handler_arg1();

/// Provide a function to invoke when XRay encounters a custom event.
extern int __xray_set_customevent_handler(void (*entry)(void *, std::size_t));

/// This removes whatever the currently provided custom event handler is.
/// Returns 1 on success, 0 on error.
extern int __xray_remove_customevent_handler();

/// Set a handler for xray typed event logging. The first parameter is a type
/// identifier, the second is a payload, and the third is the payload size.
/// NOTE: fdrLoggingHandleTypedEvent only supports uint16_t event type.
extern int __xray_set_typedevent_handler(void (*entry)(size_t, const void *,
                                                       size_t));

/// Removes the currently set typed event handler.
/// Returns 1 on success, 0 on error.
extern int __xray_remove_typedevent_handler();

extern uint16_t __xray_register_event_type(const char *event_type);

enum XRayPatchingStatus {
  NOT_INITIALIZED = 0,
  SUCCESS = 1,
  ONGOING = 2,
  FAILED = 3,
};

/// This tells XRay to patch the instrumentation points. See XRayPatchingStatus
/// for possible result values.
extern XRayPatchingStatus __xray_patch();

/// Reverses the effect of __xray_patch(). See XRayPatchingStatus for possible
/// result values.
extern XRayPatchingStatus __xray_unpatch();

/// This patches a specific function id. See XRayPatchingStatus for possible
/// result values.
extern XRayPatchingStatus __xray_patch_function(int32_t FuncId);

/// This unpatches a specific function id. See XRayPatchingStatus for possible
/// result values.
extern XRayPatchingStatus __xray_unpatch_function(int32_t FuncId);

/// This function returns the address of the function provided a valid function
/// id. We return 0 if we encounter any error, even if 0 may be a valid function
/// address.
extern uintptr_t __xray_function_address(int32_t FuncId);

/// This function returns the maximum valid function id. Returns 0 if we
/// encounter errors (when there are no instrumented functions, etc.).
extern size_t __xray_max_function_id();

/// Initialize the required XRay data structures. This is useful in cases where
/// users want to control precisely when the XRay instrumentation data
/// structures are initialized, for example when the XRay library is built with
/// the XRAY_NO_PREINIT preprocessor definition.
///
/// Calling __xray_init() more than once is safe across multiple threads.
extern void __xray_init();

} // end extern "C"

#endif // XRAY_XRAY_INTERFACE_H
