#pragma once

#include <fstream>

struct Address {
	char city[32];
	unsigned int postCode;
	char street[64];
	unsigned int streetNumber;
	char streetCharacter; 
	unsigned int entrance;
	unsigned int floor;
	unsigned int apartment;
};

void read(Address& a);
 
void readFromFile(Address& a, std::ifstream& file);

void print(const Address& a);

char generateRandomChar();

void generateRandom(Address& a);