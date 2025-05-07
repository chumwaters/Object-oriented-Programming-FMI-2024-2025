#pragma once

#include <iostream>
#include <string.h>

/// @brief DataType - tag that describes the concrete cell type
enum class DataType {
	INT,		// 64-bit signed integer
	FLOAT,		// Double
	DATE,		// Calendar date (dd.mm.yyyy, year >= 1900)
	STRING,		// Quited string with C-style escapes
	NULLTYPE	// Explicit NULL (no value)
};

/// @brief - tagged union that holds any supported type + NULL
class CellValue {
private:
	DataType type = DataType::NULLTYPE;
	bool	 null = true;		// explicit NULL flag

	// Single storage of all types (simple, but memory-heavier)
	long long	intVal_ = 0;
	double		floatVal = 0.0;
	Date		dateVal_{};
	std::string strVal_ {};
};