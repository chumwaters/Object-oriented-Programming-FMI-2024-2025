#include <iostream>
#include <fstream>

bool isSorted(const char* filename) {
	if (!filename) {
		std::cerr << "Bad name!\n";
	}

	std::ifstream file(filename);
	if (!file) {
		std::cerr << "Error opening file " << filename << " for reading!\n";
		return false;
	}

	int prev, curr;
	if (!(file >> prev)) {
		std::cerr << "The file is empty or contains invalid data!\n";
		return false;
	}

	while (file >> curr) {
		if (curr < prev) {
			std::cerr << "The numbers are not in ascending order!\n";
			return false;
		}

		prev = curr;
	}

	if (!file.eof()) {
		std::cerr << "The file contains invalid data!\n";
		return false;
	}

	std::cout << "The file is in valid format and the numbers are in ascending order!\n";
	return true;
}

int main() {
	char filename[256];
	std::cout << "Enter filename: ";
	std::cin >> filename;

	isSorted(filename);

	return 0;
}