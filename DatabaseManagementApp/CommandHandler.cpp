#include "CommandHandler.h"
#include "StringUtils.h"

CommandHandler::CommandHandler(Database& db) : db(db) {}

void CommandHandler::printHelp() const {
	std::cout << "Available commands:\n\n";

	std::cout << "  showtables\n"
		<< "    - Lists the names of all tables in the database.\n\n";

	std::cout << "  print <table>\n"
		<< "    - Displays the contents of the specified table.\n\n";

	std::cout << "  describe <table>\n"
		<< "    - Shows column names and types of the specified table.\n\n";

	std::cout << "  export <table> <file>\n"
		<< "    - Exports a single table to a specified file.\n\n";

	std::cout << "  addcolumn <table> <\"column\"> <type>\n"
		<< "    - Adds a new column with the given name and type to the table.\n\n";

	std::cout << "  insert <table> <value1> <value2> ...\n"
		<< "    - Inserts a new row into the table with the specified values.\n\n";

	std::cout << "  select <columnIndex> <value> <table>\n"
		<< "    - Prints rows in the table where the given column matches the value.\n\n";

	std::cout << "  update <table> <searchCol> <searchVal> <targetCol> <newVal>\n"
		<< "    - Updates values in a column where a condition is matched.\n\n";

	std::cout << "  modify <table> <columnIndex> <newType>\n"
		<< "    - Converts the data type of a column, if conversion is possible.\n\n";

	std::cout << "  delete <table> <columnIndex> <value>\n"
		<< "    - Deletes rows where the column matches the given value.\n\n";

	std::cout << "  save\n"
		<< "    - Saves the entire database to its associated file.\n\n";

	std::cout << "  saveas <file>\n"
		<< "    - Saves the database to a new file and updates the working file.\n\n";

	std::cout << "  close\n"
		<< "    - Closes the currently loaded database and clears all tables.\n\n";

	std::cout << "  help\n"
		<< "    - Displays this help message.\n\n";

	std::cout << "  exit\n"
		<< "    - Exits the program.\n\n";
}

