#include "Student.h"

#include <iostream>
#include <fstream>

int main() {

	/*Student s;

	std::ifstream file("test.txt");
	if (!file) {
		std::cerr << "Failed to open file for reading!\n";
		return 1;
	}

	readFromFile(s, file);
	print(s);

	file.close();

	std::ofstream outFile("testOut.txt");
	if (!file) {
		std::cerr << "Failed to open file for writing!\n";
		return 1;
	}

	writeToFile(s, outFile);

	outFile.close();
	*/ 

	Student s1;
	Student s2;
	Student s3;
	Student s4;
	Student s5;
	generateRandom(s1);
	generateRandom(s2);
	generateRandom(s3);
	generateRandom(s4);
	generateRandom(s5);
	print(s1);
	std::cout << "\nAverage score : " << calcAverageScore(s1);
	std::cout << "\n\n";
	print(s2);
	std::cout << "\nAverage score : " << calcAverageScore(s2);
	std::cout << "\n\n";
	print(s3);
	std::cout << "\nAverage score : " << calcAverageScore(s3);
	std::cout << "\n\n";
	print(s4);
	std::cout << "\nAverage score : " << calcAverageScore(s4);
	std::cout << "\n\n";
	print(s5);
	std::cout << "\nAverage score : " << calcAverageScore(s5);

	int size = 5;
	Student students[5] = { s1, s2, s3, s4, s5 };

	std::ofstream outFile("testOut1.txt");

	printStraightAToFile(students, size, outFile);

	clear(s1);
	clear(s2);
	clear(s3);
	clear(s4);
	clear(s5);

	return 0;
}