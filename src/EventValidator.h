#pragma once

#include "Event.h"

/// <summary> Used to validate an event. </summary>
class EventValidator
{
private:
	/// <summary> Returns true if the given string doesn't contain any special characters and is not null or too big. </summary>
	bool validateString(const char* str);

public:
	/// <summary> Validates the event and returns true if it is valid and false if it is not. </summary>
	void validate(const Event& event);

	void operator()(const Event& event);
};
