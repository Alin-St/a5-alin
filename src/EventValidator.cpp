#include "EventValidator.h"
#include <stdexcept>

bool EventValidator::validateString(const char* str)
{
	if (str == NULL || strlen(str) > 100)
		return false;

	for (size_t i = 0; str[i] != '\0'; ++i) {
		if (!isalnum(str[i]) && !strchr("`~!@#$%^&*()-_=+[{]}\\|;:\'\",<.>/? ", str[i]))
			return false;
	}

	return true;
}

void EventValidator::validate(const Event& event)
{
	if (event.getId() < 0)
		throw std::logic_error("Event id cannot be less than 0.");

	if (!this->validateString(event.getTitle().c_str()))
		throw std::logic_error("Invalid event title.");

	if (!this->validateString(event.getDescription().c_str()))
		throw std::logic_error("Invalid event description.");

	if (event.getDateTime().getTime() < 0)
		throw std::logic_error("Invalid event time.");

	if (event.getParticipants() < 0)
		throw std::logic_error("Event participants number cannot be less than 0.");

	if (!this->validateString(event.getLink().c_str()))
		throw std::logic_error("Invalid event link.");
}

void EventValidator::operator()(const Event& event)
{
	this->validate(event);
}
