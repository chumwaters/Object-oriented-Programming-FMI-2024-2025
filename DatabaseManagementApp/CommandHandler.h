#pragma once

#include "Database.h"

/// @brief Parses and executes user commands on a Database.
class CommandHandler {
private:
	Database& db;

public:
	/// @brief CommandHandler constructor from Database reference.
	/// @param db Database reference to construct CommandHandler object from.
	CommandHandler(Database& db);

	/// @brief Prints a summary of available commands and their usage and function.
	void printHelp() const;

	/// @brief Parses and executes a user command line.
	/// @param line The raw input command string.
	void handleCommand(const std::string& line);
};
