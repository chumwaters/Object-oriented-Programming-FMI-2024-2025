#pragma once

class Phone {
private:
	char* model;
	char* brand;
	double price;

	static bool validate(const double price) { return price > 0; }

protected:
	void copy(const Phone& other);

public:
	Phone();
	Phone(const char* model, const char* brand, const double price);
	Phone(const Phone& other);
	Phone& operator=(const Phone& other);
	~Phone();

	void setPrice(const double newPrice);

	char* getModel() const { return model; }
	char* getBrand() const { return brand; }
	double getPrice() const { return price; }
};