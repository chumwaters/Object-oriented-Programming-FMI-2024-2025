#pragma once

#include <fstream>

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

void readFromFile(Major& m, std::ifstream& file);

void print(const Major& m);

void writeToFile(const Major& m, std::ofstream& file);

void generateRandom(Major& m);