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


template<typename Slot, typename ...Args>
void invoke_in(event_loop& eventLoop, Slot&& slotFunc, Args... args)
{
	using namespace std;
	// move arguments to other thread
	eventLoop.post([slotFunc = forward<Slot>(slotFunc), argsT = make_tuple(move(args)...)]() mutable
	{
		// move arguments from lambda to slotFunc
		apply(move(slotFunc), move(argsT));
	});
}

template<template<typename, typename ...> class Signal, typename Slot, typename ...Args, typename ...Ts>
void connect_in(event_loop& eventLoop, Signal<void(Args...), Ts...>& signalFunc, Slot&& slotFunc)
{
	using namespace std;
	// arguments are copied, because there can be multiple slots
	signalFunc.connect([&eventLoop, slotFunc = forward<Slot>(slotFunc)](Args... args) mutable
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
	template<typename Slot, typename ...Args>
	static void invoke(Slot&& slotFunc, Args... args)
	{
		using namespace std;
		if constexpr (sizeof...(Args) != 0)
			invoke_in(eventLoop, forward<Slot>(slotFunc), move(args)...);
		else
			eventLoop.post(forward<Slot>(slotFunc));
	}

	template<template<typename, typename ...> class Signal, typename Slot, typename ...Args, typename ...Ts>
	static void connect(Signal<void(Args...), Ts...>& signalFunc, Slot&& slotFunc)
	{
		using namespace std;
		nya::connect_in(eventLoop, signalFunc, forward<Slot>(slotFunc));
	}
};
template<class T> nya::event_loop nya::event_loop_holder<T>::eventLoop;

}
#endif //SIGNALNYA_HPP
