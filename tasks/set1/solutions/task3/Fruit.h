#pragma once

#include "Color.h"
#include "YN.h"

struct Fruit {
	char name[32];
	Color cl;
	YN annual;
	YN perennial;
	YN tropical;
};

void printFruit(Fruit fruit);

void printArrayOfFruits(Fruit** fruits, int size);

Fruit** createFruitArray(int size);

void clearArrayOfFruits(Fruit** fruits, int size);

void sortByField(Fruit** fruitArray, int size, int field, int order);

void printPerennialTropicalFruits(Fruit** fruits, int size, Color cl);