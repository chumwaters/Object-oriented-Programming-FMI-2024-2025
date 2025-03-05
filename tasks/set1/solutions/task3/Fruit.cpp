#pragma once

#include "Fruit.h"

void printFruit(Fruit fruit) {
	std::cout << "Fruit name: " << fruit.name << std::endl;

	std::cout << "Fruit color: ";
	printColor(fruit.cl);

	std::cout << "Annual?: ";
	printYN(fruit.annual);

	std::cout << "Perennial?: ";
	printYN(fruit.perennial);

	std::cout << "Tropical?: ";
	printYN(fruit.tropical);

	std::cout << '\n';
}

void printArrayOfFruits(Fruit** fruits, int size) {
	for (int i = 0; i < size; i++) {
		printFruit(*fruits[i]);
	}
	std::cout << '\n';
}

Fruit** createFruitArray(int size) {
	Fruit** fruitPtrArray = new (std::nothrow) Fruit * [size];

	if (!fruitPtrArray) {
		std::cout << "Failed to allocate memory for fruit array!\n";

		delete[] fruitPtrArray;
		return nullptr;
	}

	for (int i = 0; i < size; i++) {
		fruitPtrArray[i] = new Fruit;

		if (!fruitPtrArray[i]) {
			std::cout << "Failed to allocate memory for some fruit!\n";

			for (int j = 0; j < i; j++) {
				delete fruitPtrArray[j];
			}
			delete[] fruitPtrArray;

			return nullptr;
		}
	}

	for (int i = 0; i < size; i++) {
		std::cout << "Enter details for fruit " << i + 1 << ":\n";

		std::cout << "Enter fruit name: ";
		std::cin.ignore();
		std::cin.getline(fruitPtrArray[i]->name, 32);

		int colorVal = 0;
		do {
			std::cout << "Enter fruit color (0-brown, 1-green, 2-orange, 3-red, 4-yellow): ";
			std::cin >> colorVal;
		} while (!isValidColor((Color)colorVal));

		fruitPtrArray[i]->cl = (Color)colorVal;

		int annualVal = 0;
		do {
			std::cout << "Is the fruit annual? (0 - no; 1 - yes): ";
			std::cin >> annualVal;
		} while (!isValidYN((YN)annualVal));

		fruitPtrArray[i]->annual = (YN)annualVal;

		int perennialVal = 0;
		do {
			std::cout << "Is the fruit perennial? (0 - no; 1 - yes): ";
			std::cin >> perennialVal;
		} while (!isValidYN((YN)perennialVal));

		fruitPtrArray[i]->perennial = (YN)perennialVal;

		int tropicalVal = 0;
		do {
			std::cout << "Is the fruit tropical? (0 - no; 1 - yes): ";
			std::cin >> tropicalVal;
		} while (!isValidYN((YN)tropicalVal));

		fruitPtrArray[i]->tropical = (YN)tropicalVal;

		std::cout << std::endl;
	}

	return fruitPtrArray;
}

void clearArrayOfFruits(Fruit** fruits, int size) {
	for (int i = 0; i < size; i++) {
		delete fruits[i];
	}
	delete[] fruits;
}

void sortByField(Fruit** fruitArray, int size, int field, int order) {
	for (int i = 0; i < size; i++) {
		int minIndex = i;
		int maxIndex = i;
		
		for (int j = i + 1; j < size; j++) {
			switch (field) {
			case 0: // name
				if (strcmp(fruitArray[j]->name, fruitArray[minIndex]->name) < 0) {
					minIndex = j;
				}
				
				if (strcmp(fruitArray[j]->name, fruitArray[minIndex]->name) > 0) {
					maxIndex = j;
				}
				
				break;

			case 1: // color
				if ((int)fruitArray[j]->cl < (int)fruitArray[minIndex]->cl) {
					minIndex = j;
				}

				if ((int)fruitArray[j]->cl > (int)fruitArray[minIndex]->cl) {
					maxIndex = j;
				}
				
				break;
				
			case 2: // duration of fruiting 
				if ((int)fruitArray[j]->annual) {
					minIndex = j;
				}

				if ((int)fruitArray[j]->perennial) {
					maxIndex = j;
				}

				break;

			default: 
				std::cout << "Invalid field to sort by!\n";
			}	
		}

		if (order == 0) { // ascending
			std::swap(fruitArray[i], fruitArray[minIndex]);
		}
		else { // descending
			std::swap(fruitArray[i], fruitArray[maxIndex]);
		}

	}
}

void printPerennialTropicalFruits(Fruit** fruits, int size, Color cl) {
	for (int i = 0; i < size; i++) {
		if ((int)fruits[i]->cl == (int)cl && (int)fruits[i]->perennial && (int)fruits[i]->tropical) {
			printFruit(*fruits[i]);
		}
	}
}