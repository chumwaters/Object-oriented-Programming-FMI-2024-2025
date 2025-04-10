#include "Date.h"

bool Date::validateDate(unsigned int day, unsigned int month, int year) {
	if (month < 1 || month > 12)
		return false;

	static unsigned int daysInMonth[] = {
		0, // dummy value for 1-indexing
		31, 28, 31, 30, 31, 30,
		31, 31, 30, 31, 30, 31 };

	if (month == 2 && isLeapYear(year)) {
		if (day < 1 || day > 29)
			return false;
	}

	return (day >= 1 && day <= daysInMonth[month]);
}

bool Date::isLeapYear(int year) {
							 // using that p => q is equivalent to !p || q
	return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

bool Date::setDate(unsigned int day, unsigned int month, int year) {
	if (validateDate(day, month, year)) {
		this->day = day;
		this->month = month;
		this->year = year;
		
		return true;
	}

	return false;
}