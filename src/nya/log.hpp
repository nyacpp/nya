#ifndef LOGNYA_HPP
#define LOGNYA_HPP

/**
 * easylogging - well documented logging library with a good variety of pretty prints.
 *
 * // Example
 * error_log << "Number %d shouldn't be here"s % 5;
 *
 */
#ifndef ELPP_STL_LOGGING
#define ELPP_STL_LOGGING
#endif
#ifndef ELPP_LOG_STD_ARRAY
#define ELPP_LOG_STD_ARRAY
#endif
#ifndef ELPP_LOG_UNORDERED_MAP
#define ELPP_LOG_UNORDERED_MAP
#endif
#ifndef ELPP_LOG_UNORDERED_SET
#define ELPP_LOG_UNORDERED_SET
#endif

#include <easylogging++.h>
#include <nya/format.hpp>

#define trace_log    LOG(TRACE)
#define info_log     LOG(INFO)
#define error_log    LOG(ERROR)
#define fatal_log    LOG(FATAL)
#define trace_raw    CLOG(TRACE, "raw")
#define info_raw     CLOG(INFO,  "raw")
#define error_raw    CLOG(ERROR, "raw")
#define fatal_raw    CLOG(FATAL, "raw")

namespace nya
{
static constexpr std::string (&GetThreadName)() = el::Helpers::getThreadName;
static constexpr void (&SetThreadName)(const std::string&) = el::Helpers::setThreadName;
}

#endif //LOGNYA_HPP

