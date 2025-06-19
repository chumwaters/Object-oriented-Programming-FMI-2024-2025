#include "Table.h"
#include "IntValue.h"
#include "FloatValue.h"
#include "DateValue.h"
#include "StringValue.h"
#include "NullValue.h"
#include "StringUtils.h"
#include "TablePrintUtils.h"

#include <fstream>

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

void Table::selectMatchingRows(std::size_t columnIndex, const std::string& searchValue) const
{
	if (columnIndex >= columns.size()) {
		throw std::out_of_range("Column index out of bounds in selectMatchingRows.");
	}

	std::vector<Row> filtered;
	if (columns[columnIndex].type == DataType::STRING) {
		for (const Row& row : rows) {
			const CellValue* cell = row[columnIndex];
			if (cell->containsSubstring(searchValue))
				filtered.push_back(row);
		}
	}
	else {
		bool ok = false;
		CellValue* query = CellValue::fromString(searchValue, columns[columnIndex].type, ok);

		if (ok) {
			for (const Row& row : rows) {
				const CellValue* cell = row[columnIndex];
				if (cell->equals(query))
					filtered.push_back(row);
			}
		}

		delete query;
	}

	const std::size_t rowsPerPage = 5;
	printRowsFormatted(columns, filtered, rowsPerPage);
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

	std::cout << "Modified column "<< columns[colIndex].name << " to " << 
		DataTypeHelpers::toString(newType) << ".\n";
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

void Table::updateMatchingRows(std::size_t searchCol, const std::string& searchValue,
	std::size_t targetCol, const std::string& targetValue)
{
	if (searchCol >= columns.size() || targetCol >= columns.size())
		throw std::out_of_range("Column index out of range in updateMatchingRows.");

	bool ok = false;

	// Convert target value
	CellValue* newValue = CellValue::fromString(targetValue, columns[targetCol].type, ok);
	if (!ok || newValue == nullptr) 
		throw std::runtime_error("Invalid target value " + targetValue);

	int updateCount = 0;

	for (Row& row : rows) {
		bool match = false;

		if (columns[searchCol].type == DataType::STRING)
			match = row[searchCol]->containsSubstring(searchValue);
		else {
			bool validSearch = false;
			CellValue* query = CellValue::fromString(searchValue, columns[searchCol].type,
				validSearch);

			if (validSearch && row[searchCol]->equals(query))
				match = true;

			delete query;
		}

		if (match) {
			delete row[targetCol];
			row[targetCol] = newValue->clone(); // use a copy
			++updateCount;
		}
	}

	std::cout << "Updated " << updateCount << " row(s).\n";

	delete newValue;
}

void Table::deleteMatchingRows(std::size_t columnIndex, const std::string& matchValue) {
	if (columnIndex >= columns.size()) {
		throw std::out_of_range("Column index out of bounds in deleteMatchingRows.");
	}

	std::vector<Row> remaining;

	for (const Row& row : rows) {
		const CellValue* cell = row[columnIndex];

		if (matchValue == "NULL") {
			if (!cell->isNull()) {
				remaining.push_back(row);
			}
		} 
		else {
			bool validSearch = false;
			bool match = false;
			CellValue* query = CellValue::fromString(matchValue, columns[columnIndex].type,
				validSearch);

			if (validSearch && cell->equals(query))
				match = true;


			delete query;

			if (!match)
				remaining.push_back(row);
		}
	}

	std::size_t deletedCount = rows.size() - remaining.size();
	rows = std::move(remaining);

	std::cout << "Deleted " << deletedCount << " row(s).\n";
}

void Table::insert(const std::vector<std::string>& rawValues) {
	if (rawValues.size() != columns.size()) {
		throw std::runtime_error("Expected " + std::to_string(columns.size()) 
			+ " values, got " + std::to_string(rawValues.size()));
	}

	Row row(columns.size());
	for (size_t i = 0; i < columns.size(); ++i) {
		// Storing for string parsing in STRING case of switch-case
		const std::string& val = rawValues[i]; 

		if (val == "NULL") {
			row[i] = new NullValue();
		}
		else {
			try {
				switch (columns[i].type) {
				case DataType::INT:
					row[i] = new IntValue(std::stoll(val));
					break;
				case DataType::FLOAT:
					row[i] = new FloatValue(std::stod(val));
					break;
				case DataType::DATE: {
					bool ok = false;

					Date d = Date::fromString(val, ok);
					if (!ok) throw std::runtime_error("Invalid date format for value: " + val);

					row[i] = new DateValue(d);
					break;
				}
				case DataType::STRING: {
					row[i] = new StringValue(val);
					break;
				}
				default:
					row[i] = new NullValue();
					break;
				}
			}
			catch (const std::exception& e) {
				row.clear();
				throw std::runtime_error("Failed to insert value '" + val + "' into column '"
					+ columns[i].name + "': " + e.what());
			}
		}
	}

	// We exited the for-loop, meaning all cells have been parsed
	// and the complete row is ready for insertion into the table.
	try {
		addRow(row);
	}
	catch (...) {
		row.clear();
		throw; // rethrowing -- we've cleaned up in time, but any callers
			   // should know something happened so they can inform the user
	}
}

void Table::exportToStream(std::ostream& out) const {
	out << "TABLE " << name << "\n";

	for (const Column& col : columns) {
		out << "COLUMN \"" << col.name << "\" "
			<< DataTypeHelpers::toString(col.type) << "\n";
	}

	for (const Row& row : rows) {
		out << "ROW";
		for (std::size_t i = 0; i < row.size(); ++i) {
			const CellValue* cell = row[i];

			if (cell == nullptr || cell->isNull())
				out << " NULL";
			else
				out << ' ' << cell->toString();
		}

		out << "\n";
	}

	out << "END\n";
}

void Table::exportToFile(const std::string& fileName) const {
	std::ofstream out(fileName);
	if (!out.is_open()) {
		throw std::runtime_error("Failed to open file for writing: " + fileName);
	}

	exportToStream(out);
}

Table Table::importFromStream(std::istream& in) {
	std::string line;

	// Reading TABLE definition
	if (!std::getline(in, line) || line.substr(0, 6) != "TABLE ")
		throw std::runtime_error("Missing TABLE declaration." + line);


	std::string tableName = line.substr(6);
	Table table(tableName);

	bool done = false; // set to true when END is read

	// Reading COLUMN definitions
	while (std::getline(in, line)) {
		if (line == "END") {
			done = true;
			break;
		}

		if (line.substr(0, 7) != "COLUMN " && line.substr(0, 4) != "ROW ")
			throw std::runtime_error("Unexpected line in import: " + line);

		if (line.substr(0, 6) == "COLUMN") {
			std::size_t firstQuote = line.find('\"');
			std::size_t lastQuote = line.find_last_of('\"');

			if (firstQuote == lastQuote)
				throw std::runtime_error("Invalid COLUMN declaration.");

			std::string colName = line.substr(firstQuote + 1, lastQuote - firstQuote - 1);
			std::string typeStr = line.substr(lastQuote + 2);

			DataType type;
			if (!DataTypeHelpers::fromString(typeStr, type))
				throw std::runtime_error("Unknown data type: " + typeStr);

			table.addColumn(colName, type);
		}

		if (line.substr(0, 4) == "ROW ") {
			std::vector<std::string> values = tokenize(line.substr(3));
			table.insert(values);
			break; // Moving to next state "reading ROW"
		}
	}

	// Reading ROW definitions
	while (std::getline(in, line)) {
		if (done) // We'll land here if the table doesnt have inserted rows
			break;

		if (line.substr(0, 3) == "END") {
			done = true;
			break;
		}

		if (line.substr(0, 4) != "ROW ")
			throw std::runtime_error("Unexpected line in import: " + line);

		std::vector<std::string> values = tokenize(line.substr(3));
		table.insert(values);
	}

	if (!done)
		throw std::runtime_error("Missing END statement.");

	return table;
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

void Table::print(std::size_t rowsPerPage) const {
	printRowsFormatted(columns, rows, rowsPerPage);
}