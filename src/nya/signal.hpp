#ifndef SIGNALNYA_HPP
#define SIGNALNYA_HPP

#include <boost/signals2.hpp>
#include <boost/asio/io_service.hpp>


namespace nya
{
template<typename ...Ts>
using sig = boost::signals2::signal<Ts...>;
using event_loop = boost::asio::io_service;

template<typename ...Args, typename Slot>
void connect_in(event_loop& eventLoop, sig<void(Args...)>& signalFunc, Slot&& slotFunc)
{
	signalFunc.connect([&eventLoop, slotFunc](Args... args)
	{
		eventLoop.post([slotFunc, args...] { slotFunc(args...); });
	});
}
}
#endif //SIGNALNYA_HPP
