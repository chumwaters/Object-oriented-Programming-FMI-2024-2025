#pragma once

#include <iostream>
#include <string>

#include "Date.h"
#include "DataType.h"

/// @brief - tagged union that holds any supported type + NULL
class CellValue {
private:
	DataType type = DataType::NULLTYPE;
	bool	 null = true;		// explicit NULL flag

	// Single storage of all types (simple, but memory-heavier)
	long long	intVal = 0;
	double		floatVal = 0.0;
	Date		dateVal{};
	std::string strVal {};

	/// @brief Returns raw value as string WITHOUT surrounding quotes. 
	/// Used internally.
	std::string toStringRaw() const;
public:
	//-------------------------------------------------
	// Constructors
	//-------------------------------------------------
	CellValue() = default;		// null by default
	CellValue(long long v) { setInt(v); }
	CellValue(double v) { setFloat(v); }
	CellValue(const Date& v) { setDate(v); }
	CellValue(const std::string& v) { setString(v); }
	CellValue(std::string&& v) { setString(std::move(v)); }

	//-------------------------------------------------
	// Setters - set value AND type, clear NULL flag
	//-------------------------------------------------
	void setInt(long long v);
	void setFloat(double v);
	void setDate(const Date& v);
	void setString(const std::string& v);
	void setString(std::string&& v);

	//-------------------------------------------------
	// NULL handling
	//-------------------------------------------------
	void setNull();
	bool isNull() const { return null; }

	//-----------------------------------------------------
	// Accessors - only call if type matches and !isNull()
	//-----------------------------------------------------
	long long          asInt()   const { return intVal; }
	double			   asFloat() const { return floatVal; }
	Date			   asDate()  const { return dateVal; }
	const std::string& asString() const { return strVal; }

	//-------------------------------------------------
	// Type query
	//-------------------------------------------------
	DataType getType() const { return type; }

	/// @brief Transforms the cell value into string object
	/// @return String object obtained from applied transformation
	std::string toString() const;

	/// @brief Looks for substring in value. Only meaningful for
	/// STRING DataType
	/// @param sub Substring to match
	/// @return True if substring is matched, false otherwise and
	/// false if type is not STRING
	bool containsSubstring(const std::string& sub) const;

	//---------------------------------------------------------
	// Equality – NULLs equal only to NULLs. Types must match.
	//---------------------------------------------------------
	bool operator==(const CellValue& rhs) const;
	bool operator!=(const CellValue& rhs) const { return !(*this == rhs); }

	//---------------------------------------------------------------------
	// convertTo – attempts in‑place type conversion; NULL on failure
	//---------------------------------------------------------------------
	bool convertTo(DataType newType);
};