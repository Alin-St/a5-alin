#pragma once

#include <ctime>

/// <summary> Used to save a date along with the specific time in that day. </summary>
class DateTime
{
private:
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;

public:
	/// <summary> Initialize default DateTime (everything is 0). </summary>
	DateTime();

	/// <summary> Initialize DateTime with the given properties. </summary>
	DateTime(int year, int month, int day, int hour, int minute, int second);

	/// <summary> Initialize DateTime using a tm structure. </summary>
	DateTime(std::tm localTime);

	/// <summary> Initalize DateTime using a time_t structure. </summary>
	DateTime(std::time_t time);

	/// <summary> Get the DateTime's year. </summary>
	int getYear() const;

	/// <summary> Set the DateTime's year. </summary>
	void setYear(int newYear);

	/// <summary> Get the DateTime's month. </summary>
	int getMonth() const;

	/// <summary> Set the DateTime's month. </summary>
	void setMonth(int newMonth);

	/// <summary> Get the DateTime's day. </summary>
	int getDay() const;

	/// <summary> Set the DateTime's day. </summary>
	void setDay(int newDay);

	/// <summary> Get the DateTime's hour. </summary>
	int getHour() const;

	/// <summary> Set the DateTime's hour. </summary>
	void setHour(int newHour);

	/// <summary> Get the DateTime's minute. </summary>
	int getMinute() const;

	/// <summary> Set the DateTime's minute. </summary>
	void setMinute(int newMinute);

	/// <summary> Get the DateTime's second. </summary>
	int getSecond() const;

	/// <summary> Set the DateTime's second. </summary>
	void setSecond(int newSecond);

	/// <summary> Get the DateTime's local time. </summary>
	std::tm getLocalTime() const;

	/// <summary> Set the DateTime's local time. </summary>
	void setLocalTime(std::tm newLocalTime);

	/// <summary> Get the DateTime's time_t. </summary>
	std::time_t getTime() const;

	/// <summary> Set the DateTime's time_t. </summary>
	void setTime(std::time_t newTime);
};
