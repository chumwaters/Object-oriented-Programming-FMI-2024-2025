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


	//Step 3: Print table
	db.printTable("people");

	return 0;
}