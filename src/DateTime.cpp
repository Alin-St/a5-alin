#include "DateTime.h"

DateTime::DateTime() : year(0), month(0), day(0), hour(0), minute(0), second(0) {}

DateTime::DateTime(int year, int month, int day, int hour, int minute, int second) : DateTime()
{
	this->setYear(year);
	this->setMonth(month);
	this->setDay(day);
	this->setHour(hour);
	this->setMinute(minute);
	this->setSecond(second);
}

DateTime::DateTime(tm localTime) : DateTime()
{
	this->setLocalTime(localTime);
}

DateTime::DateTime(time_t time) : DateTime()
{
	this->setTime(time);
}

int DateTime::getYear() const
{
	return this->year;
}

void DateTime::setYear(int newYear)
{
	this->year = newYear;
}

int DateTime::getMonth() const
{
	return this->month;
}

void DateTime::setMonth(int newMonth)
{
	this->month = newMonth;
}

int DateTime::getDay() const
{
	return this->day;
}

void DateTime::setDay(int newDay)
{
	this->day = newDay;
}

int DateTime::getHour() const
{
	return this->hour;
}

void DateTime::setHour(int newHour)
{
	this->hour = newHour;
}

int DateTime::getMinute() const
{
	return this->minute;
}

void DateTime::setMinute(int newMinute)
{
	this->minute = newMinute;
}

int DateTime::getSecond() const
{
	return this->second;
}

void DateTime::setSecond(int newSecond)
{
	this->second = newSecond;
}

tm DateTime::getLocalTime() const
{
	std::tm localTime{};
	localTime.tm_year = this->year - 1900;
	localTime.tm_mon = this->month - 1;
	localTime.tm_mday = this->day;
	localTime.tm_hour = this->hour;
	localTime.tm_min = this->minute;
	localTime.tm_sec = this->second;
	return localTime;
}

void DateTime::setLocalTime(tm newLocalTime)
{
	this->year = newLocalTime.tm_year + 1900;
	this->month = newLocalTime.tm_mon + 1;
	this->day = newLocalTime.tm_mday;
	this->hour = newLocalTime.tm_hour;
	this->minute = newLocalTime.tm_min;
	this->second = newLocalTime.tm_sec;
}

time_t DateTime::getTime() const
{
	std::tm localTime = this->getLocalTime();
	return mktime(&localTime);
}

void DateTime::setTime(time_t newTime)
{
	std::tm localTime = *localtime(&newTime);
	this->setLocalTime(localTime);
}
