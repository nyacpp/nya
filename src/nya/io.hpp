#ifndef IONYA_HPP
#define IONYA_HPP

#include <iostream>


/**
 * Only cin/cout, but faster.
 */
static void speedup_ios()
{
	std::ios::sync_with_stdio(false); // don't use <cstdio>
	std::cin.tie(0);                  // flush manually before cin
}

#include <string>
/**
 *  Use operator string() for class output.
 */
static std::ostream& operator <<(std::ostream& os, const std::string& s)
{
	return std::operator <<(os, s);
}

#ifndef NYA_DISABLE_VARIANT
#include <variant>
/**
 *  Print variant into ostream.
 */
template<typename T, typename... Args> // T - must be at least one argument
std::ostream& operator<< (std::ostream& os, const std::variant<T, Args...>& var)
{
	std::visit([&os](auto&& arg) { os << arg; }, var);
	return os;
}
#endif //NYA_DISABLE_VARIANT

#endif //IONYA_HPP