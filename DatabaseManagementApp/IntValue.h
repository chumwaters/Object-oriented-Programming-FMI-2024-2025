#pragma once

#include "CellValue.h"

/// @brief Represents an integer value in a table cell.
class IntValue : public CellValue {
private:
	long long value;

public:
	/// @brief Constructs an IntValue from a given long long value.
	/// @param v The value to store.
	IntValue(long long v) : value(v) {}

	/// @return DataType::INT
	DataType getType() const override { return DataType::INT; }

	/// @return String representation of the integer.
	std::string toString() const override { return std::to_string(value); }

	/// @return Always false.
	bool isNull() const override { return false; }
	
	/// @return True if both this and other are IntValues with the same value.
	bool equals(const CellValue* other) const override;

	/// @return A new IntValue with the same content.
	CellValue* clone() const override { return new IntValue(value); }

	/// @brief Attempts to convert IntValue to IntValue, FloatValue or 
	/// StringValue.
	bool convertTo(DataType target, CellValue*& out) const override;
};