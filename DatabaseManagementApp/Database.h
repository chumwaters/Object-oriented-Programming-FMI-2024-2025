#pragma once

#include "Table.h"

#include <string>
#include <vector>

class Database {
private:
	std::vector<Table> tables;
	std::string filePath;

	/// @brief Loads a Database from a file. Reconstruction logic for each table
	/// is found in Table::importFromStream().
	/// @param fileName The path to the file containing the database representation.
	/// @throws std::runtime_error if the file cannot be opened or parsing fails.
	void load();
public:
	//--------------------------------------
	// Constructors
	//--------------------------------------
	/// @brief Loads and binds database to the given file path.
	/// @param file The path to the database file to load.
	/// @throws std std::runtime_error If the file cannot be opened 
	/// or if parsing fails.
	Database(const std::string& file);

	//--------------------------------------
	// Operations
	//--------------------------------------

	/// @brief Adds a new table to the DB.
	/// @param t Table to be added to the DB.
	void addTable(const Table& t);

	//---------------------------------------
	// Accessors
	//---------------------------------------
	
	/// @brief Returns pointer to a table by name,
	/// or nullptr if not found.
	Table* getTable(const std::string& name);

	/// @brief Returns const pointer to a table by name,
	/// or nullptr if not found.
	const Table* getTable(const std::string& name) const;

	// --------------------------------------
	//	Information
	// --------------------------------------

	/// @brief Prints names of all tables in DB.
	void showTables() const;
};
