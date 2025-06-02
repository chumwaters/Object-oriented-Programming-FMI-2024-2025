#pragma once

#include "CellValue.h"

/// @brief Represents a floating-point value in a table cell.
class FloatValue : public CellValue {
private:
	double value;

public:
	/// @brief Constructs a FloatValue from a given double value.
	/// @param v The value to store.
	FloatValue(double v) : value(v) {}

	/// @return DataType::FLOAT
	DataType getType() const override { return DataType::FLOAT; }
};
