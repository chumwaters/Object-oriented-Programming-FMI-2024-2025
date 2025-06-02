#pragma once

#include "CellValue.h"

#include <vector>

/// @brief Represents a row in a table, containing a sequence of CellValue pointers.
class Row {
private:
	std::vector<CellValue*> cells;

public:
	/// @brief Default constructor for Row class.
	Row() = default;

	/// @brief Constructs a Row with a specific number of NULL cells.
	/// @param columnCount The number of NULL cells to initialize.
	Row(size_t columnCount);

	/// @brief Copy constructor (deep copy)
	Row(const Row& other);

	size_t size() const { return cells.size(); };
	CellValue& operator[](size_t i) { return cells[i]; };
	const CellValue& operator[](size_t i) const { return cells[i]; };
};