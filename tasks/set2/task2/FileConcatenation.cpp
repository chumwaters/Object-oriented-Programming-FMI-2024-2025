#include <iostream>
#include <fstream>

/// @brief Function that appends the content of one stream to another.
/// @param input : Input stream. Is either a file (in which case its state is verified to be good), or stdin.
/// @param output : Output stream - verified file stream.
void appendToFile(std::istream& input, std::ofstream& output) {
	char line[1024];

	while (input.getline(line, sizeof(line))) {
		if (strcmp(line, "STOP") == 0) {
			break;
		}

		output << line << "\n";
	}	
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cerr << "This program requires arguments!\n";
		return 1;
	}

	std::ofstream outputFile(argv[argc - 1], std::ios::app);
	if (!outputFile) {
		std::cerr << "Couldn't open file " << argv[argc - 1] << " for writing!\n";
		return 1;
	}

	if (argc == 2) {
		std::cout << "Enter content to append to file " << argv[1] << " (enter STOP on a new line to stop input):\n";
		appendToFile(std::cin, outputFile);
	}
	else {
		for (int i = 1; i < argc - 1; i++) {
			std::ifstream inputFile(argv[i]);
			if (!inputFile) {
				std::cerr << "Couldn't open file " << argv[i] << " for reading!\n";
				continue;
			}
			appendToFile(inputFile, outputFile);
		}
	}

	return 0;
}