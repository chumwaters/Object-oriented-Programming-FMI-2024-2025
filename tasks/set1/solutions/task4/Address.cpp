#include "Address.h"

void readAddress(Address& a) {
	std::cout << "Enter city name: " << '\n';
	std::cin.getline(a.city, 32);
	std::cout << "Enter postal code: " << '\n';
	std::cin >> a.postCode;
	std::cout << "Enter street name: " << '\n';
	std::cin.getline(a.street, 64);
	std::cout << "Enter street number: " << '\n';
	std::cin >> a.streetNumber;
	std::cout << "Enter street character: " << '\n';
	std::cin >> a.streetCharacter;
	std::cout << "Enter building entrance: " << '\n';
	std::cin >> a.entrance;
	std::cout << "Enter floor number: " << '\n';
	std::cin >> a.floor;
	std::cout << "Enter apartment number: " << '\n';
	std::cin >> a.apartment;

}

void printAddress(const Address& a) {
	std::cout << "\"" << a.city << "\"" << ", " << a.postCode << ", " << "\"" << "ul. " << a.street << "\"" << ", " << a.streetNumber << ' ' << a.streetCharacter << ", " << "vh. " << a.entrance << ", et." << a.floor << ", ap." << a.apartment << '\n';
}