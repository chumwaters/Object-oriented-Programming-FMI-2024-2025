#pragma once

#include "Table.h"

#include <string>
#include <vector>
#include <exception>

class Database {
private:
	std::vector<Table> tables;

public:
	/// @brief Adds a new table to the DB.
	/// @param t Table to be added to the DB.
	void addTable(const Table& t);

	//---------------------------------------
	// Accessors
	//---------------------------------------
	Table* getTable(const std::string& name);
	const Table* getTable(const std::string& name) const;
};
