#pragma once

#include "Table.h"

#include <string>
#include <vector>

class Database {
private:
	std::vector<Table> tables;

public:
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
