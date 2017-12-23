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
	// invoke
	nya::invoke_in(eventLoop, bar, 3);      // async connect to function
	int i = 3;
	nya::invoke_in(eventLoop, bar, i);
	nya::invoke_in(eventLoop, baz, 3);      // async connect to lambda
	nya::invoke_in(eventLoop, [](int y)     // async connect to lambda directly
	{
		x3 = y;
	}, 3);
	
	// connect
	nya::connect_in(eventLoop, foo, bar);      // async connect to function
	nya::connect_in(eventLoop, foo, baz);      // async connect to lambda
	nya::connect_in(eventLoop, foo, [](int y)  // async connect to lambda directly
	{
		x3 = y;
	});
	
	auto w = make_u<nya::event_loop::work>(eventLoop); // asio work
	thread th([&eventLoop] { eventLoop.run(); });
	
	foo(5); // call slots in "th" thread
	int j = 5;
	foo(j); // twice
	
	w.reset();
	th.join();
	
	CHECK(x1 == 5);
	CHECK(x2 == 5);
	CHECK(x3 == 5);
}

struct TestEventLoopHolder : public nya::event_loop_holder<TestEventLoopHolder>
{
	static int iFoo, iBar, iZoo;
	static void Foo() { ++iFoo; }
	static void Bar(int y) { iBar = y; }
	static void Zoo(s_p<int> z) { iZoo = *z; }

	static void Run() { eventLoop.run(); eventLoop.reset(); }
};
int TestEventLoopHolder::iFoo = 0;
int TestEventLoopHolder::iBar = 0;
int TestEventLoopHolder::iZoo = 0;

TEST_CASE( "nya event_loop_holder", "[nya]" )
{
	// invoke
	TestEventLoopHolder::invoke(TestEventLoopHolder::Foo);
	TestEventLoopHolder::invoke(TestEventLoopHolder::Bar, 5);
	int i = 5;
	TestEventLoopHolder::invoke(TestEventLoopHolder::Bar, i);
	TestEventLoopHolder::invoke(TestEventLoopHolder::Zoo, make_s<int>(5));
	TestEventLoopHolder::Run();

	CHECK(TestEventLoopHolder::iFoo == 1);
	CHECK(TestEventLoopHolder::iBar == 5);
	CHECK(TestEventLoopHolder::iZoo == 5);

	// connect
	nya::sig<void()> SigFoo;
	nya::sig<void(int)> SigBar;
	nya::sig<void(s_p<int>)> SigZoo;
	TestEventLoopHolder::connect(SigFoo, TestEventLoopHolder::Foo);
	TestEventLoopHolder::connect(SigBar, TestEventLoopHolder::Bar);
	TestEventLoopHolder::connect(SigZoo, TestEventLoopHolder::Zoo);

	SigFoo();
	SigBar(7);
	int j = 7;
	SigBar(j);
	SigZoo(make_s<int>(9));
	TestEventLoopHolder::Run();
	
	CHECK(TestEventLoopHolder::iFoo == 2);
	CHECK(TestEventLoopHolder::iBar == 7);
	CHECK(TestEventLoopHolder::iZoo == 9);
}
