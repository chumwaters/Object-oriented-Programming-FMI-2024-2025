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
	
	// For Table metadata
	const std::string& getName() const { return name; };
	size_t columnCount() const { return columns.size(); };
	size_t rowCount() const { return rows.size(); };

	// For full column and row collections 
	const std::vector<Column>& getColumns() const { return columns; };
	const std::vector<Row>& getRows() const { return rows; };

	//------------------------------------------
	// Schema and data operations
	//------------------------------------------
	void addColumn(const std::string& colName, DataType type);
	void addRow(const Row& r);
};