#pragma once

#include "CellValue.h"

/// @brief Represents a NULL (empty) value in a table cell.
class NullValue : public CellValue
{
public:
	/// @brief Constructs a NullValue.
	NullValue() = default;

	/// @return DataType::NULLTYPE
	DataType getType() const override { return DataType::NULLTYPE; }

	/// @return The string "NULL".
	std::string toString() const override { return "NULL"; };

	/// @return Always true.
	bool isNull() const override { return true; };

	/// @return True if other is also null.
	bool equals(const CellValue *other) const override { return other->isNull(); }

	/// @return A new NullValue instance.
	CellValue *clone() const override { return new NullValue(); }

	/// @brief Converts null to null.
	/// @param target Ignored.
	bool convertTo(DataType target, CellValue *&out) const override
	{
		out = new NullValue();
		return true;
	}
};
