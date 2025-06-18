#include "Date.h"

#include <exception>

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

Date Date::fromString(const std::string& str, bool& ok) {
	ok = false; // Will only be set to true after parsing is complete 
			    // and resulting Date is validated by isValid().
	Date d{};

	if (str.size() < 8) return d; // too short
	
	size_t firstDot = str.find('.');
	if (firstDot == std::string::npos) return d;
	
	size_t secondDot = str.find('.', firstDot + 1);
	if (secondDot == std::string::npos) return d;

	// Extracting substrings
	std::string dayStr   = str.substr(0, firstDot);
	std::string monthStr = str.substr(firstDot + 1, secondDot - firstDot - 1);
	std::string yearStr  = str.substr(secondDot + 1);
	if (dayStr.empty() || monthStr.empty() || yearStr.empty()) return d;

	// Converting them to ints; std::stoi may throw -- catch locally
	try {
		size_t posDay, posMonth, posYear;

		d.day = std::stoi(dayStr, &posDay);
		if (posDay != dayStr.size()) return d;

		d.month = std::stoi(monthStr, &posMonth);
		if (posMonth != monthStr.size()) return d;

		d.year = std::stoi(yearStr, &posYear);
		if (posYear != yearStr.size()) return d;
	}
	catch (const std::exception&) {
		return d;
	}

	ok = d.isValid();
	return d;
}

bool Date::operator==(const Date& rhs) const {
	return day == rhs.day && month == rhs.month && year == rhs.year;
}
