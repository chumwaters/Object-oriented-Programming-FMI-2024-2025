#pragma once

#include <iostream>

enum Color {
	COLOR_UNKNOWN = -1,
	BROWN,
	GREEN,
	ORANGE,
	RED,
	YELLOW,
	COLOR_COUNT
};

bool isValidColor(Color value);

void printColor(Color c);