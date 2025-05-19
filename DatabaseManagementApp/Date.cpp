#include "Date.h"

bool Date::isLeapYear(int y) {
	return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int Date::daysInMonth(int m, int y) {
	static const int days[12] = { 31, 28, 31,30,31,30,31,31,30,31,30,31 };
	
	if (m == 2 && isLeapYear(y)) return 29;
	
	return days[m - 1];
}