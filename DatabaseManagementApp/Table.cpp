#include "Table.h"

Table::Table(const std::string& tableName) : name(tableName) {}

void Table::addColumn(const std::string& colName, DataType type) {
	columns.push_back(Column(colName, type));
	for (Row& row : rows) {
		row.cells.push_back(CellValue());
	}
}

void Table::addRow(const Row& r) {
	if (r.size() != columns.size())
		throw std::runtime_error("Row size does not match table schema.");

	rows.push_back(r);
}