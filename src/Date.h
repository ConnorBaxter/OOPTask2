#pragma once
#include <string>

class Date
{
public:
	Date();
	Date(std::string&);
	~Date();
	
	Date &getCurrentDate();

	const std::string& toString(Date&) const;

private:
	int Day;
	int Month;
	int Year;
};

