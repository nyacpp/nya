#ifndef EXCEPTIONNYA_HPP
#define EXCEPTIONNYA_HPP

#include <exception>
#include <sstream>
#include <nya/format.hpp>


/**
 * Exception throwing with std::ostringstream. Stream allows using boost::format.
 *
 * \code{.cpp}
 *    // example
 *    throw_nya &lt;&lt; "File %s is not found"s % fileName;
 * \endcode
 */
#define throw_nya throw nya::exception() = std::ostringstream() << "exception:\n\t" << __FILE__ << ":" << __LINE__ << " >> "


namespace nya
{
using namespace std;

class exception : public std::exception
{
	string message;
public:
	// can be used only in throw_nya — no idea how to do it better
	nya::exception& operator =(ostream& other)
	{
		message = move(((ostringstream&) other).str());
		return *this;
	}
	
	operator string() const { return message; }
	const char* what() const noexcept override { return message.c_str(); }
};
}

#endif //EXCEPTIONNYA_HPP

