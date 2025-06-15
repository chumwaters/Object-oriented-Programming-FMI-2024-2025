#include "Database.h"
#include "CommandHandler.h"

#include <iostream>

int main() {
	Database db;
	CommandHandler handler(db);

	// Step 1: Create a table
	Table people("people");
	db.addTable(people);

	handler.handleCommand("addcolumn people \"ID\" INT");
	handler.handleCommand("addcolumn people \"Name\" STRING");
	handler.handleCommand("addcolumn people \"Birthday\" DATE");
	handler.handleCommand("addcolumn people \"GPA\" FLOAT");

	// Step 2: Insert sample data
	handler.handleCommand("insert people 1 \"Alice\" 01.01.2000 3.75");
	handler.handleCommand("insert people 2 \"Bob\" 15.06.1999 NULL");
	handler.handleCommand("insert people 3 \"Carol\" 28.02.2001 4.00");
	handler.handleCommand("insert people 4 \"Bobby John\" 15.06.1999 3.50");

	// Step 3: Print table
	handler.handleCommand("print people");

	// Step 4: Select tests
	std::cout << "\n=== Select: Name contains 'Bob' ===\n";
	handler.handleCommand("select 1 Bob people");

	std::cout << "\n=== Select: GPA equals '4.00' ===\n";
	handler.handleCommand("select 3 4.00 people");

	std::cout << "\n=== Select: ID equals '2' ===\n";
	handler.handleCommand("select 0 2 people"); 

	// Step 6: Update tests
	std::cout << "\n=== Update: Set GPA to 3.90 for ID == 4 ===\n";
	handler.handleCommand("update people 0 4 3 3.90");

	std::cout << "\n=== Table after GPA update ===\n";
	handler.handleCommand("print people");

	std::cout << "\n=== Update: Set ID to 99 for rows where Name contains 'Bob' ===\n";
	handler.handleCommand("update people 1 Bob 0 99");

	std::cout << "\n=== Table after ID update ===\n";
	handler.handleCommand("print people");

	std::cout << "\n=== Update: Attempt to update GPA where ID == 999 (no match expected) ===\n";
	handler.handleCommand("update people 0 999 3 2.50");

	std::cout << "\n=== Table after no-match update ===\n";
	handler.handleCommand("print people");
	
	// Step 6: Modify tests
	std::cout << "\n=== Modify: GPA (column 3) to STRING ===\n";
	handler.handleCommand("modify people 3 STRING");

	std::cout << "\n=== Table after GPA converted to STRING ===\n";
	handler.handleCommand("print people");

	std::cout << "\n=== Modify: Name (column 1) to INT (expect failures) ===\n";
	handler.handleCommand("modify people 1 INT");

	std::cout << "\n=== Table after Name converted to INT ===\n";
	handler.handleCommand("print people");

	// Step 7: Delete tests
	std::cout << "\n=== Delete: Delete rows where ID == 99 ===\n";
	handler.handleCommand("delete people 0 99");

	std::cout << "\n=== Table after deleting ID == 99 ===\n";
	handler.handleCommand("print people");

	std::cout << "\n=== Delete: Delete rows where GPA == NULL ===\n";
	handler.handleCommand("delete people 3 NULL"); 

	std::cout << "\n=== Table after deleting GPA == NULL ===\n";
	handler.handleCommand("print people");

	std::cout << "\n=== Delete: Delete rows where Birthday == 28.02.2001 ===\n";
	handler.handleCommand("delete people 2 28.02.2001");

	std::cout << "\n=== Table after deleting Birthday == 28.02.2001 ===\n";
	handler.handleCommand("print people");

	std::cout << "\n=== Delete: Attempt to delete rows where Name == 999 (no match expected) ===\n";
	handler.handleCommand("delete people 1 999");

	std::cout << "\n=== Table after no-match delete ===\n";
	handler.handleCommand("print people");

	// Step 8: Export test
	std::cout << "\n=== Export: Save table to file ===\n";
	handler.handleCommand("export people people_export.txt");

	// Step 9: Command prompt-and-execute loop
	std::string input;

	while (true) {
		std::cout << "> ";
		std::getline(std::cin, input);

		if (input == "exit") {
			std::cout << "Exiting. Goodbye!\n";
			break;
		}

		if (input.empty()) continue;

		try {
			handler.handleCommand(input);
		}
		catch (const std::exception& e) {
			std::cerr << "Fatal error: " << e.what() << "\n";
		}
	}

	
	return 0;
}