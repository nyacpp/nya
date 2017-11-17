#ifndef _LOGNYA_H
#define    _LOGNYA_H

/**
 * easylogging - well documented logging library with a good variety of pretty prints.
 * boost::format - printf-like formatting.
 *
 * // Example
 * error_log << "Number %d shouldn't be here"s % 5;
 *
 */
#include <easylogging++.h>
#define trace_log    LOG(TRACE)
#define info_log     LOG(INFO)
#define error_log    LOG(ERROR)
#define fatal_log    LOG(FATAL)
#define trace_raw    CLOG(TRACE, "raw")
#define info_raw     CLOG(INFO,  "raw")
#define error_raw    CLOG(ERROR, "raw")
#define fatal_raw    CLOG(FATAL, "raw")


// implicit conversion std::string ⇒ boost::format
#include <boost/format.hpp>
template<typename T>
boost::format operator % (const std::string& s, T arg) { return boost::format(s) % arg; }

// ""_f instead of ""s, though no templates:
//boost::format operator "" _f(const char* s, std::size_t) { return boost::format(s); }

#endif    /* _LOGNYA_H */

