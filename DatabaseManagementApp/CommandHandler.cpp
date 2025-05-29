#include "CommandHandler.h"

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
		db.showTables();
	}
	else if (command == "print") {
		if (tokens.size() < 2) {
			std::cerr << "Usage: print <table>\n";
		}
		else {
			db.printTable(tokens[1]);
		}
	}
	else if (command == "insert") {
		if (tokens.size() < 3) {
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
	else {
		std::cerr << "Unknown command: " << command << "\n";
	}
}