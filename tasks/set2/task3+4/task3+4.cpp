#include <iostream>
#include <fstream>

/// @brief Function that checks that a file is in the format specified in the task and is sorted in non-descending order.
/// @param filename : Name of file to be checked. 
/// @return True if file meets the requirements, false otherwise.
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
		std::cerr << "The file " << filename << " is empty or contains invalid data!\n";
		return false;
	}

	while (file >> curr) {
		if (curr < prev) {
			std::cerr << "The numbers in file " << filename << " are not in non-descending order!\n";
			return false;
		}

		prev = curr;
	}

	if (!file.eof()) {
		std::cerr << "The file " << filename << " contains invalid data!\n";
		return false;
	}

	file.close();
	return true;
}

/// @brief Function that merges two sorted files file1 and file2 in file1 
/// by creating and using a temporary file.
/// @param file1 : Opened for reading and writing and validated file stream .
/// @param file2 : Opened for reading and validated file stream .
void mergeSortedFiles(std::fstream& file1, std::ifstream& file2) {
	std::ofstream tempFile("temp.txt");
	if (!tempFile) {
		std::cerr << "Error: Could not creat temporary file to use as buffer for merging!\n";
		return;
	}

	// Both files have at least 1 number, guaranteed by the isSorted function.
	bool hasNum1 = true;
	bool hasNum2 = true;

	int num1, num2;
	file1 >> num1; 
	file2 >> num2;

	while (hasNum1 && hasNum2) {
		if (num1 <= num2) {
			tempFile << num1 << " ";
			hasNum1 = (file1 >> num1) ? true : false;  // Using implicit check here since conversion to bool 
			// doesn't happen automatically in assignment. Alternative is 
			// static_cast<bool> -- still not sure which is better.
		}
		else {
			tempFile << num2 << " ";
			hasNum2 = (file2 >> num2) ? true : false;
		}
	}

	// Copying the remaining numbers from whichever file has them
	while (hasNum1) {
		tempFile << num1 << " ";
		hasNum1 = (file1 >> num1) ? true : false;
	}

	while (hasNum2) {
		tempFile << num2 << " ";
		hasNum2 = (file2 >> num2) ? true : false;
	}

	file2.close();
	tempFile.close();

	// Overwriting file1 contents with merged content.
	// First, moving the cursor in file1 back to the beginning:
	file1.clear();
	file1.seekp(0);
	if (!file1) {
		std::cerr << "Error moving write-cursor in merge-file!\n";
		return;
	}

	// Now, reopening the temporary file for reading:
	std::ifstream tempReadFile("temp.txt");
	if (!tempReadFile) {
		std::cerr << "Error opening temporary file for reading!\n";
		return;
	}

	// Overwriting:
	int tempNum;
	while (tempReadFile >> tempNum) {
		file1 << tempNum << " ";
	}

	tempReadFile.close();
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cerr << "This program requires arguments!\n";
		return 1;
	}

	std::fstream mergeFile(argv[1], std::ios::in | std::ios::out);
	if (!mergeFile) {
		std::cerr << "Couldn't open file " << argv[1] << " for reading and writing!\n";
		return 1;
	}

	for (int i = 2; i < argc; i++) {
		if (!isSorted(argv[i])) {
			return 1;
		}

		std::ifstream inputFile(argv[i]);
		if (!inputFile) {
			std::cerr << "Couldn't open file " << argv[i] << " for reading!\n";
			return 1;
		}

		mergeSortedFiles(mergeFile, inputFile);
		mergeFile.clear();
		mergeFile.seekg(0);	
		if (!mergeFile) {
			std::cerr << "Error moving read-cursor in merge-file to beginning!\n";
		}
	}

	mergeFile.close();

	return 0;
}