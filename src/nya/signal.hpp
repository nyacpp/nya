#ifndef SIGNALNYA_HPP
#define SIGNALNYA_HPP

#include <tuple>
#include <utility>
#include <boost/signals2.hpp>
#include <boost/asio/io_service.hpp>


namespace nya
{
template<typename ...Ts>
using sig = boost::signals2::signal<Ts...>;
using event_loop = boost::asio::io_service;


template<typename ...Args>
void invoke_in(event_loop& eventLoop, typename sig<void(Args...)>::slot_type&& slotFunc, Args... args)
{
	using namespace std;
	// move arguments to other thread
	eventLoop.post([slotFunc = move(slotFunc), argsT = make_tuple(move(args)...)]() mutable
	{
		// move arguments from lambda to slotFunc
		apply(move(slotFunc), move(argsT));
	});
}

template<typename ...Args>
void connect_in(event_loop& eventLoop, sig<void(Args...)>& signalFunc, typename sig<void(Args...)>::slot_type&& slotFunc)
{
	using namespace std;
	// arguments are copied, because there can be multiple slots
	signalFunc.connect([&eventLoop, slotFunc = move(slotFunc)](Args... args) mutable
	{
		// slot is copied, because it can be called multiple times
		auto slotCopy = slotFunc;
		invoke_in(eventLoop, move(slotCopy), move(args)...);
	});
}

template<class T>
class event_loop_holder
{
protected:
	static nya::event_loop eventLoop;

public:
	template<typename ...Args>
	static void invoke(typename sig<void(Args...)>::slot_type&& slotFunc, Args... args)
	{
		using namespace std;
		if constexpr (sizeof...(Args))
			invoke_in(eventLoop, move(slotFunc), move(args)...);
		else
			eventLoop.post(move(slotFunc));
	}
	
	template<typename ...Args>
	static void connect(nya::sig<void(Args...)>& signalFunc, typename sig<void(Args...)>::slot_type&& slotFunc)
	{
		nya::connect_in(eventLoop, signalFunc, std::move(slotFunc));
	}
};
template<class T> nya::event_loop nya::event_loop_holder<T>::eventLoop;

}
#endif //SIGNALNYA_HPP
