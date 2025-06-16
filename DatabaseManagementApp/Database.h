#pragma once

#include "Table.h"

#include <string>
#include <vector>

class Database {
private:
	std::vector<Table> tables;
	std::string filePath;

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

	/// @brief Loads a Database from associated file. Reconstruction logic for each table
	/// is found in Table::importFromStream(). Used in Database(const std::string&) c-tor.
	/// @throws std::runtime_error if the file cannot be opened or parsing fails.
	void load();

	/// @brief Savees the current database to its associated file.
	/// This overwrites the file with the latest table data.
	/// @throws std::runtime_error if writing fails or file cannot be opened.
	void save() const;

	/// @brief Saves the database to the given file path and updates the 
	/// working file path.
	/// @param newFilePath The file path to save the database to.
	/// @throws std::runtime_error if the file cannot be opened for writing. 
	void saveAs(const std::string& newFilePath);

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
