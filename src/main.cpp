#include "core.h"
#include <iostream>

int main()
{
	try {
		EventValidator eventValidator;
		Repository<Event> eventRepository(eventValidator);
		EventService eventService(eventRepository);

		addTestItems(eventRepository);

		Console console(eventService);
		console.run();
	}
	catch (const std::exception& ex) {
		std::cout << "Error: " << ex.what() << '\n';
		return -1;
	}

	std::cout << "Program finished.\n";

	_CrtDumpMemoryLeaks();
	return 0;
}
