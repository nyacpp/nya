#include <catch2/catch.hpp>
#include <nya/exception.hpp>


void foo()
{
	using namespace std::string_literals;

	nya_throw << "just %d"s % 1 << " error";  // "just 1 error"
}


TEST_CASE("nya exception", "[nya]")
{
	using namespace Catch::Matchers;

	CHECK_THROWS_AS(foo(), nya::exception);
	CHECK_THROWS_WITH(foo(), EndsWith("1 error"));
}