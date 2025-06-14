#define FMT_HEADER_ONLY
#include "libs/include/lemlib/fmt/format.h"
#include "libs/include/lemlib/logger/telemetrySink.hpp"
#include "libs/include/lemlib/logger/stdout.hpp"

namespace lemlib {
TelemetrySink::TelemetrySink() { setFormat("TELE_{level}:{message}TELE_END"); }

void TelemetrySink::sendMessage(const Message& message) {
    bufferedStdout().print("\033[s{}\033[u\033[0J", message.message);
}
} // namespace lemlib
