#pragma once

#include <iostream>

struct Address {
	char city[32];
	unsigned int postCode;
	char street[64];
	unsigned int streetNumber;
	char streetCharacter; 
	short entrance;
	short floor;
	short apartment;
};

void readAddress(Address& a);

void printAddress(const Address& a);

