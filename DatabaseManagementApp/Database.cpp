#include "Database.h"

#include <fstream>
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

void Database::loadFromFile(const std::string& fileName) {
	std::ifstream in(fileName);
	if (!in.is_open())
		throw std::runtime_error("Failed to open file for import: " + fileName);

	while (in) {
		// Skip empty lines or whitespace-only lines
		std::string peekLine;
		std::getline(in, peekLine);

		if (peekLine.empty()) continue;

		// Rewind to just before the line
		in.seekg(-static_cast<int>(peekLine.length()) - 2, std::ios_base::cur);

		Table table = Table::importFromStream(in);
		addTable(table);
	}
}

void Database::showTables() const {
	std::cout << "Tables in database:\n";
	for (const Table& t : tables) {
		std::cout << " - " << t.getName() << "\n";
	}
}