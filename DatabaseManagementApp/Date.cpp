#include "Date.h"

bool Date::isLeapYear(int y) {
	return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int Date::daysInMonth(int m, int y) {
	static const int days[12] = { 31, 28, 31,30,31,30,31,31,30,31,30,31 };
	
	if (m == 2 && isLeapYear(y)) return 29;
	
	return days[m - 1];
}

bool Date::isValid(int d, int m, int y) {
	if (y < 1900 || m < 1 || m > 12) return false;

	int dim = daysInMonth(m, y);

	return d >= 1 && d <= dim;
}

std::string Date::toString() const {
	if (!isValid()) return "INVALID_DATE";

	std::string s;

	if (day < 10) s += '0';
	s += std::to_string(day);
	s += '.';

	if (month < 10) s += '0';
	s += std::to_string(month);
	s += '.';

	s += std::to_string(year);

	return s;
}