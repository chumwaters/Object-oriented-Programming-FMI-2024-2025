#include "Color.h"

bool isValidColor(Color value) {
	return value > Color::COLOR_UNKNOWN && value < Color::COLOR_COUNT;
}

void printColor(Color c) {
	if (!isValidColor(c)) {
		std::cout << "Not a valid color!\n";
		return;
	}

	static const char* colors[(int)Color::COLOR_COUNT] = { "brown", "green", "orange", "red", "yellow" };
	std::cout << colors[(int)c] << std::endl;
}
