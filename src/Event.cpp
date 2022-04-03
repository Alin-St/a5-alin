#include "Event.h"

Event::Event() : id(0), title(), description(), dateTime(), participants(0), link() {}

Event::Event(int id, const char* title, const char* description, DateTime dateTime, int participants, const char* link) : Event()
{
	setId(id);
	setTitle(title);
	setDescription(description);
	setDateTime(dateTime);
	setParticipants(participants);
	setLink(link);
}

int Event::getId() const
{
	return this->id;
}

void Event::setId(int newId)
{
	this->id = newId;
}

const std::string& Event::getTitle() const
{
	return this->title;
}

void Event::setTitle(const char* newTitle)
{
	this->title = std::string(newTitle);
}

const std::string& Event::getDescription() const
{
	return this->description;
}

void Event::setDescription(const char* newDescription)
{
	this->description = std::string(newDescription);
}

const DateTime& Event::getDateTime() const
{
	return this->dateTime;
}

void Event::setDateTime(const DateTime& newDateTime)
{
	this->dateTime = newDateTime;
}

int Event::getParticipants() const
{
	return this->participants;
}

void Event::setParticipants(int newParticipants)
{
	this->participants = newParticipants;
}

const std::string& Event::getLink() const
{
	return this->link;
}

void Event::setLink(const char* newLink)
{
	this->link = newLink;
}
