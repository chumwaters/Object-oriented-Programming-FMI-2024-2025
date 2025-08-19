#pragma once

#include <cstring>

enum Color {
	Red,
	Black,
	Blue,
	White,
	Green,
	InvalidColor
};

struct Player {
	char name[128];
	unsigned short id;
};

struct Card {
	char name[64];
	unsigned short id;
	Color color;
};

struct Deck {
	unsigned short ownerId;
	Color color;
	unsigned short cardIds[60];
};

const char* colorToStr(Color c) {
	switch (c) {
	case Color::Red: return "Red";
	case Color::Black: return "Black";
	case Color::Blue: return "Blue";
	case Color::White: return "White";
	case Color::Green: return "Green";
	}

	return "Invalid Color";
}

Color strToColor(const char* s) {
	if (strcmp(s, "Red") == 0) return Color::Red;
	if (strcmp(s, "Black") == 0) return Color::Black;
	if (strcmp(s, "Blue") == 0) return Color::Blue;
	if (strcmp(s, "White") == 0) return Color::White;
	if (strcmp(s, "Green") == 0) return Color::Green;

	return InvalidColor;
}