void CommandHandler::handleCommand(const std::string& line) {
	std::vector<std::string> tokens = tokenize(line);
	if (tokens.empty()) return;

	const std::string& command = tokens[0];

	try {
		if (command == "showtables" && tokens.size() == 1) {
			db.showTables();
		}
		else if (command == "print" && 
			(tokens.size() == 2 || tokens.size() == 3)) 
		{
			Table* table = db.getTable(tokens[1]);
			if (!table) throw std::runtime_error("Table not found: " + tokens[1]);

			std::size_t rpn = 0;
			if (tokens.size() == 3) {
				const char* rpnStr = tokens[2].c_str();
				char* endptr = nullptr;
				long parsed = std::strtol(rpnStr, &endptr, 10);
				if (*endptr != '\0' || parsed < 0)
					throw std::runtime_error("Invalid number for rows per page: " + tokens[2]);
				rpn = static_cast<std::size_t>(parsed);
			}

			table->print(rpn);
		}
		else if (command == "describe" && tokens.size() == 2) {
			Table* table = db.getTable(tokens[1]);
			if (!table) throw std::runtime_error("Table not found: " + tokens[1]);

			table->describe();
		}
		else if (command == "export" && tokens.size() == 3) {
			Table* table = db.getTable(tokens[1]);
			if (!table) throw std::runtime_error("Table not found: " + tokens[1]);

			table->exportToFile(tokens[2]);
		}
		else if (command == "addcolumn" && tokens.size() == 4) {
			Table* table = db.getTable(tokens[1]);
			if (!table) throw std::runtime_error("Table not found: " + tokens[1]);

			DataType type;
			if (!DataTypeHelpers::fromString(tokens[3], type)) {
				throw std::runtime_error("Invalid data type: " + tokens[3]);
			}

			table->addColumn(tokens[2], type);
		}
		else if (command == "insert" && tokens.size() >= 3) {
			Table* table = db.getTable(tokens[1]);
			if (!table) throw std::runtime_error("Table not found: " + tokens[1]);
			
			std::vector<std::string> values(tokens.begin() + 2, tokens.end());
			table->insert(values);
		}
		else if (command == "select" && tokens.size() == 4) {
			const char* idxStr = tokens[1].c_str();
			char* endptr = nullptr;
			long parsedIndex = std::strtol(idxStr, &endptr, 10);
			if (*endptr != '\0' || parsedIndex < 0)
				throw std::runtime_error("Invalid column index: " + tokens[1]);
			std::size_t colIndex = static_cast<std::size_t>(parsedIndex);

			const std::string& value = tokens[2];
			
			Table* table = db.getTable(tokens[3]);
			if (!table) throw std::runtime_error("Table not found: " + tokens[3]);

			table->selectMatchingRows(colIndex, value);
		}
		else if (command == "modify" && tokens.size() == 4) {
			const char* idxStr = tokens[2].c_str();
			char* endptr = nullptr;
			long parsedIndex = std::strtol(idxStr, &endptr, 10);
			if (*endptr != '\0' || parsedIndex < 0)
				throw std::runtime_error("Invalid column index: " + tokens[1]);
			std::size_t colIndex = static_cast<std::size_t>(parsedIndex);

			Table* table = db.getTable(tokens[1]);
			if (!table) throw std::runtime_error("Table not found: " + tokens[1]);

			DataType newType;
			if (!DataTypeHelpers::fromString(tokens[3], newType)) 
				throw std::runtime_error("Invalid data type: " + tokens[3]);

			table->modifyColumnType(static_cast<std::size_t>(colIndex), newType);
		}
		else if (command == "update" && tokens.size() == 6) {
			const char* srchIdxStr = tokens[2].c_str();
			const char* trgtIdxStr = tokens[4].c_str();
			char* endptr1 = nullptr;
			char* endptr2 = nullptr;
			long parsedSrchIndex = std::strtol(srchIdxStr, &endptr1, 10);
			long parsedTrgtIndex = std::strtol(trgtIdxStr, &endptr2, 10);
			if (*endptr1 != '\0' || parsedSrchIndex < 0)
				throw std::runtime_error("Invalid search index: " + tokens[2]);

			if (*endptr2 != '\0' || parsedTrgtIndex < 0)
				throw std::runtime_error("Invalid target index: " + tokens[4]);

			Table* table = db.getTable(tokens[1]);
			if (!table) throw std::runtime_error("Table not found: " + tokens[1]);

			table->updateMatchingRows(static_cast<std::size_t>(parsedSrchIndex), tokens[3], 
				static_cast<std::size_t>(parsedTrgtIndex), tokens[5]);
		}
		else if (command == "delete" && tokens.size() == 4) {
			const char* idxStr = tokens[2].c_str();
			char* endptr = nullptr;
			long parsedIndex = std::strtol(idxStr, &endptr, 10);
			if (*endptr != '\0' || parsedIndex < 0)
				throw std::runtime_error("Invalid column index: " + tokens[2]);

			Table* table = db.getTable(tokens[1]);
			if (!table) throw std::runtime_error("Table not found: " + tokens[1]);

			table->deleteMatchingRows(static_cast<std::size_t>(parsedIndex), tokens[3]);
		}
		else if (command == "open" && tokens.size() == 2) {
			db.load(tokens[1]);
		}
		else if (command == "close" && tokens.size() == 1) {
			db.close();
		}
		else if (command == "save" && tokens.size() == 1) {
			db.save();
		}
		else if (command == "saveas" && tokens.size() == 2) {
			db.saveAs(tokens[1]);
		}
		else if (command == "help" && tokens.size() == 1) {
			printHelp();
		}
		else {
			std::cerr << "Unknown or malformed command: " << command << '\n';
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << '\n';
	}
}