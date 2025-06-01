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
	db.insertInto("people", { "1", "\"Alice\"", "01.01.2000", "3.75" });
	db.insertInto("people", { "2", "\"Bob\"", "15.06.1999", "NULL" });
	db.insertInto("people", { "3", "\"Carol\"", "28.02.2001", "4.00" });


	// Step 3: Print table
	db.printTable("people");

	// Step 4: Select tests
	std::cout << "\n=== SELECT Name contains 'li' ===\n";
	db.selectMatchingRows("people", 1, "li");

	std::cout << "\n=== SELECT ID = 2 ===\n";
	db.selectMatchingRows("people", 0, "2");

	std::cout << "\n=== SELECT GPA = 4.00 ===\n";
	db.selectMatchingRows("people", 3, "4.00");

	std::cout << "\n=== SELECT Birthday = 28.02.2001 ===\n";
	db.selectMatchingRows("people", 2, "28.02.2001");

	std::cout << "\n=== SELECT Name contains 'x' (no match) ===\n";
	db.selectMatchingRows("people", 1, "x");

	std::cout << "\n=== SELECT on invalid column index ===\n";
	db.selectMatchingRows("people", 5, "something");

	std::cout << "\n=== SELECT with invalid int value ===\n";
	db.selectMatchingRows("people", 0, "notanint");


	return 0;
}