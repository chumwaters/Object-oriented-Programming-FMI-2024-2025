#pragma once

#include "Phone.h"

class Smartphone : public Phone {
private:
	char* operatingSystem;
	unsigned int memory;

	static bool validate(const unsigned int memory) { return memory >= 0; }
	void copy(const Smartphone& other);
public:
	Smartphone();
	Smartphone(char* model, char* brand, double price, 
		char* operatingSystem, unsigned int memory);
	Smartphone(const Smartphone& other);
	Smartphone& operator=(const Smartphone& other);
	~Smartphone();
};
