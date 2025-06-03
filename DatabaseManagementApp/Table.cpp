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

void Table::modifyColumnType(size_t colIndex, DataType newType) {
	if (colIndex >= columns.size()) {
		throw std::out_of_range("Column index out of bounds in modifyColumnType.");
	}

	int successCount = 0;
	std::vector<size_t> failedRows;

	for (size_t r = 0; r < rows.size(); ++r) {
		CellValue* converted = nullptr;

		if (rows[r][colIndex]->convertTo(newType, converted)) {
			delete rows[r][colIndex];
			rows[r][colIndex] = converted;
			++successCount;
		}
		else {
			delete rows[r][colIndex];
			rows[r][colIndex] = new NullValue();
			failedRows.push_back(r);
		}
	}

	columns[colIndex].type = newType;

	std::cout << "Modified column to " << static_cast<int>(newType) << ".\n";
	std::cout << "Success count: " << successCount << ", Failures: " << failedRows.size() << '\n';

	if (!failedRows.empty()) {
		std::cout << "Failed rows: ";

		for (size_t i = 0; i < failedRows.size(); ++i) {
			std::cout << failedRows[i];
			if (i + 1 < failedRows.size()) std::cout << ", ";
		}
		std::cout << '\n';
	}
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