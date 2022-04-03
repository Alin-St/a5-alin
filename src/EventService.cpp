#include "EventService.h"

EventService::EventService(Repository<Event>& repo) : repository(repo) {}

size_t EventService::getCount() const { return this->repository.getCount(); }

int EventService::add(int id, const char* title, const char* description, DateTime dateTime, int participants, const char* link)
{
	Event newEvent(0, title, description, dateTime, participants, link);
	id = (id < 0) ? -2 : id;
	return this->repository.save(id, newEvent);
}

bool EventService::find(int id, Event& reqEvent) const
{
	const Event* result = this->repository.get(id);
	if (result == nullptr)
		return false;
	reqEvent = *result;
	return true;
}

Event EventService::update(int id, const char* title, const char* description, DateTime dateTime, int participants, const char* link)
{
	Event oldEvent, newEvent(id, title, description, dateTime, participants, link);
	if (!this->repository.update(-1, newEvent, &oldEvent))
		throw std::logic_error("No event with the specified id found.");
	return oldEvent;
}

Event EventService::remove(int id)
{
	Event oldEvent;
	if (!this->repository.del(id, &oldEvent))
		throw std::logic_error("No event with the specified id found.");
	return oldEvent;
}

DynamicVector<Event> EventService::listAll() const
{
	DynamicVector<Event> result;
	for (const Event& curEvent : this->repository.getAll())
		result.add(curEvent);
	return result;
}

bool EventService::findByTitle(const char* title, Event* reqEvent) const
{
	for (const Event& curEvent : this->listAll()) {
		if (strcmp(curEvent.getTitle().c_str(), title) == 0) {
			if (reqEvent)
				*reqEvent = curEvent;
			return true;
		}
	}

	return false;
}

void EventService::addByTitle(const char* title, const char* description, const DateTime& dateTime, const char* link)
{
	if (this->findByTitle(title, nullptr))
		throw std::logic_error("Event title is already used.");

	this->add(-2, title, description, dateTime, 0, link);
}

void EventService::updateByTitle(const char* title, const char* description, const DateTime& dateTime, int participants, const char* link)
{
	Event curEvent;
	if (!this->findByTitle(title, &curEvent))
		throw std::logic_error("No event with the specified title found.");

	this->update(curEvent.getId(), title, description, dateTime, participants, link);
}

void EventService::removeByTitle(const char* title)
{
	Event remEvent;
	if (!this->findByTitle(title, &remEvent))
		throw std::logic_error("No event with the specified title found.");

	this->remove(remEvent.getId());
}
