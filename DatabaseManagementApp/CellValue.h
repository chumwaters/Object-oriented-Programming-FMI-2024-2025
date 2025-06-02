#pragma once

#include <iostream>
#include <string>

#include "Date.h"
#include "DataType.h"

/// @brief Abstract base class representing a value in a table cell.
class CellValue {
public:
	/// @return Whether the cell is null
	virtual bool isNull() const = 0;

	/// @return The type of this cell
	virtual DataType getType() const = 0;

	/// @brief Transforms the cell value into string object
	/// @return String object obtained from applied transformation
	virtual std::string toString() const = 0;

	/// @brief Checks if another cell is equal to this one.
	/// @param other Cell to compare with
	/// @return True if values are equal
	virtual bool equals(const CellValue* other) const = 0;

	/// @brief Returns a heap-allocated deep copy of this object.
	virtual CellValue* clone() const = 0;

	/// @brief Looks for substring in value. Only meaningful for
	/// STRING DataType
	/// @param sub Substring to match
	/// @return True if substring is matched, false otherwise and
	/// false if type is not STRING
	virtual bool containsSubstring(const std::string& sub) const { return false; };

	/// @brief Attempts to convert this value to a different type.
	/// @param target Target type 
	/// @param out Will be set to new CellValue if conversion succeeds
	/// @return true on success; false on failure
	virtual bool convertTo(DataType target, CellValue*& out) const = 0;
};