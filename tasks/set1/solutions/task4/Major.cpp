#include "Major.h"

bool isValidMajor(const Major& value) {
	return value > Major::MAJOR_UNKNOWN && value < Major::MAJOR_COUNT;
}

void read(Major& m) {
	int majorVal = 0;
	std::cout << "Enter students major (0 - Informatics, 1 - Computer Science, 2 - Information Systems, 3 - Software Engineering): ";
	std::cin >> majorVal;
	m = (Major)majorVal;
}

void print(const Major& m) {
	if (!isValidMajor) {
		std::cout << "Not a valid major!\n";
		return;
	}

	static const char* majors[(int)Major::MAJOR_COUNT] = {"Informatics", "Computer Science", "Information Systems", "Software Engineering"};
	std::cout << majors[(int)m] << '\n';
}

void generateRandom(Major& m) {
	m = (Major)((int)Major::INFORMATICS + rand() % (int)Major::MAJOR_COUNT);
}