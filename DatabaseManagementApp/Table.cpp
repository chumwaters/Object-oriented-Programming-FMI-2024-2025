#include "Table.h"

Table::Table(const std::string& tableName) : name(tableName) {}

void Table::addColumn(const std::string& colName, DataType type) {
	columns.push_back(Column(colName, type));
	for (Row& row : rows) {
		row.cells.push_back(CellValue());
	}
}