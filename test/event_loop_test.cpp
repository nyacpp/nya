#include <catch2/catch.hpp>
#include <nya/event_loop.hpp>
#include <thread>

int a = 0;

void eq_f0()
{
	a = 1;
}

void eq_f1(int x)
{
	a = x;
}

void eq_f2(int x, int y)
{
	a = x + y;
}

TEST_CASE("event loop no thread", "[nya]")
{
	nya::event_loop eventLoop;
	eventLoop.post(&eq_f0);
	eventLoop.post(&eq_f1, 2);
	eventLoop.post(&eq_f2, 3, 0);
	eventLoop.post([]() { a = 4; });

	eventLoop.run();
	CHECK(a == 4);
}

TEST_CASE("event loop multithread", "[nya]")
{
	nya::event_loop eventLoop;
	std::thread th([&eventLoop]
				   {
					   eventLoop.post(&eq_f0);
					   eventLoop.post(&eq_f1, 2);
					   eventLoop.post(&eq_f2, 3, 0);
					   eventLoop.post([]() { a = 4; });

					   eventLoop.stop();
				   });

	eventLoop.start();
	CHECK(a == 4);
	th.join();
}