#ifndef SIGNALNYA_HPP
#define SIGNALNYA_HPP

#include <boost/signals2.hpp>
#include <boost/asio/io_service.hpp>


namespace nya
{
template<typename ...Ts>
using sig = boost::signals2::signal<Ts...>;
using event_loop = boost::asio::io_service;

template<typename ...Args>
void connect_in(event_loop& eventLoop, sig<void(Args...)>& signalFunc, typename sig<void(Args...)>::slot_type slotFunc)
{
	signalFunc.connect([&eventLoop, slotFunc](Args... args)
	{
		eventLoop.post([slotFunc, args...] { slotFunc(args...); });
	});
}

template<class T>
class event_loop_holder
{
protected:
	static nya::event_loop eventLoop;

public:
	template<typename ...Args, typename Slot>
	static void Connect(nya::sig<void(Args...)>& signalFunc, Slot&& slotFunc)
	{
		nya::connect_in(eventLoop, signalFunc, slotFunc);
	}
};
template<class T> nya::event_loop nya::event_loop_holder<T>::eventLoop;

}
#endif //SIGNALNYA_HPP
