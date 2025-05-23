#pragma once

#include <string>

struct Date {
	int day	  = 1;
	int month = 1;
	int year  = 1900;

	//-----------------------------------
	// Helpers
	//-----------------------------------
	static bool isLeapYear(int y);
	static int daysInMonth(int m, int y);
	static bool isValid(int d, int m, int y);
	bool isValid() const { return isValid(day, month, year); };
	
	//-------------------------------------
	// String conversion and parsing
	//-------------------------------------
	
	/// @brief Method to convert Date object into string representation.
	/// @return String representation of Date object.
	std::string toString() const;

	/// @brief Method to parse Date object from string representation.
	/// @param str String representation of Date object.
	/// @param ok Boolean value to report to outside world if parsing fails.
	/// @return Parsed Date object from given string representation.
	static Date fromString(const std::string& str, bool& ok);
};
