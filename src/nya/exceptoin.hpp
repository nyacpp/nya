#ifndef _EXCEPTIONNYA_H
#define    _EXCEPTIONNYA_H

#include <exception>
#include <string>
#include <sstream>


namespace nya
{
using namespace std;

class exception : public std::exception
{
	const char* file;
	const int line;
	const string message;
	// stacktrace should be here

public:
	exception(const char* file, int line, string message)
			: file(file), line(line), message(std::move(message)) {}
	
	const char* what() const noexcept override
	{
		stringstream ss;
		ss << "exception:\n\t" << file << ":" << line << " >> " << message;
		return ss.str().c_str();
	}
};
}

#define throw_nya(message) throw nya::exception(__FILE__, __LINE__, message)

#endif    /* _EXCEPTIONNYA_H */

