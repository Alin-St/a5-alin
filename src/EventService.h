#pragma once

#include "Repository.h"
#include "Event.h"

/// <summary> Class containing all required functionality to manipulate a repository of events. </summary>
class EventService
{
private:
	Repository<Event>& repository;

public:
	/// <summary> Creates a service that uses a given repository. </summary>
	/// <param name="repository"> A repository that won't be destroyed while the service is in use. </param>
	EventService(Repository<Event>& repository);

	/// <summary> Get the number of events in the repository. </summary>
	size_t getCount() const;

	/// <summary> Adds event with the given properties to the repository. </summary>
	/// <param name="id"> The event's id. Use negative to auto-assign. </param>
	/// <returns> The id used to save the event. </returns>
	int add(int id, const char* title, const char* description, DateTime dateTime, int participants, const char* link);

	/// <summary> Finds the event with the specified id. </summary>
	/// <param name="reqEvent"> If found, the event will be saved here. </param>
	/// <returns> True if the event was found, otherwise false. </returns>
	bool find(int id, Event& reqEvent) const;

	/// <summary> Updates the event with the specified id with the given properties. </summary>
	/// <returns> The previous event. </returns>
	Event update(int id, const char* title, const char* description, DateTime dateTime, int participants, const char* link);

	/// <summary> Removes the event with the specified id. </summary>
	/// <returns> The removed event. </returns>
	Event remove(int id);

	/// <summary> Returns a list with all the events in the repository. </summary>
	DynamicVector<Event> listAll() const;


	/// <summary> Finds the event with the specified title. </summary>
	/// <param name="reqEvent"> If not null, saves the event to this address. </param>
	/// <returns> True if the event was found, false otherwise. </returns>
	bool findByTitle(const char* title, Event* reqEvent = nullptr) const;

	/// <summary> Adds an event with the specified properties and 0 participants if the title is not already used. </summary>
	void addByTitle(const char* title, const char* description, const DateTime& dateTime, const char* link);

	/// <summary> Updates the event with the specified title using the other properties. </summary>
	void updateByTitle(const char* title, const char* description, const DateTime& dateTime, int participants, const char* link);

	/// <summary> Removes the event with the specified title. </summary>
	void removeByTitle(const char* title);
};
