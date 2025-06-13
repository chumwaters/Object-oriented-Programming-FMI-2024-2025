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
		else {
			std::cerr << "Unknown or malformed command: " << command << '\n';
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << '\n';
	}
}