#include "Database.h"
#include "CommandHandler.h"

#include <iostream>

int main() {
	try {
		// Step 1: Load Database from file
		Database db("people_export.txt");
		CommandHandler handler(db);

		// Step 2: Print table
		std::cout << "\n=== Print first table: people ===\n";
		handler.handleCommand("print people");

		std::cout << "\n=== Print second table: pets ===\n";
		handler.handleCommand("print pets");

		// Step 3: Select tests
		std::cout << "\n=== Select: Name contains 'Bob' ===\n";
		handler.handleCommand("select 1 Bob people");

		std::cout << "\n=== Select: GPA equals '4.00' ===\n";
		handler.handleCommand("select 3 4.00 people");

		std::cout << "\n=== Select: ID equals '2' ===\n";
		handler.handleCommand("select 0 2 people");

		std::cout << "\n=== Select: OwnerID == 2 ===\n";
		handler.handleCommand("select 1 2 pets");

		// Step 4: Update tests
		std::cout << "\n=== Update: Set GPA to 3.90 for ID == 4 ===\n";
		handler.handleCommand("update people 0 4 3 3.90");

		std::cout << "\n=== Table after GPA update ===\n";
		handler.handleCommand("print people");

		std::cout << "\n=== People Update: Set ID to 99 for rows where Name contains 'Bob' ===\n";
		handler.handleCommand("update people 1 Bob 0 99");

		std::cout << "\n=== People Table after ID update ===\n";
		handler.handleCommand("print people");

		std::cout << "\n=== People Update: Attempt to update GPA where ID == 999 (no match expected) ===\n";
		handler.handleCommand("update people 0 999 3 2.50");

		std::cout << "\n=== People Table after no-match update ===\n";
		handler.handleCommand("print people");

		std::cout << "\n=== Pets Update: Rename Max to Buddy ===\n";
		handler.handleCommand("update pets 2 Max 2 Buddy");

		std::cout << "\n=== Pets Table after update ===\n";
		handler.handleCommand("print pets");

		// Step 5: Modify tests
		std::cout << "\n=== Modify: GPA (column 3) to STRING ===\n";
		handler.handleCommand("modify people 3 STRING");

		std::cout << "\n=== Table after GPA converted to STRING ===\n";
		handler.handleCommand("print people");

		std::cout << "\n=== Modify: Name (column 1) to INT (expect failures) ===\n";
		handler.handleCommand("modify people 1 INT");

		std::cout << "\n=== Table after Name converted to INT ===\n";
		handler.handleCommand("print people");

		// Step 6: Delete tests
		std::cout << "\n=== People Delete: Delete rows where ID == 99 ===\n";
		handler.handleCommand("delete people 0 99");

		std::cout << "\n=== People Table after deleting ID == 99 ===\n";
		handler.handleCommand("print people");

		std::cout << "\n=== People Delete: Delete rows where GPA == NULL ===\n";
		handler.handleCommand("delete people 3 NULL");

		std::cout << "\n=== People Table after deleting GPA == NULL ===\n";
		handler.handleCommand("print people");

		std::cout << "\n=== People Delete: Delete rows where Birthday == 28.02.2001 ===\n";
		handler.handleCommand("delete people 2 28.02.2001");

		std::cout << "\n=== People Table after deleting Birthday == 28.02.2001 ===\n";
		handler.handleCommand("print people");

		std::cout << "\n=== People Delete: Attempt to delete rows where Name == 999 (no match expected) ===\n";
		handler.handleCommand("delete people 1 999");

		std::cout << "\n=== People Table after no-match delete ===\n";
		handler.handleCommand("print people");

		std::cout << "\n=== Pets Delete: Remove pet named Fluffy ===\n";
		handler.handleCommand("delete pets 2 Fluffy");

		std::cout << "\n=== Pets Table after deletion ===\n";
		handler.handleCommand("print pets");

		// Step 7: Export test
		std::cout << "\n=== Export: Save table to file ===\n";
		handler.handleCommand("export people people_export.txt");

		// Step 8: Command prompt-and-execute loop
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

	}
	catch (const std::exception& ex) {
		std::cerr << "Load failed: " << ex.what() << '\n';
		return 1;
	}
	
	return 0;
}