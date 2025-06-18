#include "Database.h"
#include "CommandHandler.h"

#include <iostream>

int main() {
	try {
		// Step 1: Load Database from file
		Database db("database_file.txt");
		CommandHandler handler(db);

		// Step 2: Print table
		std::cout << "\n=== Print first table: people ===\n";
		handler.handleCommand("print people");

		std::cout << "\n=== Print second table: pets ===\n";
		handler.handleCommand("print pets");

		std::cout << "\n=== Print: non_existing_table (should fail) ===\n";
		handler.handleCommand("print non_existing_table");

		std::cout << "\n=== Print: wrong argument count (should fail) ===\n";
		handler.handleCommand("print people pets third");

		// Step 3: Showtables test
		std::cout << "\n=== Showtables: expect people, pets ===\n";
		handler.handleCommand("showtables");

		std::cout << "\n=== Showtables: wrong argument count (should fail) ===\n";
		handler.handleCommand("showtables arg");

		// Step 4: Describe tests
		std::cout << "\n=== Describe: people ===\n";
		handler.handleCommand("describe people");

		std::cout << "\n=== Describe: pets ===\n";
		handler.handleCommand("describe pets");

		std::cout << "\n=== Describe: non_existing_table (should fail) ===\n";
		handler.handleCommand("describe non_existing_table");

		std::cout << "\n=== Describe: wrong argument count (should fail) ===\n";
		handler.handleCommand("describe people pets");

		// Step 5: Select tests
		std::cout << "\n=== Select: (People) Name contains 'Bob' ===\n";
		handler.handleCommand("select 1 Bob people");

		std::cout << "\n=== Select: (People) GPA equals '4.00' ===\n";
		handler.handleCommand("select 3 4.00 people");

		std::cout << "\n=== Select: (People) ID equals '2' ===\n";
		handler.handleCommand("select 0 2 people");

		std::cout << "\n=== Select: (Pets) OwnerID == 2 ===\n";
		handler.handleCommand("select 1 2 pets");

		std::cout << "\n=== Select: (Pets) Name == 3 (expect 0 results) ===\n";
		handler.handleCommand("select 2 3 pets");

		std::cout << "\n=== Select: (Pets) PetID == \"Banana Peel\" (expect 0 results) ===\n";
		handler.handleCommand("select 0 \"Banana Peel\" pets");

		std::cout << "\n=== Select: (Pets) PetID == \"1\" (expect Fluffy) === \n";
		handler.handleCommand("select 0 \"1\" pets");

		std::cout << "\n=== Select: (People) Birthday == \"Pirate Ship\" (expect 0 results) ===\n";
		handler.handleCommand("select 2 \"Pirate Ship\" people");

		std::cout << "\n=== Select: (People) Birthday == 01.01.2000 (expect Alice) ===\n";
		handler.handleCommand("select 2 01.01.2000 people");

		std::cout << "\n=== Select: (People) Birthday == 01.01.2000.AC (expect 0 results) ===\n";
		handler.handleCommand("select 2 01.01.2000.AC people");

		std::cout << "\n=== Select: non_existing_table (should fail) ===\n";
		handler.handleCommand("select 2 \"Blackbeard\" non_existing_table");

		std::cout << "\n=== Select: Out of bounds index (should fail) ===\n";
		handler.handleCommand("select 10 42 people");

		std::cout << "\n=== Select: Negative index (should fail) ===\n";
		handler.handleCommand("select -5 42 people");

		std::cout << "\n=== Select: Invalid index (should fail) ===\n";
		handler.handleCommand("select marry 42 people");

		std::cout << "\n=== Select: wrong argument count (should fail) ===\n";
		handler.handleCommand("select 2 Max pets fourth");

		// Step 6: Update tests
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
		std::cout << "\n=== Export: Save people table to file ===\n";
		handler.handleCommand("export people people_export.txt");

		// Step 8: Save test 
		std::cout << "\n=== Save: Save database to file ===\n";
		handler.handleCommand("save");

		// Step 9: SaveAs test
		std::cout << "\n=== SaveAs: Save database to new file ===\n";
		handler.handleCommand("saveas database_file1.txt");

		// Step 10: Close test
		std::cout << "\n=== Close: Close current database ===\n";
		handler.handleCommand("close");

		// Step 11: Open test
		std::cout << "\n=== Open: Open original file ===\n";
		handler.handleCommand("open big_table.txt");

		// Step 12: Help test
		std::cout << "\n=== Help: Show a list of commands and their usage ===\n";
		handler.handleCommand("help");

		// Step 13: Paginated print test
		std::cout << "\n=== Paginated Print: 5 rows per page ===\n";
		handler.handleCommand("print people 5");

		// Step 14: Paginated select test
		std::cout << "\n=== Paginated Select: Name contains 'a' (case-sensitive) ===\n";
		handler.handleCommand("select 1 a people");

		// Step 15: Command prompt-and-execute loop
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