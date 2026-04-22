#include "Core/Events/EventBus/EventBus.h"

template<typename TEvent>
void EventBus::subscribe(std::function<void(const TEvent&)> listener)
{
	auto key = std::type_index(typeid(TEvent));
	listeners[key].push_back(
		[listener](const std::any& event)
		{
			listener(std::any_cast<const TEvent&>(event));
		}
	);
}

template<typename TEvent>
void EventBus::emit(const TEvent& event)
{
	auto key = std::type_index(typeid(TEvent));
	eventQueue.push_back({ key, event });
}