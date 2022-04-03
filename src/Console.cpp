#include "Console.h"
#include "AdminConsole.h"
#include <iostream>

Console::Console(EventService& eventServ) : eventService(eventServ) {}

void Console::run()
{
	std::cout << "Life after School.\n";

	bool running = true;
	while (running)
	{
		std::cout << "\n\n"
			"1. Administrator mode.\n"
			"2. Exit.\n";

		int command{};
		std::cout << "Enter a command: ";
		std::cin >> command;

		switch (command)
		{
		case 1:
			uiAdministratorMode();
			break;

		case 2:
			running = false;
			break;

		default:
			std::cout << "Unknown command.\n";
		}
	}

	std::cout << "Closing application...\n";
}

void Console::uiAdministratorMode()
{
	AdminConsole adminConsole(this->eventService);
	adminConsole.run();
}
