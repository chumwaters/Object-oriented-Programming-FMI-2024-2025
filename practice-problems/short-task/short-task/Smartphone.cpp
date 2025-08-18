#include "Smartphone.h"
#include <iostream>

void Smartphone::copy(const Smartphone& other) {
	Phone::copy(other);

	operatingSystem = new char[strlen(other.operatingSystem) + 1];
	strcpy(operatingSystem, other.operatingSystem);

	memory = other.memory;
}

Smartphone::Smartphone() : Phone() {
	operatingSystem = new char[8];
	strcpy(operatingSystem, "DEFAULT");

	memory = 0;
}

Smartphone::Smartphone(char* model, char* brand, double price,
	char* operatingSystem, unsigned int memory) : Phone(model, brand, price) 
{
	if (!validate(memory))
		throw std::invalid_argument("Memory must be non-negative.");

	this->operatingSystem = new char[strlen(operatingSystem) + 1];
	strcpy(this->operatingSystem, operatingSystem);

	this->memory = memory;

	setPrice(getPrice() + memory);
}

Smartphone::Smartphone(const Smartphone& other) {
	copy(other);
}

Smartphone& Smartphone::operator=(const Smartphone& other) {
	if (this != &other) {
		copy(other);
	}

	return *this;
}

Smartphone::~Smartphone() {
	delete[] operatingSystem;
}