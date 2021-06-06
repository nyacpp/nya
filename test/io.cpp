#include <catch2/catch.hpp>
#include <sstream>
#include <nya/io.hpp>

using namespace std;


struct A
{
	operator string() { return "abc"; }
};

TEST_CASE( "nya io", "[nya]" )
{
	stringstream ss;
	
	// implicit conversion to string for stream
	ss << A();
	CHECK(ss.str() == "abc");
	ss.str({});
	
	// print variant
	variant<int, string> v1 = 5, v2 = "xyz";
	ss << v1 << " " << v2;
	CHECK(ss.str() == "5 xyz");
}