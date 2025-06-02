#pragma once

#include "CellValue.h"
#include "Date.h"

/// @brief Represents a calendar date value in a table cell.
class DateValue : public CellValue {
private:
	Date value;

public:
	/// @brief Constructs a DateValue from a given Date object.
	/// @param d The Date object to store.
	DateValue(const Date& d) : value(d) {}

	/// @return DataType::DATE
	DataType getType() const override { return DataType::DATE; }

	/// @return String representation of the date (DD.MM.YYYY).
	std::string toString() const override { return value.toString(); }

	/// @return Always false.
	bool isNull() const override { return false; }

	/// @return True if both are DateValues and represent the same date.
	bool equals(const CellValue* other) const override;
};