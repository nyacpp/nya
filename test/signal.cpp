#include <catch.hpp>
#include <thread>
#include <nya/signal.hpp>
#include <nya.hpp>

using namespace std;


int x1 = 0, x2 = 0, x3 = 0;
nya::sig<void(int)> foo;           // signal
void bar(int y) { x1 = y; }        // slot 1
auto baz = [](int y) { x2 = y; };  // slot 2

TEST_CASE( "nya signal", "[nya]" )
{
	nya::event_loop eventLoop;
	nya::connect_in(eventLoop, foo, bar);      // async connect to function
	nya::connect_in(eventLoop, foo, baz);      // async connect to lambda
	nya::connect_in(eventLoop, foo, [](int y)  // async connect to lambda directly
	{
		x3 = y;
	});
	
	auto w = make_u<nya::event_loop::work>(eventLoop); // asio work
	thread th([&eventLoop] { eventLoop.run(); });
	
	foo(5); // call slots in "th" thread
	
	w.reset();
	th.join();
	
	CHECK(x1 == 5);
	CHECK(x2 == 5);
	CHECK(x3 == 5);
}