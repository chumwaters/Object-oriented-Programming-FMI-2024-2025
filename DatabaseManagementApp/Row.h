#pragma once

#include "CellValue.h"

#include <vector>

/// @brief Represents a row in a table, containing a sequence of CellValue pointers.
class Row {
private:
	std::vector<CellValue*> cells;

public:
	Row() = default;
	Row(size_t columnCount) : cells(columnCount) {};

	size_t size() const { return cells.size(); };
	CellValue& operator[](size_t i) { return cells[i]; };
	const CellValue& operator[](size_t i) const { return cells[i]; };
};