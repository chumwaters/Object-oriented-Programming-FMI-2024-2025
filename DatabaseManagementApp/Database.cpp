#include "Database.h"

#include <fstream>
#include <exception>

Database::Database(const std::string& file) {
	load(file);
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
	if (!isOpen)
		throw std::runtime_error("Operation failed. Database is not opened.");

	for (Table& t : tables) {
		if (t.getName() == name) return &t;
	}

	return nullptr;
}

const Table* Database::getTable(const std::string& name) const {
	if (!isOpen)
		throw std::runtime_error("Operation failed. Database is not opened.");

	for (const Table& t : tables) {
		if (t.getName() == name) return &t;
	}

	return nullptr;
}

void Database::load(const std::string& file) {
	std::ifstream in(file);
	if (!in.is_open())
		throw std::runtime_error("Failed to open file for import: " + filePath);

	tables.clear();
	filePath.clear();
	filePath = file;
	isOpen = true;

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

	in.close();
}

void Database::close() {
	if (!isOpen)
		throw std::runtime_error("Operation failed. Database is not opened.");

	tables.clear();
	filePath.clear();
	isOpen = false;
	std::cout << "Database closed successfuly.\n";
}

void Database::save() const {
	if (!isOpen)
		throw std::runtime_error("Operation failed. Database is not opened.");

	std::ofstream out(filePath);
	if (!out) {
		throw std::runtime_error("Failed to open file for saving: " + filePath);
	}

	for (const Table& table : tables) {
		table.exportToStream(out);
		out << "\n";
	}

	out.close();
}

void Database::saveAs(const std::string& newFilePath) {
	if (!isOpen)
		throw std::runtime_error("Operation failed. Database is not opened.");

	std::ofstream out(newFilePath);
	if (!out)
		throw std::runtime_error("Failed to open file for writing: " + newFilePath);

	for (const Table& table : tables) {
		table.exportToStream(out);
		out << '\n';
	}

	out.close();
	filePath = newFilePath;
}

void Database::showTables() const {
	if (!isOpen)
		throw std::runtime_error("Operation failed. Database is not opened.");

	std::cout << "Tables in database:\n";
	for (const Table& t : tables) {
		std::cout << " - " << t.getName() << "\n";
	}
}