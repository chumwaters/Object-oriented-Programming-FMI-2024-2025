#include <iostream>

#include "DefaultDataSource.h"
#include "FileDataSource.h"
#include "ArrayDataSource.h"
#include "AlternateDataSource.h"

int main() {
	// --- Static arrays for ArrayDataSource
	int a[] = { 1, 2 };
	int b[] = { 10, 20, 30 };

	// Use copies of these arrays to avoid lifetime issues
	ArrayDataSource<int>* arrDS1 = new ArrayDataSource<int>(a, 2);
	ArrayDataSource<int>* arrDS2 = new ArrayDataSource<int>(b, 3);

	// DefaultDataSource (always returns default value)
	DefaultDataSource<int>* defDS = new DefaultDataSource<int>();

	// FileDataSource: "data.txt" should contain some ints (e.g., "100 200 300")
	FileDataSource<int>* fileDS = new FileDataSource<int>("data.txt");

	// --- AlternateDataSource with 3 sources
	DataSource<int>** sources = new DataSource<int>*[3];
	sources[0] = arrDS1;
	sources[1] = arrDS2;
	sources[2] = defDS;

	AlternateDataSource<int> altDS(sources, 3);

	std::cout << "Round-robin from AlternateDataSource:\n";
	for (int i = 0; i < 7; ++i) {  // just a fixed number of gets
		int x;
		altDS >> x;
		std::cout << x << " ";
	}

	std::cout << "\n\nResetting...\n";
	if (altDS.reset()) {
		for (int i = 0; i < 7; ++i) {
			std::cout << altDS() << " ";
		}
	}
	else {
		std::cout << "Some sources do not support reset.\n";
	}

	std::cout << "\n";

	return 0;
}