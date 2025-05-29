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

	// Individual element access
	Column& getColumn(size_t i) { return columns[i]; };
	Row& getRow(size_t i) { return rows[i]; };
	const Row& getRow(size_t i) const { return rows[i]; };

	//------------------------------------------
	// Schema and data operations
	//------------------------------------------
	
	/// @brief Adds an empty column with name @colName and type @type 
	/// to the table.
	void addColumn(const std::string& colName, DataType type);

	/// @brief Adds an empty row to the table.
	void addRow(const Row& r);

	//------------------------------------------
	// Information
	//------------------------------------------

	/// @brief Prints the schema of the table: column names and their data types.
	void describe() const;
};