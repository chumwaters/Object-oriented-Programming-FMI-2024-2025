#include "Table.h"
#include "NullValue.h"

Table::Table(const std::string& tableName) : name(tableName) {}

void Table::addColumn(const std::string& colName, DataType type) {
	columns.push_back(Column(colName, type));
	for (Row& row : rows) {
		row.addCell(new NullValue());
	}
}

void Table::addRow(const Row& r) {
	if (r.size() != columns.size())
		throw std::runtime_error("Row size does not match table schema.");

	rows.push_back(r);
}

std::vector<Row> Table::selectSubstringMatches(size_t colIndex, const std::string & value) const {
	std::vector<Row> result;

	if (colIndex >= columns.size()) {
		throw std::out_of_range("Column index out of bounds in selectSubstringMatches.");
	}

	for (const Row& row : rows) {
		const CellValue* cell = row[colIndex];
		
		if (columns[colIndex].type == DataType::STRING && cell &&
			cell->containsSubstring(value)) 
		{
			result.push_back(row);
		}
	}

	return result;
}

void Table::describe() const {
	std::cout << "Table '" << name << "' structure:\n";

	for (std::size_t i = 0; i < columns.size(); ++i) {
		std::cout << "Column " << i << ": " << columns[i].name << " (";

		switch (columns[i].type) {
			case DataType::INT: std::cout << "INT"; break;
			case DataType::FLOAT: std::cout << "FLOAT"; break;
			case DataType::DATE: std::cout << "DATE"; break;
			case DataType::STRING: std::cout << "STRING"; break;
			case DataType::NULLTYPE: std::cout << "NULL"; break;
		}

		std::cout << ")\n";
	}
}