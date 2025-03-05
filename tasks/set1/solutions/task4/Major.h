#pragma once

#include <iostream>

enum Major {
	MAJOR_UNKNOWN = -1,
	INFORMATICS,
	COMPUTER_SCIENCE,
	INFORMATION_SYSTEMS,
	SOFTWARE_ENGINEERING,
	MAJOR_COUNT
};

bool isValidMajor(const Major& value);

void readMajor(Major& m);

void printMajor(const Major& m);