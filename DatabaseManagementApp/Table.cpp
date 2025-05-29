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

void Table::describe() const {
	for (std::size_t i = 0; i < columns.size(); ++i) {
		std::cout << columns[i].name << ":";

		switch (columns[i].type) {
			case DataType::INT: std::cout << "INT"; break;
			case DataType::FLOAT: std::cout << "FLOAT"; break;
			case DataType::DATE: std::cout << "DATE"; break;
			case DataType::STRING: std::cout << "STRING"; break;
			case DataType::NULLTYPE: std::cout << "NULL"; break;
		}

		std::cout << "\n";
	}
}