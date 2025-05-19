#pragma once

struct Date {
	int day	  = 1;
	int month = 1;
	int year  = 1900;

	//-----------------------------------
	// Helpers
	//-----------------------------------
	static bool isLeapYear(int y);
	static int daysInMonth(int m, int y);
};
