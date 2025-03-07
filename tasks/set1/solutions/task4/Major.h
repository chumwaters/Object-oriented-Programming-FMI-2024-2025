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

void read(Major& m);

void print(const Major& m);

void generateRandom(Major& m);