#include "Date.h"

#include <iostream>

bool Date::validateDate(unsigned int day, unsigned int month, int year)
{
	if (month < 1 || month > 12)
		return false;

	static unsigned int daysInMonth[] = {
		0, // dummy value for 1-indexing
		31, 28, 31, 30, 31, 30,
		31, 31, 30, 31, 30, 31};

	if (month == 2 && isLeapYear(year))
	{
		if (day < 1 || day > 29)
			return false;
	}

	return (day >= 1 && day <= daysInMonth[month]);
}

bool Date::isLeapYear(int year)
{
	// using that p => q is equivalent to !p || q
	return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

void Date::setDate(unsigned int day, unsigned int month, int year)
{
	if (validateDate(day, month, year))
	{
		this->day = day;
		this->month = month;
		this->year = year;

		return true;
	}

	return false; // TODO: throw maybe?
}

bool Date::read()
{
	unsigned int day, month;
	int year;
	char delim1, delim2;

	std::cout << "Enter sdate (DD/MM/YYYY): ";
	std::cin >> day >> delim1 >> month >> delim2 >> year;

	if (!std::cin || delim1 != '/' || delim2 != '/')
	{
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cout << "Invalid input format!\n";
		return false;
	}

	if (!setDate(day, month, year))
	{
		std::cout << "Invalid date.\n";
		return false;
	}

	return true;
}

void Date::print() const
{
	if (day < 10)
		std::cout << '0';
	std::cout << day << '/';

	if (month < 10)
		std::cout << '0';
	std::cout << month << '/';

	std::cout << year << "\n";
}