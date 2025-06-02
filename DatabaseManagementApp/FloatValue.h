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

	/// @return String representation of the float value.
	std::string toString() const override { return std::to_string(value); }

	/// @return Always false.
	bool isNull() const override { return false; }

	/// @return True if both this and other are FloatValues and are values 
	/// within some epsilon tolerance (set in the definition) of eachother.
	bool equals(const CellValue* other) const override;
};
