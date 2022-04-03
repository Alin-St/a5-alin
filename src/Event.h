#pragma once

#include "DateTime.h"
#include <string>

/// <summary> Used to store information about an event. </summary>
class Event
{
private:
	int id;
	std::string title;
	std::string description;
	DateTime dateTime;
	int participants;
	std::string link;

public:
	// CONSTRUCTOR / DESTRUCTOR.

	/// <summary> Create an empty event. </summary>
	Event();

	/// <summary> Create an event using the given properties. </summary>
	Event(int id, const char* title, const char* description, DateTime dateTime, int participants, const char* link);

	// PROPERTIES.

	/// <summary> Get event's id. </summary>
	int getId() const;

	/// <summary> Set event's id. </summary>
	void setId(int newId);

	/// <summary> Get event's title. </summary>
	const std::string& getTitle() const;

	/// <summary> Set event's title. </summary>
	void setTitle(const char* newTitle);

	/// <summary> Get event's description. </summary>
	const std::string& getDescription() const;

	/// <summary> Set event's description. </summary>
	void setDescription(const char* newDescription);

	/// <summary> Get event's date and time. </summary>
	const DateTime& getDateTime() const;

	/// <summary> Set event's date and time. </summary>
	void setDateTime(const DateTime& newDateTime);

	/// <summary> Get event's participants. </summary>
	int getParticipants() const;

	/// <summary> Set event's participants. </summary>
	void setParticipants(int newParticipants);

	/// <summary> Get event's link. </summary>
	const std::string& getLink() const;

	/// <summary> Set event's link. </summary>
	void setLink(const char* newLink);
};
