#include "Types.h"
#include "FileHelpers.cpp"

#include <vector>
#include <map>
#include <iostream>

void cmd_cp(const std::string& name) {
	Player p;
	p.id = generateNewId("players.dat", sizeof(Player));
	strncpy(p.name, name.c_str(), 127);
	p.name[127] = '\0';
	savePlayer(p);
}

void cmd_cc(const std::string& colorStr, const std::string& name) {
	Card c;
	c.id = generateNewId("cards.dat", sizeof(Card));
	strncpy(c.name, name.c_str(), 63);
	c.name[63] = '\0';
	c.color = strToColor(colorStr.c_str());
	saveCard(c);
}

void cmd_cd(const std::string& playerName, const std::vector<std::string>& cardNames) {
	if (cardNames.size() != 60) {
		std::cerr << "Deck must contain 60 cards!\n";
		return;
	}

	Player p;
	if (!loadPlayerByName(playerName.c_str(), p)) {
		std::cerr << "No such player!\n";
		return;
	}

	Deck d;
	d.ownerId = p.id;

	std::map<Color, int> colorCount;
	for (size_t i = 0; i < cardNames.size(); ++i) {
		Card c;
		if (!loadCardByName(cardNames[i].c_str(), c)) {
			std::cerr << "Invalid card: " << cardNames[i] << "\n";
			return;
		}

		d.cardIds[i] = c.id;
		colorCount[c.color]++;
	}

	Color mostFreq = Color::Red;
	int maxCnt = -1;
	for (auto& kv : colorCount) {
		if (kv.second > maxCnt) {
			maxCnt = kv.second;
			mostFreq = kv.first;
		}
	}

	d.color = mostFreq;

	saveDeck(d);
}

void cmd_report() {
	std::ifstream fd("decks.dat", std::ios::binary);
	std::ofstream out("reports.txt");

	std::map<Color, std::vector<Deck>> decksByColor;
	Deck d;
	while (fd.read((char*)&d, sizeof(d))) {
		decksByColor[d.color].push_back(d);
	}

	std::map<unsigned short, int> cardUsage;

	for (auto& kv : decksByColor) {
		out << colorToStr(kv.first) << "\n";
		
		for (auto& deck : kv.second) {
			Player p;
			std::ifstream fp("players.dat", std::ios::binary);
			Player tmp;
			while (fp.read((char*)&tmp, sizeof(tmp))) {
				if (tmp.id == deck.ownerId) {
					p = tmp;
					break;
				}
			}

			Card first;
			std::ifstream fc("cards.dat", std::ios::binary);
			Card tmpc;
			while (fc.read((char*)&tmpc, sizeof(tmpc))) {
				if (tmpc.id == deck.cardIds[0]) {
					first = tmpc;
					break;
				}
			}

			out << "Owner: " << p.name 
				<< "Card: " << first.name 
				<< "Color: " << colorToStr(deck.color) << "\n";

			for (int i = 0; i < 60; ++i) {
				cardUsage[deck.cardIds[i]]++;
			}
		}	
	}

	unsigned short mostUsedCardId = 0;
	int mostUsedCnt = -1;
	for (auto& kv : cardUsage) {
		if (kv.second > mostUsedCnt) {
			mostUsedCnt = kv.second;
			mostUsedCardId = kv.first;
		}
	}

	Card mostUsedCard;
	loadCardByName("", mostUsedCard);
	std::ifstream fc("cards.dat", std::ios::binary);
	Card tmpc;

	while (fc.read((char*)&tmpc, sizeof(tmpc))) {
		if (tmpc.id == mostUsedCardId) {
			mostUsedCard = tmpc;
			break;
		}
	}

	out << "\nMost common card: " << mostUsedCard.name
		<< " Color: " << colorToStr(mostUsedCard.color) << '\n';
}