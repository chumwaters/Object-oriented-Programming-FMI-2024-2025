#include "Address.h"

#include <iostream>

void read(Address& a) {
    std::cout << "Enter city: ";
    std::cin.getline(a.city, 32);

    std::cout << "Enter postal code: ";
    std::cin >> a.postCode;
    std::cin.ignore();

    std::cout << "Enter street: ";
    std::cin.getline(a.street, 64);

    std::cout << "Enter street number: ";
    std::cin >> a.streetNumber;

    std::cout << "Enter street character: ";
    std::cin >> a.streetCharacter;

    std::cout << "Enter entrance: ";
    std::cin >> a.entrance;

    std::cout << "Enter floor: ";
    std::cin >> a.floor;

    std::cout << "Enter apartment: ";
    std::cin >> a.apartment;
}

void readFromFile(Address& a, std::ifstream& file) {
    file.getline(a.city, 32);

    file >> a.postCode;
    file.ignore();

    file.getline(a.street, 64);

    file >> a.streetNumber;

    file >> a.streetCharacter;

    file >> a.entrance;

    file >> a.floor;

    file >> a.apartment;
}

void print(const Address& a) {
	std::cout << "\"" << a.city << "\"" << ", " << a.postCode << ", " << "\"" << "ul. " << a.street << "\"" << ", " << a.streetNumber << ' ' << a.streetCharacter << ", " << "vh. " << a.entrance << ", et." << a.floor << ", ap." << a.apartment << '\n';
}

void writeToFile(const Address& a, std::ofstream& file) {
    file << "\"" << a.city << "\"" << ", " << a.postCode << ", " << "\"" << "ul. " << a.street << "\"" << ", " << a.streetNumber << ' ' << a.streetCharacter << ", " << "vh. " << a.entrance << ", et." << a.floor << ", ap." << a.apartment << '\n';
}

char generateRandomChar() {
    return 'A' + rand() % 26;
}

void generateRandom(Address& a) {
    const char* cities[] = { "Plovdiv", "Ruse", "Burgas", "Varna", "Sofia" };
    const char* streets[] = { "Hristo Botev", "Ivan Vazov", "Tsar Simeon", "Vasil Levski", "Slavyanska" };

    strcpy_s(a.city, cities[rand() % (sizeof(cities) / sizeof(const char*))]);
    a.postCode = 1000 + rand() % 9000;
    strcpy_s(a.street, streets[rand() % (sizeof(streets) / sizeof(const char*))]);
    a.streetNumber = 1 + rand() % 10;
    a.streetCharacter = generateRandomChar();
    a.entrance = rand() % 10;
    a.floor = rand() % 10;
    a.apartment = rand() % 50;
}