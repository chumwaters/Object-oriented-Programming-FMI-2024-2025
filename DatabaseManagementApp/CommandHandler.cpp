#include "CommandHandler.h"
#include "StringUtils.h"

CommandHandler::CommandHandler(Database& db) : db(db) {}

void CommandHandler::handleCommand(const std::string& line) {
	std::vector<std::string> tokens = splitCommandLine(line);
	if (tokens.empty()) return;

	const std::string& command = tokens[0];

	try {
		if (command == "showtables") {
			db.showTables();
		}
		else if (command == "print" && tokens.size() == 2) {
			Table* table = db.getTable(tokens[1]);
			if (!table) throw std::runtime_error("Table not found: " + tokens[1]);

			table->print();
		}
		else if (command == "describe" && tokens.size() == 2) {
			Table* table = db.getTable(tokens[1]);
			if (!table) throw std::runtime_error("Table not found: " + tokens[1]);

			table->describe();
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
			const char* idxStr = tokens[1].c_str();
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
		else {
			std::cerr << "Unknown or malformed command: " << command << " " << tokens.size() << '\n';
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << '\n';
	}
}