#pragma once

#include <memory>
#include <array>

#define FMT_HEADER_ONLY
#include "libs/include/lemlib/fmt/core.h"

#include "libs/include/lemlib/logger/baseSink.hpp"
#include "libs/include/lemlib/logger/infoSink.hpp"
#include "libs/include/lemlib/logger/telemetrySink.hpp"

namespace lemlib {

/**
 * @brief Get the info sink.
 * @return std::shared_ptr<InfoSink>
 */
std::shared_ptr<InfoSink> infoSink();

/**
 * @brief Get the telemetry sink.
 * @return std::shared_ptr<TelemetrySink>
 */
std::shared_ptr<TelemetrySink> telemetrySink();
} // namespace lemlib
