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

#define nya_thread_name el::Helpers::setThreadName

namespace nya
{
template<typename ...>
inline void init_logs(const char* configPath)
{
	el::Loggers::configureFromGlobal(configPath);
	el::Configurations rawConf;
	rawConf.parseFromText("*GLOBAL:\n FORMAT = %msg", el::Loggers::getLogger("default")->configurations());
	el::Loggers::getLogger("raw")->configure(rawConf);
	
	nya_thread_name("_main_");
}
}

#endif //LOGNYA_HPP

