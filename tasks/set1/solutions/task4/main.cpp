#include "Student.h"

int main() {

	Student s1;
	Student s2;
	Student s3;
	generateRandom(s1);
	generateRandom(s2);
	generateRandom(s3);
	print(s1);
	std::cout << "\nAverage score : " << calcAverageScore(s1);
	std::cout << "\n\n";
	print(s2);
	std::cout << "\nAverage score : " << calcAverageScore(s2);
	std::cout << "\n\n";
	print(s3);
	std::cout << "\nAverage score : " << calcAverageScore(s3);

	int size = 3;
	Student students[3] = { s1, s2, s3 };

	int filteredSize = 0;
	unsigned short threshold = 5;
	Student* filtered = filterAboveThreshold(students, size, filteredSize, threshold);

	std::cout << "\n\nStudents with average grade above " << threshold << ":\n";
	std::cout << "------------------------------------\n";
	for (int i = 0; i < filteredSize; i++) {
		print(filtered[i]);
		std::cout << "\n\n";;
	}

	delete[] filtered;
	clear(s1);
	clear(s2);
	clear(s3);
	
	return 0;
}