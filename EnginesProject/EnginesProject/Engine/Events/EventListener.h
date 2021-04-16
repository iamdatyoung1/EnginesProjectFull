#ifndef EVENTLISTNER_H
#define EVENTLISTNER_H
#include "MouseEventListener.h"
class EventListener
{
public:
	EventListener(const EventListener&) = delete;
	EventListener(EventListener&&) = delete;

	EventListener() = delete;
	~EventListener();

	static void Update();
};
#endif