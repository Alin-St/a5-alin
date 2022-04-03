#pragma once

#include "services.h"
#include "domain.h"

class Console
{
private:
	EventService& eventService;

public:
	Console(EventService& eventService);

	void run();

	void uiAdministratorMode();
};
