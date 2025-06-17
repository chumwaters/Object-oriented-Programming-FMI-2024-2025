#pragma once

#include "CellValue.h"

/// @brief Represents a string value in a table cell.
class StringValue : public CellValue
{
private:
	std::string value;

public:
	/// @brief Constructs a StringValue from a given std::string object.
	/// @param v The string to store.
	StringValue(const std::string &v) : value(v) {}

	/// @return DataType::STRING
	DataType getType() const override { return DataType::STRING; }

	/// @return String representation of the value, quoted and escaped.
	std::string toString() const override;

	/// @return a printable, non-escaped version of the string for display
	std::string toHumanString() const override { return value; }

	/// @return Always false.
	bool isNull() const override { return false; } // TODO??

	/// @return True if both this and other are StringValue and their
	/// values match.
	bool equals(const CellValue *other) const override;

	/// @return A new StringValue with the same content.
	CellValue *clone() const override { return new StringValue(value); } // TODO??

	bool containsSubstring(const std::string &s) const override;

	/// @brief Attempts to convert this value to IntValue, FloatValue or StringValue
	bool convertTo(DataType target, CellValue *&out) const override;
};