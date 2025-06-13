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
	handler.handleCommand("insert people 4 \"Bobby\" 15.06.1999 3.50");

	// Step 3: Print table
	handler.handleCommand("print people");

	// Step 4: Select tests
	std::cout << "\n=== Select: Name contains 'Bob' ===\n";
	handler.handleCommand("select 1 Bob people");  // Should match "Bob" and "Bobby"

	std::cout << "\n=== Select: GPA equals '4.00' ===\n";
	handler.handleCommand("select 3 4.00 people");  // Should match Carol only

	std::cout << "\n=== Select: ID equals '2' ===\n";
	handler.handleCommand("select 0 2 people");  // Should match Bob only

	// Step 5: Command prompt-and-execute loop
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