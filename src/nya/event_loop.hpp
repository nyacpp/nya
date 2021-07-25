#ifndef NYA_EVENT_QUEUE_TEST_HPP
#define NYA_EVENT_QUEUE_TEST_HPP

#include <atomic>
#include <functional>

#include "bloque.hpp"

namespace nya
{
/**
 * Event Loop.
 */
class event_loop
{
	using Functor = std::function<void(void)>;

public:
	/// Post one event for execution.
	template<typename Event, typename... Args> void post(Event&& event, Args... args)
	{
		using namespace std;
		if constexpr (sizeof...(Args) == 0)
			queue.push(event);
		else
			queue.push([e = forward<Event>(event), argsT = make_tuple(move(args)...)]() mutable {
				// move arguments from lambda to slotFunc
				apply(move(e), move(argsT));
			});
	}

	/// Block tread and start the event loop.
	void start()
	{
		while (auto functor = queue.take()) { functor.value()(); }
	}

	/// Stop the blocking event loop.
	void stop() { queue.release(); }

	/// Immediately stop the blocking event loop.
	void abort()
	{
		queue.clear();
		queue.release();
	}

	/// Run all events in the loop without blocking.
	void run()
	{
		for (const auto& functor : queue.drain()) { functor(); }
	}

private:
	bloque<Functor> queue;
};
}  // namespace nya

#endif  // NYA_EVENT_QUEUE_TEST_HPP
