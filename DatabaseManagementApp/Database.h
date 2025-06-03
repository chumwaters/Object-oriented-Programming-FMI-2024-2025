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

	/// @brief Prints the contents of a table by name.
	/// 
	/// Format:
	/// - Names of all columns as a header row.
	/// - A seprator line beneath the header.
	/// - One line per row of data, formatted with `CellValue::toString`.
	/// 
	/// If the table is not found, an error message is printed to std::cerr.
	/// 
	/// @param tableName The name of the table to display.
	void printTable(const std::string& tableName) const;

	/// @brief Prints all rows in a table where the specified column matches a given
	/// value.
	/// @param tableName Name of table to select from.
	/// @param columnIndex Index of column in table to match.
	/// @param searchValue String form of the value to match.
	void selectMatchingRows(const std::string& tableName, std::size_t columnIndex,
		const std::string& searchValue) const;

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
