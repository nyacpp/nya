#include <iostream>
#include <string>


/**
 * Only cin/cout, but faster.
 */
void speedup_ios()
{
	ios::sync_with_stdio(false); // don't use <cstdio>
	
	cin.tie(0);                  // flush manually before cin
}

/**
 *  Use operator string() for class output.
 */
std::ostream& operator<<(std::ostream& os, const std::string& s) 
{ 
	return std::operator<<(os, s); 
}