#pragma once

#include "CellValue.h"

/// @brief Represents a NULL (empty) value in a table cell.
class NullValue : public CellValue {
public:
	/// @brief Constructs a NullValue.
	NullValue() = default;

	/// @return DataType::NULLTYPE
	DataType getType() const override { return DataType::NULLTYPE; }

	/// @return The string "NULL".
	std::string toString() const override {	return "NULL"; };

	/// @return Always true.
	bool isNull() const override { return true; };

	/// @return True if other is also null.
	bool equals(const CellValue* other) const override { return other->isNull(); }
};
