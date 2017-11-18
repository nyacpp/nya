#ifndef FORMATNYA_HPP
#define FORMATNYA_HPP

/**
 * cout << "abc %s ghi"s % "def"; // abc def ghi
 */

#include <boost/format.hpp>
#include <string>

// implicit conversion std::string ⇒ boost::format
template<typename T>
boost::format operator %(const std::string& s, T arg) { return boost::format(s) % arg; }

// ""_f instead of ""s, though no templates:
//boost::format operator "" _f(const char* s, std::size_t) { return boost::format(s); }

#endif //FORMATNYA_HPP
