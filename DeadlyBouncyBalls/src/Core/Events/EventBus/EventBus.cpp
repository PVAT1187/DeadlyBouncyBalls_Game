#include "Core/Events/EventBus/EventBus.h"

void EventBus::dispatch()
{
	auto pending = std::move(eventQueue);
	eventQueue.clear();

	for (const auto& [key, event] : pending)
	{
		auto iter = listeners.find(key);
		if (iter != listeners.end())
		{
			for (const auto& listener : iter->second)
			{
				listener(event);
			}
		}
	}
}
