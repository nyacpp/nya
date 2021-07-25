#include <catch2/catch.hpp>
#include <nya/bloque.hpp>
#include <thread>

TEST_CASE("blocking queue no thread", "[nya]")
{
	nya::bloque<int> q;
	q.push(1);
	q.push(2);
	q.push(3);

	for (int i = 1; i < 4; ++i) { CHECK(q.take() == i); }
}

TEST_CASE("blocking queue multithread", "[nya]")
{
	nya::bloque<int> q;
	std::thread th([&q] {
		q.push(1);
		q.push(2);
		q.push(3);
	});

	for (int i = 1; i < 4; ++i) { CHECK(q.take() == i); }
	th.join();
}