#ifndef EVENT_BUS_H
#define EVENT_BUS_H

#include "Core/Events/EventBus/QueuedEvent.h"

#include <functional>
#include <unordered_map>
#include <vector>

class EventBus
{
	public:
		template<typename TEvent>
		void subscribe(std::function<void(const TEvent&)> listener);

		template<typename TEvent>
		void emit(const TEvent& event);

		void dispatch();

	private:
		std::vector<QueuedEvent> eventQueue;

		std::unordered_map<
			std::type_index, 
			std::vector<std::function<void(const std::any&)>>
		> listeners;
};

#include "Core/Events/EventBus/EventBus.inl"
#endif // !EVENT_BUS_H

