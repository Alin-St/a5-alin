#pragma once

#include "EventService.h"
#include "DynamicVector.h"

class AdminConsole
{
private:
	EventService& eventService;

public:
	AdminConsole(EventService& eventService);

	void run();

	void uiAddEvent();
	void uiListAllEvents();
	void uiUpdateEvent();
	void uiDeleteEvent();

	void printEvent(const Event& event, size_t index);
	void printEvents(const DynamicVector<Event> events, const char* prompt);
};
