#ifndef EXCEPTIONNYA_HPP
#define EXCEPTIONNYA_HPP

#include <cstring>
#include <exception>
#include <sstream>
#include <nya/format.hpp>

#ifdef _WIN32
	#define __DELIM_CHAR__ '\\'
#else
	#define __DELIM_CHAR__ '/'
#endif
#define __FILENAME__ (strrchr(__FILE__, __DELIM_CHAR__) ? strrchr(__FILE__, __DELIM_CHAR__) + 1 : __FILE__)

/**
 * Exception throwing with std::ostringstream. Stream allows using boost::format.
 *
 * \code{.cpp}
 *    // example
 *    nya_throw &lt;&lt; "File %s is not found"s % fileName;
 * \endcode
 */
#define nya_throw throw nya::exception() = std::ostringstream() << __FILENAME__ << ":" << __LINE__ << " -- "


namespace nya
{
class exception : public std::exception
{
	std::string message;
public:
	// can be used only in nya_throw — no idea how to do it better
	nya::exception& operator =(std::ostream& other)
	{
		message = std::move(((std::ostringstream&) other).str());
		return *this;
	}
	
	operator std::string() const { return message; }
	const char* what() const noexcept override { return message.c_str(); }
};
}

#endif //EXCEPTIONNYA_HPP

