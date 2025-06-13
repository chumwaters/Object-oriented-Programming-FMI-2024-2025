#include "Database.h"

#include <iostream>

int main() {
	Database db;

	// Step 1: Create a table
	Table people("people");
	people.addColumn("ID", DataType::INT);
	people.addColumn("Name", DataType::STRING);
	people.addColumn("Birthday", DataType::DATE);
	people.addColumn("GPA", DataType::FLOAT);

	db.addTable(people);

	// Step 2: Insert sample data
	people.insert({ "1", "\"Alice\"", "01.01.2000", "3.75" });
	people.insert({ "2", "\"Bob\"", "15.06.1999", "NULL" });
	people.insert({ "3", "\"Carol\"", "28.02.2001", "4.00" });
	people.insert({ "4", "\"Bobby\"", "15.06.1999", "3.50" });

	// Step 3: Print table
	people.print();

	// Step 4: Select tests
	std::cout << "\n=== Select: Name contains 'Bob' ===\n";
	people.selectMatchingRows(1, "Bob");  // Should match "Bob" and "Bobby"

	std::cout << "\n=== Select: GPA equals '4.00' ===\n";
	people.selectMatchingRows(3, "4.00");  // Should match Carol only

	std::cout << "\n=== Select: ID equals '2' ===\n";
	people.selectMatchingRows(0, "2");  // Should match Bob only
	
	return 0;
}