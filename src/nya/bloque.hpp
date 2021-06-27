#ifndef NYA_BLOQUE_HPP
#define NYA_BLOQUE_HPP

#include <mutex>
#include <condition_variable>
#include <deque>
#include <optional>

namespace nya
{
/**
 * Blocking Queue.
 */
template<typename T, template<typename> class Container = std::deque>
class bloque
{
	Container<T> container;
	bool is_valid = true;
	mutable std::mutex object_mutex;
	std::condition_variable when_empty;

public:
	/// True if no elements.
	bool empty() const
	{
		std::unique_lock lock(object_mutex);
		return container.empty();
	}

	/// Number of elements.
	std::size_t size() const
	{
		std::unique_lock lock(object_mutex);
		return container.size();
	}

	/// Push one value.
	void push(T value)
	{
		{
			std::unique_lock lock(object_mutex);
			container.push_back(std::move(value));
		}
		when_empty.notify_one();
	}

	/// Take one value, waiting if necessary.
	std::optional<T> take()
	{
		std::unique_lock lock(object_mutex);
		if (container.empty())
		{
			if (!is_valid)
			{
				return std::nullopt; // released before wait
			}
			when_empty.wait(lock);
			if (container.empty())
			{
				return std::nullopt; // released after wait
			}
		}
		T value = container.front();
		container.pop_front();
		return value;
	}

	/// Take all elements.
	Container<T> drain()
	{
		std::unique_lock lock(object_mutex);
		return std::move(container);
	}

	/// Remove all elements.
	void clear()
	{
		std::unique_lock lock(object_mutex);
		container.clear();
	}

	/// Release all taking and invalidate container.
	void release()
	{
		{
			std::unique_lock lock(object_mutex);
			is_valid = false;
		}
		when_empty.notify_all();
	}
};
}
#endif //NYA_BLOQUE_HPP
