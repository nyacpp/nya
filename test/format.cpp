#include <catch2/catch.hpp>
#include <nya/format.hpp>

TEST_CASE("nya format", "[nya]")
{
	using namespace std::string_literals;

	auto s = str("abc %s ghi"s % "def");
	CHECK(s == "abc def ghi");

	s = str("abc %d ghi"s % 111);
	CHECK(s == "abc 111 ghi");
}