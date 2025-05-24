#pragma once

#include "Column.h"
#include "Row.h"

#include <string>
#include <vector>
#include <exception>

/// @brief Holds rows and columns, supports adding rows and modifying schema
class Table {
private:
	std::string name;
	std::vector<Column> columns;
	std::vector<Row> rows;

public:
	/// @brief Constructs a table with a given name.
	/// @param Name to give to constructed Table.
	Table(const std::string& tableName);

	//---------------------------------------
	// Accessors
	//---------------------------------------
	const std::string& getName() const { return name; };
	size_t columnCount() const { return columns.size(); };
	size_t rowCount() const { return rows.size(); };
};