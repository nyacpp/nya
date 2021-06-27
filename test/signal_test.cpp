#include <catch2/catch.hpp>
#include <thread>
#include <boost/signals2.hpp>
#include <nya/signal.hpp>
#include <nya/event_loop.hpp>
#include <nya.hpp>


using namespace std;
template<typename F>
using sig = boost::signals2::signal<F>;

int x1 = 0, x2 = 0, x3 = 0;
void bar(int y) { x1 = y; }        // slot 1
auto baz = [](int y) { x2 = y; };  // slot 2

TEST_CASE( "nya signal", "[nya]" )
{
	nya::event_loop eventLoop;
	thread th([&eventLoop] { eventLoop.start(); });

	sig<void(int)> foo; // signal with int argument
	sig<void()> foon;    // signal without arguments

	// invoke
	nya::invoke_in(eventLoop, bar, 3);      // invoke function
	int i = 3;
	nya::invoke_in(eventLoop, bar, i);
	nya::invoke_in(eventLoop, baz, 3);      // invoke lambda
	nya::invoke_in(eventLoop, [](int y)     // invoke lambda directly
	{
		x3 = y;
	}, 3);
	nya::invoke_in(eventLoop, []   // check uses invoke without arguments
	{
		CHECK(x1 == 3);
		CHECK(x2 == 3);
		CHECK(x3 == 3);;
	});

	// connect
	nya::connect_in(eventLoop, foo, bar);      // async connect to function
	nya::connect_in(eventLoop, foo, baz);      // async connect to lambda
	nya::connect_in(eventLoop, foo, [](int y)  // async connect to lambda directly
	{
		x3 = y;
	});
	nya::connect_in(eventLoop, foon, []
	{
		CHECK(x1 == 5);
		CHECK(x2 == 5);
		CHECK(x3 == 5);
	});

	foo(4); // call slots in "th" thread
	int j = 5;
	foo(j); // twice
	foon();

	eventLoop.stop();
	th.join();
}

struct TestEventLoopHolder : public nya::event_loop_holder<nya::event_loop>
{
	static inline int iFoo = 0, iBar = 0;
	static inline s_p<int> iZoo;

	static void Foo() { ++iFoo; }
	static void Bar(int y) { iBar = y; }
	static void Zoo(s_p<int> z) { iZoo = move(z); }

	static void Run() { eventLoop.run(); }
};

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
	CHECK(*TestEventLoopHolder::iZoo == 5);

	// connect
	sig<void()> SigFoo;
	sig<void(int)> SigBar;
	sig<void(s_p<int>)> SigZoo;
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
	CHECK(*TestEventLoopHolder::iZoo == 9);
}
