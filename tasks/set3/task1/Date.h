#pragma once

class Date {
private:
	unsigned int day;
	unsigned int month;
	int year;

public:
	bool validateDate(unsigned int day, unsigned int month, int year);
	bool isLeapYear(int year);
	bool setDate(unsigned int day, unsigned int month, int year); // interdependent fields - one setter
	bool read();
	void print() const;
};
