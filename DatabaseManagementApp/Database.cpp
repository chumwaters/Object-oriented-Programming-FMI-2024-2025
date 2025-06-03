#include "Database.h"

#include <exception>

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