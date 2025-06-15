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
	
	/// @brief Adds an empty column with name <colName> and type <type> 
	/// to the table.
	void addColumn(const std::string& colName, DataType type);

	/// @brief Adds an empty row to the table.
	void addRow(const Row& r);

	/// @brief Prints all rows in the table where the specified column matches a given
	/// value.
	/// @param columnIndex Index of column in table to match.
	/// @param searchValue String form of the value to match.
	void selectMatchingRows(std::size_t columnIndex, const std::string& searchValue) const;

	/// @brief Modifies the type of a column, attempting conversion.
	/// Outputs information reagarding success and failure count on 
	/// conversions, as well as row-indexes of failures.
	/// @param colIndex Index of the column to change.
	/// @param newType New data type to convert to.
	void modifyColumnType(size_t colIndex, DataType newType);
	
	/// @brief Updates all rows where one column matches a given value,
	/// replacing another column's value.
	/// @param searchCol The index of the column to search for matches.
	/// @param searchValue The value to look for.
	/// @param targetCol The index of the column to update.
	/// @param targetValue The value to assign.
	/// @throws std::runtime_error on bad input or failed conversion.
	void updateMatchingRows(std::size_t searchCol, const std::string& searchValue,
		std::size_t targetCol, const std::string& targetValue);

	/// @brief Deletes all rows where the value in the specified column matches 
	/// the given value. 
	/// 
	/// The comparison is exact:
	///		- Strings must match fully (no substring check).
	///		- All other types are compared using their equals() implementations.
	///		- The special value "NULL" matches cells that are null.
	/// 
	/// @param columnIndex Index of the column to search.
	/// @param matchValue Value to match against.
	/// 
	/// @throws std::out_of_range if columnIndex is invalid.
	void deleteMatchingRows(std::size_t columnIndex, const std::string& matchValue);

	/// @brief Inserts a new row into the table using raw
	/// string values.
	/// @param rawValues A vector of strings representing the values to
	/// insert.
	/// @return True if the row was successfully inserted, false otherwise.
	void insert(const std::vector<std::string>& rawValues);

	//------------------------------------------
	// Stream import/export
	//------------------------------------------
	
	/// @brief Exports the structure and contents of the table to the given
	/// output stream in a format designed to be human readable and suitable 
	/// for later parsing.
	/// 
	/// Example output:
	/// @code
	/// TABLE people
	/// COLUMN "ID" INT
	/// COLUMN "Name" STRING
	///	COLUMN "Birthday" DATE
	///	COLUMN "GPA" FLOAT
	/// ROW 1 "Alice" 01.01.2000 3.75
	/// ROW 2 "Bob" 15.06.1999 NULL
	/// END
	///	@endcode
	void exportToStream(std::ostream& out) const;

	/// @brief Exports the contents of the table to a specified text file in
	/// the format of exportToStream().
	/// @param fileName The name of the file to write to.
	/// @throws std::runtime_error if the file cannot be opened.
	void exportToFile(const std::string& fileName) const;

	/// @brief Imports a Table from the given imput stream.
	///
	/// The input is expected to be in the format defined in the exportToStream()
	/// method. Any deviation will throw.
	/// 
	/// @param in the input stream to read the table definition and data from.
	/// @throws std::runtime_error If the input format is invalid or incomplete.
	static Table importFromStream(std::istream& in);

	//------------------------------------------
	// Information
	//------------------------------------------

	/// @brief Prints the schema of the table: column names and their data types.
	void describe() const;

	/// @brief Prints the contents of the table.
	/// 
	/// Format:
	/// - Names of all columns as a header row.
	/// - A separator line beneath the header.
	/// - One line per row of data, formatted with `CellValue::toString`.
	void print() const;
};