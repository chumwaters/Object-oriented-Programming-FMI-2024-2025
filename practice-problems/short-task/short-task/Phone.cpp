#include "Phone.h"
#include <iostream>

void Phone::copy(const Phone& other) {
	model = new char[strlen(other.model) + 1];
	strcpy(model, other.model);

	try {
		brand = new char[strlen(other.brand) + 1];
		strcpy(brand, other.brand);
	}
	catch (...) {
		delete[] model;
		throw;
	}

	this->price = other.price;
}

Phone::Phone() {
	model = new char[8];
	strcpy(model, "DEFAULT");

	brand = new char[8];
	strcpy(brand, "DEFAULT");

	price = 100;
}

Phone::Phone(const char* model, const char* brand, const double price) {
	if (!validate(price)) {
		throw std::invalid_argument("Phone price must be a positive number.");
	}

	this->model = new char[strlen(model) + 1];
	strcpy(this->model, model);

	try {
		this->brand = new char[strlen(brand) + 1];
		strcpy(this->brand, brand);
	}
	catch (...) {
		delete[] this->model; 
		throw;
	}
	
	this->price = price;
}

Phone::Phone(const Phone& other) {
	copy(other);
}

Phone& Phone::operator=(const Phone& other) {
	if (this != &other) {
		copy(other);
	}

	return *this;
}

Phone::~Phone() {
	delete[] model;
	delete[] brand;
}

void Phone::setPrice(const double newPrice) {
	if (!validate(newPrice)) {
		throw std::invalid_argument("Price must be a positive value.");
	}

	price = newPrice;
}