#include "Database.h"
#include "CommandHandler.h"

#include <iostream>

int main() {
	try {
		// Step 1: Load Database from file
		Database db("database_file.txt");
		CommandHandler handler(db);

		std::cout << "\n=== Help: Show a list of commands and their usage ===\n";
		handler.handleCommand("help");

		// Step 2: Non-paginated Print tests
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

		// Step 5: Non-paginated Select tests
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

		std::cout << "\n=== Select: (People) GPA equals 4 (expect Carol) ===\n";
		handler.handleCommand("select 3 4 people");

		std::cout << "\n=== Select: (People) GPA equals 4.0000000000000001 (expect Carol) ===\n";
		handler.handleCommand("select 3 4.0000000000000001 people");

		std::cout << "\n=== Select: (People) GPA equals 3.501 (expect no results) ===\n";
		handler.handleCommand("select 3 3.501 people");

		std::cout << "\n=== Select: (People) GPA equals 3.50.14 (expect no results) ===\n";
		handler.handleCommand("select 3 3.50.14 people");

		std::cout << "\n=== Select: (People) ID equals 1asdf (expect no results) ===\n";
		handler.handleCommand("select 0 1asdf people");

		// Step 6: Update tests
		std::cout << "\n=== People Update: Set GPA to 3.90 for ID == 4 ===\n";
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

		std::cout << "\n=== People Update: Attempt to null out birthday where "
			"GPA == 3.90 ===\n";
		handler.handleCommand("update people 3 3.90 2 NULL");

		std::cout << "\n=== People Table after update ===\n";
		handler.handleCommand("print people");

		std::cout << "\n=== People Update: Attempt to set birthday where "
			"Birthday == NULL ===\n";
		handler.handleCommand("update people 2 NULL 2 15.06.1999");

		std::cout << "\n=== People Table after update ===\n";
		handler.handleCommand("print people");

		std::cout << "\n=== Pets Update: Attempt to set PetID to invalid value (should fail) ===\n";
		handler.handleCommand("update pets 2 \"Fluffy\" 0 \"Scruffy\"");

		std::cout << "\n=== Pets Table after update ===\n";
		handler.handleCommand("print pets");

		std::cout << "\n=== People Update: Attempt to set Birthday to semantically "
			"invalid value (should fail) ===\n";
		handler.handleCommand("update people 1 \"Carol\" 2 \"29.02.2001\"");

		std::cout << "\n=== People Table after update ===\n";
		handler.handleCommand("print people");

		std::cout << "\n=== People Update: Attempt to set Birthday to syntactically "
			"invalid value (should fail) ===\n";
		handler.handleCommand("update people 1 \"Carol\" 2 \"28.02.2001va\"");

		std::cout << "\n=== People Table after update ===\n";
		handler.handleCommand("print people");

		std::cout << "\n=== People Update: Attempt to set GPA to invalid value (should fail) ===\n";
		handler.handleCommand("update people 3 15.06.1999 3 6.00.01");

		std::cout << "\n=== People Table after update ===\n";
		handler.handleCommand("print people");

		std::cout << "\n=== Update: non_existing_table (should fail) ===\n";
		handler.handleCommand("update non_existing_table 4 \"Clownfish\" 4 \"Seahorse\"");

		std::cout << "\n=== Update: Out of bounds indeces (should fail) ===\n";
		handler.handleCommand("update people 10 \"Sea Urchin\" 1 \"Bobby \\\"Sea Urchin\\\" John\"");
		handler.handleCommand("update people 1 \"Bobby John\" 5 \"Fishing\"");

		std::cout << "\n=== Update: Negative indeces (should fail) ===\n";
		handler.handleCommand("update pets -8 777 1 7777");
		handler.handleCommand("update pets 2 \"Bella\" -2 \"alleB\"");

		std::cout << "\n=== Update: Invalid index (should fail) ===\n";
		handler.handleCommand("update pets one 1 1 2");
		handler.handleCommand("update pets 1 1 one 2");
		handler.handleCommand("update pets 1one 1 1 2");
		handler.handleCommand("update pets 1 1 1one 2");

		std::cout << "\n=== Pets Table after invalid-index updates ===\n";
		handler.handleCommand("print pets");

		std::cout << "\n=== Update: wrong argument count (should fail) ===\n";
		handler.handleCommand("update people 0 1 \"Alisson\"");
		handler.handleCommand("update people 0 1 1 \"Alisson\" sixth");

		std::cout << "\n=== People Table after wrong argument count updates ===\n";
		handler.handleCommand("print people");

		// Step 7: Modify tests
		std::cout << "\n=== People Modify: GPA (column 3) to STRING ===\n";
		handler.handleCommand("modify people 3 STRING");

		std::cout << "\n=== Table after GPA converted to STRING ===\n";
		handler.handleCommand("print people");

		std::cout << "\n=== People Modify: Update GPA (column 3) where GPA == 4.00 to \"Good\" ===\n";
		handler.handleCommand("update people 3 4.00 3 \"Good\"");

		std::cout << "\n=== Table after update of Carol's GPA to \"Good\" ===\n";
		handler.handleCommand("print people");

		std::cout << "\n=== People Modify: Name (column 1) to INT (expect failures) ===\n";
		handler.handleCommand("modify people 1 INT");

		std::cout << "\n=== Table after Name converted to INT ===\n";
		handler.handleCommand("print people");

		std::cout << "\n=== People Modify: Attempt to Update Name (column 1) where GPA == \"Good\" "
			"to 1234asdf (should fail) ===\n";
		handler.handleCommand("update people 3 \"Good\" 1 1234asdf");

		std::cout << "\n=== Table after attempting to set the NONE name where GPA is \"Good\" "
			"to 1234asdf ===\n";
		handler.handleCommand("print people");

		std::cout << "\n=== Pets Modify: Name (column 2) to NONE (should fail) ===\n";
		handler.handleCommand("modify pets 1 NONE");

		std::cout << "\n=== Pets Table after failed conversion of Name to NONE ===\n";
		handler.handleCommand("print pets");

		std::cout << "\n=== Pets Modify: PetID (column 0) to arbitrary unrecognized type (should fail) ===\n";
		handler.handleCommand("modify pets 0 SOME_UNKNOWN_TYPE");

		std::cout << "\n=== Pets Table after failed conversion of Name to SOME_UNKNOWN_TYPE ===\n";
		handler.handleCommand("print pets");

		std::cout << "\n=== Pets Modify: PetID (column 0) to FLOAT ===\n";
		handler.handleCommand("modify pets 0 FLOAT");

		std::cout << "\n=== Pets Table after converting PetID (column 0) to FLOAT ===\n";
		handler.handleCommand("print pets");

		std::cout << "\n=== Pets Modify: Updating PetID where Name == \"Buddy\" to 2.50 ===\n";
		handler.handleCommand("update pets 2 \"Buddy\" 0 2.50");

		std::cout << "\n=== Pets Table after updating the PetID of \"Buddy\" to 2.50 ===\n";
		handler.handleCommand("print pets");

		std::cout << "\n=== Modify: non_existing_table (should fail) ===\n";
		handler.handleCommand("modify non_existing_table 0 FLOAT");

		std::cout << "\n=== Modify: Out of bounds index (should fail) ===\n";
		handler.handleCommand("modify pets 34 DATE");

		std::cout << "\n=== Pets Table after attempting modification with out of bounds index===\n";
		handler.handleCommand("print pets");

		std::cout << "\n=== Modify: Negative index (should fail) ===\n";
		handler.handleCommand("modify pets -34 DATE");

		std::cout << "\n=== Pets Table after attempting modification with negative index===\n";
		handler.handleCommand("print pets");

		std::cout << "\n=== Modify: Invalid index (should fail) ===\n";
		handler.handleCommand("modify pets \"Peppermint\" DATE");

		std::cout << "\n=== Pets Table after attempting modification with invalid index===\n";
		handler.handleCommand("print pets");

		std::cout << "\n=== Modify: wrong argument count (should fail) ===\n";
		handler.handleCommand("modify people 2");
		handler.handleCommand("modify pets 2 INT fourth");

		// Step 8: Delete tests
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

		std::cout << "\n=== Pets Delete: Attempt to delete pet where name contains \"Bel\" " 
			"(expect nothing to be deleted)===\n";
		handler.handleCommand("delete pets 2 Bud");

		std::cout << "\n=== Pets Table after deletion attempt ===\n";
		handler.handleCommand("print pets");

		std::cout << "\n=== Delete: non_existing_table (should fail) ===\n";
		handler.handleCommand("delete non_existing_table 1 \"Harry Truman\"");

		std::cout << "\n=== Delete: Out of bounds index (should fail) ===\n";
		handler.handleCommand("delete people 115 \"THE END\"");

		std::cout << "\n=== People Table after attempting deletion with out of bounds index===\n";
		handler.handleCommand("print pets");

		std::cout << "\n=== Delete: Negative index (should fail) ===\n";
		handler.handleCommand("modify pets -1 1337");

		std::cout << "\n=== Pets Table after attempting deletion with negative index===\n";
		handler.handleCommand("print pets");

		std::cout << "\n=== Delete: Invalid index (should fail) ===\n";
		handler.handleCommand("delete pets \"Oslo, Norway\" \"Bella\"");

		std::cout << "\n=== Pets Table after attempting deletion with invalid index===\n";
		handler.handleCommand("print pets");

		std::cout << "\n=== Delete: wrong argument count (should fail) ===\n";
		handler.handleCommand("delete people 2");
		handler.handleCommand("delete pets 2 \"Buddy\" fourth");

		// Step 9: Insert tests
		std::cout << "\n=== People Insert: New row in people table ===\n";
		handler.handleCommand("insert people 2 8008135 16.08.1994 4.52");

		std::cout << "\n=== People table after insertion===\n";
		handler.handleCommand("print people");

		std::cout << "\n=== Pets Insert: New row in pets table ===\n";
		handler.handleCommand("insert pets 3.01 2 \"Vulpix\"");

		std::cout << "\n=== Pets table after insertion===\n";
		handler.handleCommand("print pets");

		std::cout << "\n=== People Insert: Attemp to insert too long row in people table ===\n";
		handler.handleCommand("insert people 2 404 04.04.2000 6.00 Male");

		std::cout << "\n=== People table after failed insertion===\n";
		handler.handleCommand("print people");

		std::cout << "\n=== Pets Insert: Attemp to insert too short row in pets table ===\n";
		handler.handleCommand("insert pets 4.99 1");

		std::cout << "\n=== Pets table after failed insertion===\n";
		handler.handleCommand("print pets");

		std::cout << "\n=== Insert: non_existing_table (should fail) ===\n";
		handler.handleCommand("insert non_existing_table 5 \"Lyndon B. Johnson\"");

		std::cout << "\n=== People Insert: Attemp to insert entry in people with invalid Birthday ===\n";
		handler.handleCommand("insert people 2 45752 29.02.2013 5.00");

		std::cout << "\n=== People table after failed insertion===\n";
		handler.handleCommand("print people");

		std::cout << "\n=== People Insert: Attemp to insert entry in pets with invalid PetID ===\n";
		handler.handleCommand("insert pets \"Robert Knievel\" 2 \"Evel Knievel\"");

		std::cout << "\n=== People table after failed insertion===\n";
		handler.handleCommand("print people");

		std::cout << "\n=== Insert: No arguments (should fail) ===\n";
		handler.handleCommand("insert pets");

		// Step 10: Addcolumn tests
		std::cout << "\n=== People Addcolumn: New column in people table ===\n";
		handler.handleCommand("addcolumn people Age INT");

		std::cout << "\n=== People table after new column added===\n";
		handler.handleCommand("print people");

		std::cout << "\n=== People Addcolumn: Add value in new column ===\n";
		handler.handleCommand("update people 1 NULL 4 25");

		std::cout << "\n=== People table after value added in new column===\n";
		handler.handleCommand("print people");

		std::cout << "\n=== People Addcolumn: Attempt to add invalid value in new column ===\n";
		handler.handleCommand("update people 3 4.52 4 \"Treaty\"");

		std::cout << "\n=== People table after attempting to add invalid value in new column ===\n";
		handler.handleCommand("print people");

		std::cout << "\n=== Pets Addcolumn: Add Invalid column-type ===\n";
		handler.handleCommand("addcolumn pets Weight NULL");

		std::cout << "\n=== Pets table after attempting to add column of invalid type ===\n";
		handler.handleCommand("print pets");

		std::cout << "\n=== Pets Addcolumn: Add Invalid column-type ===\n";
		handler.handleCommand("addcolumn pets Weight INVALID_TYPENAME");

		std::cout << "\n=== Pets table after attempting to add column of invalid type ===\n";
		handler.handleCommand("print pets");

		std::cout << "\n=== Addcolumn: non_existing_table (should fail) ===\n";
		handler.handleCommand("addcolumn non_existing_table Height FLOAT");

		std::cout << "\n=== Addcolumn: wrong argument count (should fail) ===\n";
		handler.handleCommand("addcolumn people Residency");
		handler.handleCommand("addcolumn pets Color STRING fourth");

		// Step 11: Export tests
		std::cout << "\n=== Export: Save people table to file ===\n";
		handler.handleCommand("export people people_export.txt");

		std::cout << "\n=== Export: non_existing_table (should fail) ===\n";
		handler.handleCommand("export non_existing_table shopping_list.txt");

		std::cout << "\n=== Export: wrong argument count (should fail) ===\n";
		handler.handleCommand("export pets");
		handler.handleCommand("export pets the_archive.txt the_savefile.txt");

		// Step 12: Save tests
		std::cout << "\n=== Save: Save database to file ===\n";
		handler.handleCommand("save");

		std::cout << "\n=== Save: With argument (should fail) ===\n";
		handler.handleCommand("save database_file1.txt");

		// Step 13: SaveAs tests
		std::cout << "\n=== SaveAs: Save database to current working file ===\n";
		handler.handleCommand("saveas database_file.txt");

		std::cout << "\n=== SaveAs: Save database to new file ===\n";
		handler.handleCommand("saveas database_file1.txt");

		std::cout << "\n=== SaveAs: Wrong argument count ===\n";
		handler.handleCommand("saveas");
		handler.handleCommand("saveas database_file1.txt database_file2.txt");

		// Step 14: Close tests
		std::cout << "\n=== Close: Close current database ===\n";
		handler.handleCommand("close");

		std::cout << "\n=== Close: Attempt to execute unavailable-after-close commands ===\n";
		handler.handleCommand("showtables");
		handler.handleCommand("addcolumn people Weight FLOAT");
		handler.handleCommand("delete pets 2 \"Vulpix\"");
		handler.handleCommand("save");

		std::cout << "\n=== Close: With argument (should fail) ===\n";
		handler.handleCommand("close database_file1.txt");

		// Step 15: Open tests
		std::cout << "\n=== Open: Open new file ===\n";
		handler.handleCommand("open big_table.txt");

		std::cout << "\n=== Open: showtables of new db ===\n";
		handler.handleCommand("showtables");

		std::cout << "\n=== Open: print books table ===\n";
		handler.handleCommand("print books");

		std::cout << "\n=== Open: save after opening (to check that working file changed) ===\n";
		handler.handleCommand("save");

		std::cout << "\n=== Open: Open non-existing file (should fail) ===\n";
		handler.handleCommand("open encyclopedia_britannica.txt");

		std::cout << "\n=== Open: showtables after failed open ===\n";
		handler.handleCommand("showtables");

		std::cout << "\n=== Open: Wrong argument count ===\n";
		handler.handleCommand("open");
		handler.handleCommand("open leftwing_parties.txt rightwing_parties.txt");

		// Step 16: Help test
		std::cout << "\n=== Help: with argument ===\n";
		handler.handleCommand("help me");

		// Step 17: Paginated print test
		std::cout << "\n=== Paginated Print: 5 rows per page ===\n";
		handler.handleCommand("print books 5");

		std::cout << "\n=== Paginated Print: 0 rows per page (should call default print) ===\n";
		handler.handleCommand("print books 0");

		std::cout << "\n=== Paginated Print: big RPN (should print entire table) ===\n";
		handler.handleCommand("print books 30");

		std::cout << "\n=== Paginated Print: negative RPN (should fail) ===\n";
		handler.handleCommand("print books -21");

		std::cout << "\n=== Paginated Print: invalid RPN (should fail) ===\n";
		handler.handleCommand("print books \"Dwight D. Eisenhower\"");

		// Step 18: Paginated select tests
		std::cout << "\n=== Paginated Select: Name contains 'a' (case-sensitive) ===\n";
		handler.handleCommand("select 1 a books");

		std::cout << "\n=== Paginated Select: Name contains empty string ===\n";
		handler.handleCommand("select 1 \"\" books");

		// Step 19: Command prompt-and-execute loop
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
	catch (const std::bad_alloc& ex) {
		std::cerr << "Fatal memory error: " << ex.what() << "\n";
		return 1;
	}
	catch (const std::exception& ex) {
		std::cerr << "Fatal error: " << ex.what() << "\n";
		return 1;
	}
	catch (...) {
		std::cerr << "Unknown fatal error occurred.\n";
		return 1;
	}
	
	return 0;
}