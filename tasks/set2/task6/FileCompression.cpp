#include <iostream>
#include <fstream>

/// @brief Function that replaces consecutive whitespaces with only one whitespace.
/// @param inputFile File opened for reading, verified to be in good state.
/// @param outputFile File opened for writing, verified to be in good state.
void compressFile(std::ifstream& inputFile, std::ofstream& outputFile) {
	char curr, prev = 0;

	while (inputFile.get(curr)) {
		if ((curr == ' ' || curr == '\t' || curr == '\n') &&
			(prev == ' ' || prev == '\t' || prev == '\n')) {
			continue;
		}

		outputFile.put(curr);
		prev = curr;
	}
}

int main() {
	std::ifstream testIn("testIn.txt");
	if (!testIn) {
		std::cerr << "Failed to open file for reading!\n";
		return 1;
	}

	std::ofstream testOut("testOut.txt");
	if (!testOut) {
		std::cerr << "Failed to open file for writing!\n";
		return 1;
	}

	compressFile(testIn, testOut);

	return 0;
}