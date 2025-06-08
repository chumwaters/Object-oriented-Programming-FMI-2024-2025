#include "Set.h"
#include "FiniteSet.h"
#include "Intersection.h"
#include "Union.h"
#include "ConstructedSet.h"

#include <fstream>
#include <iostream>

uint32_t* global_array = nullptr;
std::size_t global_size = 0;

static bool False(uint32_t) { return false; }

static bool dividesAll(const uint32_t num) {
	for (unsigned i = 0; i < global_size; ++i) {
		if (global_array[i] % num != 0)
			return false;
	}

	return true;
}

static bool dividesAny(const uint32_t num) {
	for (unsigned i = 0; i < global_size; ++i) {
		if (global_array[i] % num == 0)
			return true;
	}

	return false;
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cerr << "This program accepts exactly one argument!\n";

		return 1;
	}

	std::ifstream file;
	file.open(argv[1]);

	// Creating empty set as a neutral value
	Set<uint32_t>* result = new ConstructedSet<uint32_t>(False);
	
	char line[512];
	while (file.getline(line, 512)) {
		uint16_t N, T;
		uint32_t numbers[32];

		std::ifstream innerFile(line, std::ios::binary);
		if (!innerFile.is_open()) {
			std::cerr << "Failed to open one of the files named in " << line << " for reading!\n";

			return 1;
		}

		innerFile.read(reinterpret_cast<char*>(&N), sizeof(uint16_t));
		innerFile.read(reinterpret_cast<char*>(&T), sizeof(uint16_t));

		for (unsigned i = 0; i < N; ++i) {
			innerFile.read(reinterpret_cast<char*>(&numbers[i]), sizeof(uint32_t));

			if (!innerFile) {
				std::cerr << "Only " << i << " numbers were read from file " << line;

				return 1;
			}
		}

		const Set<uint32_t>** operands = new Set<uint32_t>*[2];
		global_array = numbers;
		global_size = N;
		operands[1] = result;

		Set<uint32_t>* newResult;
		switch (T) {
			case 0:
				operands[0] = new FiniteSet<uint32_t>(numbers, N);
				newResult = new Union<uint32_t>(operands, 2); // ^takes ownership of this memory
				break;
			case 1:	
				operands[0] = new ConstructedSet<uint32_t>(dividesAll);;		
				newResult = new Union<uint32_t>(operands, 2);
				break;
			case 2:
				operands[0] = new ConstructedSet<uint32_t>(dividesAny);
				newResult = new Union<uint32_t>(operands, 2);
				break;
			case 8:
				operands[0] = new FiniteSet<uint32_t>(numbers, N);
				newResult = new Intersection<uint32_t>(operands, 2);
				break;
			case 9:
				operands[0] = new ConstructedSet<uint32_t>(dividesAll);
				newResult = new Intersection<uint32_t>(operands, 2);
				break;
			case 10:
				operands[0] = new ConstructedSet<uint32_t>(dividesAny); 
				newResult = new Intersection<uint32_t>(operands, 2);
				break;
		}

		delete result;
		result = newResult;

		delete[] operands;
	}
	
	delete result;

	return 0;
}