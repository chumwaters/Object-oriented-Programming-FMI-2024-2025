#include "Database.h"

#include <exception>

/// @brief Prints a collection of Rows with a common column structure to standart output with aligned
/// columns.
/// @param columns The metadata describing each column (names and types).
/// @param rows The rows of data to print. These must match the column structure.
static void printRowsFormatted(const std::vector<Column>& columns, const std::vector<Row>& rows) {
	std::vector<std::size_t> widths(columns.size(), 0);

	// Initializing widths array with collumn names
	for (std::size_t i = 0; i < columns.size(); ++i) {
		widths[i] = columns[i].name.size();
	}

	// Iterating through each element in each row in search
	// for the longest element of each column 
	for (const Row& row : rows) {
		for (std::size_t i = 0; i < row.size(); ++i) {
			std::size_t len = row[i].toString().size();
			if (len > widths[i]) widths[i] = len;
		}
	}

	// Printing header
	for (std::size_t i = 0; i < columns.size(); ++i) {
		std::cout << columns[i].name;

		std::size_t padding = widths[i] > columns[i].name.size() ? widths[i] - columns[i].name.size() : 0;
		for (std::size_t p = 0; p < padding; ++p) std::cout << ' ';
		if (i + 1 < columns.size()) std::cout << " | ";
	}
	std::cout << "\n";

	// Printing appropriate number of dashes for each collumn to form the 
	// line on the second row of the visualization
	for (std::size_t i = 0; i < columns.size(); ++i) {
		for (std::size_t j = 0; j < widths[i]; ++j) std::cout << '-';
		if (i + 1 < columns.size()) std::cout << "-+-";
	}
	std::cout << "\n";

	// Printing rows
	for (std::size_t r = 0; r < rows.size(); ++r) {
		const Row& row = rows[r];

		for (std::size_t i = 0; i < row.size(); ++i) {
			std::string cellStr = row[i].toString();
			std::cout << cellStr;
			std::size_t padding = widths[i] > cellStr.size() ? widths[i] - cellStr.size() : 0;

			for (std::size_t p = 0; p < padding; ++p) std::cout << ' ';
			if (i + 1 < row.size()) std::cout << " | ";
		}
		std::cout << "\n";
	}
}

void Database::addTable(const Table& t) {
	for (const Table& tbl : tables) {
		if (tbl.getName() == t.getName()) {
			throw std::runtime_error("Table with name '" + t.getName()
				+ "' already exists.");
		}
	}

	tables.push_back(t);
}

Table* Database::getTable(const std::string& name) {
	for (Table& t : tables) {
		if (t.getName() == name) return &t;
	}

	return nullptr;
}

const Table* Database::getTable(const std::string& name) const {
	for (const Table& t : tables) {
		if (t.getName() == name) return &t;
	}

	return nullptr;
}

void Database::printTable(const std::string& tableName) const {
	const Table* table = getTable(tableName);
	if (!table) {
		std::cerr << "Error: Table '" << tableName << "' not found.\n";
		return;
	}

	printRowsFormatted(table->getColumns(), table->getRows());
}

void Database::selectMatchingRows(const std::string& tableName, std::size_t columnIndex,
	const std::string& searchValue) const 
{
	const Table* table = getTable(tableName);
	if (!table) {
		std::cerr << "Table '" << tableName << "' not found.\n";
		return;
	}

	const std::vector<Column>& cols = table->getColumns();
	if (columnIndex >= cols.size()) {
		std::cerr << "Invalid column index.";
		return;
	}

	CellValue ref;
	DataType type = cols[columnIndex].type;
	bool valid = true;

	switch (type) {
		case DataType::INT: {
			char* endptr = nullptr;
			long long val = std::strtoll(searchValue.c_str(), &endptr, 10);
			if (*endptr != '\0') valid = false;
			else ref.setInt(val);
			break;
		}
		case DataType::FLOAT: {
			char* endptr = nullptr;
			double val = std::strtod(searchValue.c_str(), &endptr);
			if (*endptr != '\0') valid = false;
			else ref.setFloat(val);
			break;
		}
		case DataType::DATE: {
			bool ok = false;
			Date d = Date::fromString(searchValue, ok);
			if (!ok) valid = false;
			else ref.setDate(d);
			break;
		}
		case DataType::STRING:
			ref.setString(searchValue);
			break;
		default:
			valid = false;
			break;
	}

	if (!valid) {
		std::cerr << "Could not parse value '" << searchValue << "' to match type of given column.\n";
		return;
	}

	std::vector<Row> filtered;
	const std::vector<Row>& rows = table->getRows();
	for (const Row& row : rows) {
		const CellValue& cell = row[columnIndex];
		bool match = false;

		if (type == DataType::STRING) {
			match = cell.containsSubstring(searchValue);
		}
		else {
			match = cell == ref;
		}
		if (match) filtered.push_back(row);
	}

	printRowsFormatted(cols, filtered);
}

void Database::showTables() const {
	std::cout << "Tables in database:\n";
	for (const Table& t : tables) {
		std::cout << " - " << t.getName() << "\n";
	}
}