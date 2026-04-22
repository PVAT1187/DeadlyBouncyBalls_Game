#ifndef QUEUED_EVENT_H
#define QUEUED_EVENT_H

#include <typeindex>
#include <any>

struct QueuedEvent
{
	std::type_index event;
	std::any data;
};

#endif // !QUEUED_EVENT_H

