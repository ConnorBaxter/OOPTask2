#include "Date.h"
#include <ctime>
#include <iostream>

Date::Date() {}

Date::Date(std::string&)
{
	
}

Date::~Date() = default;

Date &Date::getCurrentDate()
{
	time_t now = time(0);

	//Must be done to supress build error about localtime being unsafe?
	#pragma warning(suppress : 4996)
	tm* t = localtime(&now);

	//tm_year is relative to 1900 not 1970 or 0 because that would make too much sense 
	int year = t->tm_year + 1900;
	//tm_mon can be 0-11 but tm_mday can be 1-31 ...
	int month = t->tm_mon + 1;
	int day = t->tm_mday;
	
	Date d = std::to_string(day) + "-" + std::to_string(month) + "-" + std::to_string(year);

	return d;
}

const std::string &Date::toString(Date &d) const
{
	std::string retVal = std::to_string(d.Day) + "-" + std::to_string(d.Month) + "-" + std::to_string(d.Year);
	return retVal;
}
