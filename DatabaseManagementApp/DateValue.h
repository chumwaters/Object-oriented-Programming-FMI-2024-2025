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
};