#include <fstream>

#include "Types.h"

unsigned short generateNewId(const char* filename, size_t recordSize) {
	std::ifstream f(filename, std::ios::binary);
	if (!f) return 0;

	unsigned short maxId = 0;
	char buffer[512];
	while (f.read(buffer, recordSize)) {
		unsigned short id;
		memcpy(&id, buffer, sizeof(id));
		if (id > maxId) maxId = id;
	}

	return maxId + 1;
}

void savePlayer(const Player& p) {
	std::ofstream f("players.dat", std::ios::binary | std::ios::app);
	f.write((const char*)&p, sizeof(p));
}

void saveCard(const Card& c) {
	std::ofstream f("cards.dat", std::ios::binary | std::ios::app);
	f.write((const char*)&c, sizeof(c));
}

void saveDeck(const Deck& d) {
	std::ofstream f("decks.dat", std::ios::binary | std::ios::app);
	f.write((const char*)&d, sizeof(d));
}

bool loadPlayerByName(const char* name, Player& out) {
	std::ifstream f("players.dat", std::ios::binary);

	Player p;
	while (f.read((char*)&p, sizeof(p))) {
		if (strcmp(p.name, name) == 0) {
			out = p;
			return true;
		}
	}

	return false;
}

bool loadCardByName(const char* name, Card& out) {
	std::ifstream f("cards.dat", std::ios::binary);

	Card c;
	while (f.read((char*)&c, sizeof(c))) {
		if (strcmp(c.name, name) == 0) {
			out = c;
			return true;
		}
	}

	return false;
}