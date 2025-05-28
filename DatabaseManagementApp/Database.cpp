#include "Database.h"

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

void Database::showTables() const {
	std::cout << "Tables in database:\n";
	for (const Table& t : tables) {
		std::cout << " - " << t.getName() << "\n";
	}
}

bool Database::insertInto(const std::string& tableName, const std::vector<std::string>& rawValues) {
	Table* table = getTable(tableName);
	if (!table) {
		std::cerr << "Error: Table '" << tableName << "' not found!\n";
		return false;
	}

	const std::vector<Column>& cols = table->getColumns();
	if (rawValues.size() != cols.size()) {
		std::cerr << "Error: Expected " << cols.size() << " values, got " << rawValues.size()
			<< ".\n";
		return false;
	}

	Row row(cols.size());
	for (size_t i = 0; i < cols.size(); ++i) {
		CellValue cell;

		const std::string& val = rawValues[i];
		if (val == "NULL") {
			cell.setNull();
		}
		else {
			switch (cols[i].type) {
				case DataType::INT:
					try {
						cell.setInt(std::stoll(val));
					}
					catch (...) {
						std::cerr << "Invalid INT: " << val << "\n";
						return false;
					}
					break;
				case DataType::FLOAT:
					try {
						cell.setFloat(std::stod(val));
					} 
					catch (...) {
						std::cerr << "Invalid FLOAT: " << val << "\n";
						return false;
					}
					break;
				case DataType::DATE: {
					bool ok = false;

					Date d = Date::fromString(val, ok);
					if (!ok) {
						std::cerr << "Invalid DATE: " << val << "\n";
						return false;
					}

					cell.setDate(d);
					break;
				}
				case DataType::STRING: {
					if (val.size() < 2 || val.front() != '"' || val.back() != '"') {
						std::cerr << "Invalid STRING: " << val << "\n";
						return false;
					}

					std::string parsed;
					// Iterating from after the first quote to before the last quote
					for (size_t j = 1; j + 1 < val.size(); ++j) {
						// If we find a backslash 
						if (val[j] == '\\' && j + 1 < val.size() - 1) {
							char next = val[j + 1];
							// If the next char is a quote or a backslash we append it
							if (next == '\"' || next == '\\') {
								parsed += next;
								++j;
							}
							// Otherwise, we treat the backslash as a literal character
							else {
								parsed += val[j];
							}
						}
						// Characters that are not backslashes are just appended
						else {
							parsed += val[j];
						}
					}
					
					cell.setString(parsed);
					break;
				}
				default:
					cell.setNull();
					break;
			}			
		}

		// Cell is now set to a parsed value and is ready to be inserted
		// into the row.
		row[i] = cell;
	}

	// We exited the for-loop, meaning all cells have been parsed
	// and the complete row is ready for insertion into the table.
	try {
		table->addRow(row);
	} catch (const std::exception& e) {
		std::cerr << "Failed to insert row: " << e.what() << "\n";
		return false;
	}

	return true;
}

void Database::printTable(const std::string& tableName) const {
	const Table* table = getTable(tableName);
	if (!table) {
		std::cerr << "Error: Table '" << tableName << "' not found.\n";
		return;
	}

	const std::vector<Column>& columns = table->getColumns();
	const std::vector<Row>& rows = table->getRows();

	// Here we will store how wide each column is for proper formating.
	std::vector<std::size_t> colWidths(columns.size(), 0);

	// Fill the colWidths vector by determining maximum width for each column.
	for (std::size_t i = 0; i < columns.size(); ++i) {
		
		// Take into account the possibility for the column name to be the maximum.
		std::size_t maxLen = columns[i].name.length();
		for (std::size_t r = 0; r < rows.size(); ++r) {
			std::size_t len = rows[r].cells[i].toString().length();
			if (len > maxLen) maxLen = len;
		}

		colWidths[i] = maxLen;
	}

	// Print header
	for (std::size_t i = 0; i < columns.size(); ++i) {
		std::cout << "| " << columns[i].name << ' ';

		// Add padding based on column size
		std::size_t padding = colWidths[i] > columns[i].name.length() ? colWidths[i] - columns[i].name.length() : 0;
		for (std::size_t p = 0; p < padding; ++p) std::cout << ' ';
		std::cout << ' ';
	}
	std::cout << "|";

	// Print separator
	for (std::size_t i = 0; i < columns.size(); ++i) {
		std::cout << "+-";
		
		for (std::size_t j = 0; j < colWidths[i]; ++j) std::cout << "-";
		std::cout << "-";
	}
	std::cout << "|";

	// Print each row
	for (std::size_t r = 0; r < rows.size(); ++r) {
		for (std::size_t c = 0; c < columns.size(); ++c) {
			std::string valStr = rows[r].cells[c].toString();
			std::cout << "| " << valStr;
			
			std::size_t padding = colWidths[c] > valStr.length() ? colWidths[c] - valStr.length() : 0;
			for (std::size_t p = 0; p < padding; ++p) std::cout << ' ';
			std::cout << ' ';
		}
		std::cout << "|";
	}
}