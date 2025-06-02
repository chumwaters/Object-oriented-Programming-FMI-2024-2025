#include "Row.h"
#include "NullValue.h"

Row::Row(size_t columnCount) {
	for (size_t i = 0; i < columnCount; ++i) {
		cells.push_back(new NullValue());
	}
}

Row::Row(const Row& other) {
	for (const CellValue* val : other.cells) {
		cells.push_back(val->clone());
	}
}

Row::Row(Row&& other) noexcept : cells(std::move(other.cells)) {
	other.cells.clear();
}

Row& Row::operator=(const Row& other) {
	if (this != &other) {
		for (CellValue* val : cells) delete val;
		
		cells.clear();

		for (const CellValue* val : other.cells) {
			cells.push_back(val->clone());
		}
	}

	return *this;
}

Row& Row::operator=(Row&& other) noexcept {
	if (this != &other) {
		for (CellValue* val : cells) delete val;

		cells = std::move(other.cells);

		other.cells.clear();
	}

	return *this;
}

Row::~Row() {
	for (CellValue* val : cells) delete val;
	cells.clear();
}

CellValue*& Row::operator[](size_t i) {
	if (i >= cells.size()) throw std::out_of_range("Row index is out of bounds");

	return cells[i];
}

const CellValue* Row::operator[](size_t i) const {
	if (i >= cells.size()) throw std::out_of_range("Row index is out of bounds.");

	return cells[i];
}