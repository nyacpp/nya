#ifndef IONYA_HPP
#define IONYA_HPP

#include <iostream>
#include <string>


/**
 * Only cin/cout, but faster.
 */
static void speedup_ios()
{
	std::ios::sync_with_stdio(false); // don't use <cstdio>
	std::cin.tie(0);                  // flush manually before cin
}

/**
 *  Use operator string() for class output.
 */
static std::ostream& operator <<(std::ostream& os, const std::string& s)
{
	return std::operator <<(os, s);
}

#endif //IONYA_HPP