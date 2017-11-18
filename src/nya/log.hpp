#ifndef LOGNYA_HPP
#define LOGNYA_HPP

/**
 * easylogging - well documented logging library with a good variety of pretty prints.
 *
 * // Example
 * error_log << "Number %d shouldn't be here"s % 5;
 *
 */
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

#endif //LOGNYA_HPP

