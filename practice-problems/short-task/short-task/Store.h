#pragma once

#include "Phone.h"

class Store {
private:
	Phone* phones;
	size_t size;

	double budget;

	static bool validate(const double budget) { return budget >= 0; }
	void copy(const Store& other);
public:
	Store();
	Store(const double budget);
	Store(const Store& other);
	Store& operator=(const Store& other);
	~Store();

	void addPhone(const Phone& phone);
	void sellPhone(const char* model, const char* brand);
};
