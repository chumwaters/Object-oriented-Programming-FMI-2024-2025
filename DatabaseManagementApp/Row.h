#pragma once

#include "CellValue.h"

#include <vector>

struct Row {
	std::vector<CellValue> cells;

	Row() = default;
	Row(size_t columnCount) : cells(columnCount) {};
};