#include "Fruit.h"

int main(){
	int size = 0;
	std::cout << "How many fruits would you like to create?: ";
	std::cin >> size;
	std::cout << '\n';

	Fruit** fruitPtrArray = createFruitArray(size);
	
	if (!fruitPtrArray) {
		return 1;
	}

	std::cout << "Array of fruits, sorted by name: \n";
	std::cout << "-------------------------------- \n";
	sortByField(fruitPtrArray, size, 0, 0);
	printArrayOfFruits(fruitPtrArray, size);

	std::cout << "Array of fruits, sorted by color: \n";
	std::cout << "--------------------------------- \n";
	sortByField(fruitPtrArray, size, 1, 0);
	printArrayOfFruits(fruitPtrArray, size);

	std::cout << "Array of fruits, sorted by duration of fruiting: \n";
	std::cout << "------------------------------------------------ \n";
	sortByField(fruitPtrArray, size, 2, 0);
	printArrayOfFruits(fruitPtrArray, size);

	int colorVal = 0;
	std::cout << "Now select a color (the program will sort all perenial, tropical fruits of that color and output the result - again (0-brown, 1-green, 2-orange, 3-red, 4-yellow)): ";
	std::cin >> colorVal; 
	std::cout << "Perenial, tropical fruits of color ";
	printColor(Color(colorVal));
	std::cout << ", sorted in descending order: \n";
	std::cout << "-------------------------------------- \n";
	sortByField(fruitPtrArray, size, 0, 1); 
	printPerennialTropicalFruits(fruitPtrArray, size, (Color)colorVal);


	clearArrayOfFruits(fruitPtrArray, size);

	return 0;
}