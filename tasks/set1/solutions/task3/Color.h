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

bool isValidColor(const Color& value);

void printColor(const Color& c);