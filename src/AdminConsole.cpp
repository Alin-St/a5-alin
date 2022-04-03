#include "AdminConsole.h"
#include <iostream>

AdminConsole::AdminConsole(EventService& eventServ) : eventService(eventServ) {}

void AdminConsole::run()
{
	std::cout << "Using administrator mode...\n";

	bool running = true;
	while (running)
	{
		try
		{
			std::cout << "\n\n"
				"1. Add event.\n"
				"2. List all events.\n"
				"3. Update event.\n"
				"4. Delete event.\n"
				"5. Exit.\n";

			int command{};
			std::cout << "Enter a command: ";
			std::cin >> command;

			bool unknown = false;
			switch (command)
			{
			case 1:
				this->uiAddEvent();
				break;

			case 2:
				this->uiListAllEvents();
				break;

			case 3:
				this->uiUpdateEvent();
				break;

			case 4:
				this->uiDeleteEvent();
				break;

			case 5:
				running = false;
				break;

			default:
				std::cout << "Unknown command.\n";
				unknown = true;
			}

			if (running && !unknown)
				std::cout << "Operation completed successfully.\n";
		}
		catch (const std::exception& ex) {
			std::cout << "Error: " << ex.what() << '\n';
		}
	}

	std::cout << "Leaving administrator mode...\n";
}

void AdminConsole::uiAddEvent()
{
	std::string title, description, link;
	int year, month, day, hour, minute;

	std::cout << "Title: ";
	std::getline(std::cin, title);
	std::getline(std::cin, title);

	std::cout << "Description: ";
	std::getline(std::cin, description);

	std::cout << "Event year: ";
	std::cin >> year;

	std::cout << "Event month: ";
	std::cin >> month;

	std::cout << "Event day: ";
	std::cin >> day;

	std::cout << "Event hour: ";
	std::cin >> hour;

	std::cout << "Event minute: ";
	std::cin >> minute;

	std::cout << "Event link: ";
	std::getline(std::cin, link);
	std::getline(std::cin, link);

	this->eventService.addByTitle(title.c_str(), description.c_str(), DateTime(year, month, day, hour, minute, 0), link.c_str());
}

void AdminConsole::uiListAllEvents()
{
	auto events = this->eventService.listAll();
	this->printEvents(events, "All events:");
}

void AdminConsole::uiUpdateEvent()
{
	std::string title, description, link;
	int year, month, day, hour, minute, participants;

	std::cout << "Title: ";
	std::getline(std::cin, title);
	std::getline(std::cin, title);

	std::cout << "Description: ";
	std::getline(std::cin, description);

	std::cout << "Event year: ";
	std::cin >> year;

	std::cout << "Event month: ";
	std::cin >> month;

	std::cout << "Event day: ";
	std::cin >> day;

	std::cout << "Event hour: ";
	std::cin >> hour;

	std::cout << "Event minute: ";
	std::cin >> minute;

	std::cout << "Participants: ";
	std::cin >> participants;

	std::cout << "Event link: ";
	std::getline(std::cin, link);
	std::getline(std::cin, link);

	this->eventService.updateByTitle(title.c_str(), description.c_str(), DateTime(year, month, day, hour, minute, 0), participants, link.c_str());
}

void AdminConsole::uiDeleteEvent()
{
	std::string title;
	std::cout << "Title: ";
	std::getline(std::cin, title);
	std::getline(std::cin, title);

	this->eventService.removeByTitle(title.c_str());
}

void AdminConsole::printEvent(const Event& event, size_t index)
{
	const DateTime& dt = event.getDateTime();
	std::cout << index << ") "
		"Id: " << event.getId() << ", "
		"Title: \"" << event.getTitle() << "\", "
		"Description: \"" << event.getDescription() << "\", "
		"Date: " << dt.getMonth() << "/" << dt.getDay() << "/" << dt.getYear() << " " << dt.getHour() << ":" << dt.getMinute() << ", "
		"Participants: " << event.getParticipants() << ", "
		"Link: " << event.getLink() << "\n";
}

void AdminConsole::printEvents(const DynamicVector<Event> events, const char* prompt)
{
	std::cout << prompt << '\n';
	for (size_t i = 0; i < events.getLength(); ++i)
		this->printEvent(events[i], i + 1);
	if (events.getLength() == 0)
		std::cout << "No events.\n";
}
