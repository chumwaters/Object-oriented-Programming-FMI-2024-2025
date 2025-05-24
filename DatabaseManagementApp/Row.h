#pragma once

#include "CellValue.h"

#include <vector>

struct Row {
	std::vector<CellValue> cells;

	Row() = default;
	Row(size_t columnCount) : cells(columnCount) {};

	size_t size() const { return cells.size(); };
	CellValue& operator[](size_t i) { return cells[i]; };
};