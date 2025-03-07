#pragma once

#include <iostream>

#define _CRT_SECURE_NO_WARNINGS_

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

void print(const Address& a);

char generateRandomChar();

void generateRandom(Address& a);