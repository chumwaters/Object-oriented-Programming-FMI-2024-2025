#pragma once

#include "CellValue.h"

/// @brief Represents a string value in a table cell.
class StringValue : public CellValue {
private:
	std::string value;

public:
	/// @brief Constructs a StringValue from a given std::string object.
	/// @param v The string to store.
	StringValue(const std::string& v) : value(v) {}

	/// @return DataType::STRING
	DataType getType() const override { return DataType::STRING; }

	/// @return String representation of the value, quoted and escaped.
	std::string toString() const override;

	/// @return Always false.
	bool isNull() const override { return false; }
 
	/// @return True if both this and other are StringValue and their
	/// values match.
	bool equals(const CellValue* other) const override;
};