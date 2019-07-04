#ifndef LD64_CRASHREPORTERCLIENT_H_
#define LD64_CRASHREPORTERCLIENT_H_

#include <stdint.h>

#define CRASHREPORTER_ANNOTATIONS_VERSION 5
#define CRASHREPORTER_ANNOTATIONS_SECTION "__crash_info"

static inline void CRSetCrashLogMessage(const char *) {}

struct crashreporter_annotations_t {
    uint64_t version;
    uint64_t message;
    uint64_t signature_string;
    uint64_t backtrace;
    uint64_t message2;
    uint64_t thread;
    uint64_t dialog_mode;
    uint64_t abort_cause;
};

#endif // LD64_CRASHREPORTERCLIENT_H_
