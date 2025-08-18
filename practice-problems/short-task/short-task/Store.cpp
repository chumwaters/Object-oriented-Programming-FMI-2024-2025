#include "Store.h"
#include <iostream>

void Store::copy(const Store& other) {
	phones = new Phone[other.size];
	for (size_t i = 0; i < other.size; ++i) {
		phones[i] = other.phones[i];
	}

	size = other.size;
	budget = other.budget;
}

Store::Store() {
	phones = nullptr;
	size = 0;
	budget = 1000;
}

Store::Store(const double budget) : size(0), phones(nullptr) {
	if (!validate(budget))
		throw std::invalid_argument("Budget must be non-negative!");

	this->budget = budget;
}

Store::Store(const Store& other) {
	copy(other);
}

Store& Store::operator=(const Store& other) {
	if (this != &other) {
		copy(other);
	}

	return *this;
}

Store::~Store() {
	delete[] phones;
}

void Store::addPhone(const Phone& phone) {
	if (budget - phone.getPrice() < 0)
		throw std::logic_error("Cannot add anymore phones - out of money!");		
	
	Phone* newPhones = new Phone[size + 1];
	for (size_t i = 0; i < size; ++i) {
		newPhones[i] = phones[i];
	}
	newPhones[size] = phone;

	delete[] phones;
	phones = newPhones;
	newPhones = nullptr;
	size++;
}

void Store::sellPhone(const char* model, const char* brand) {
	for (size_t i = 0; i < size; ++i) {
		if (strcmp(phones[i].getModel(), model) == 0 &&
			strcmp(phones[i].getBrand(), brand) == 0) 
		{
			Phone* newPhones = new Phone[size - 1];
			for (size_t j = 0; j < i; ++j) {
				newPhones[j] = phones[j];
			}
			for (size_t j = i; j < size - 1; ++j) {
				newPhones[j] = phones[j + 1];
			}

			delete[] phones;
			phones = newPhones;
			newPhones = nullptr;
			size--;
			budget += phones[i].getPrice();

			std::cout << "Sold phone " << model << " " << brand << " for " << phones[i].getPrice() << "leva!\n";
			std::cout << "New budget: " << budget << " leva.";
		}
	}
}