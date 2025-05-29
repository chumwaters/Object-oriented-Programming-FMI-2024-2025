#include "CommandHandler.h"

/// @brief Simple token splitter helper method.
/// @param line Line to split up.
/// @return Vector of space-separated words of input line.
static std::vector<std::string> splitCommandLine(const std::string& line) {
	std::vector<std::string> tokens;

	const char* str = line.c_str();
	while (*str) {	// This semantically iterates through words, not characters
		while (*str && std::isspace(*str)) ++str; // Skip whitespaces

		const char* start = str; // Remember first character you find
		while (*str && !std::isspace(*str)) ++str; // Go to the end of the word
		if (start != str)
			tokens.emplace_back(start, str - start); // Construct directly in vector
	}

	return tokens;
}

CommandHandler::CommandHandler(Database& db) : db(db) {}

void CommandHandler::handleCommand(const std::string& line) {
	std::vector<std::string> tokens = splitCommandLine(line);
	if (tokens.empty()) return;

	const std::string& command = tokens[0];

	if (command == "exit") {
		std::cout << "Exiting.\n";
		exit(0);
	}
	else if (command == "showtables") {
		if (tokens.size() != 1) {
			std::cerr << "Showtables command has no arguments!\n";
		}
		else {
			db.showTables();
		}
		
	}
	else if (command == "print") {
		if (tokens.size() != 2) {
			std::cerr << "Usage: print <table>\n";
		}
		else {
			db.printTable(tokens[1]);
		}
	}
	else if (command == "insert") {
		if (tokens.size() != 3) {
			std::cerr << "Usage: insert <table> <val1> <val2> ... \n";
		}
		else {
			const std::string& tableName = tokens[1];
			std::vector<std::string> values(tokens.begin() + 2, tokens.end());
			if (!db.insertInto(tableName, values)) {
				std::cerr << "Insert failed.\n";
			}
		}
	}
	else if (command == "describe") {
		if (tokens.size() != 2) {
			std::cerr << "Usage: describe <table>\n";
		}
		else {
			const Table* table = db.getTable(tokens[1]);
			if (!table) {
				std::cerr << "Table '" << tokens[1] << "' not found.\n";
			}
			else {
				table->describe();
			}
		}
	}
	else {
		std::cerr << "Unknown command: " << command << "\n";
	}
}