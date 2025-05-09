#pragma once

#include <iostream>
#include <string>

/// @brief DataType - tag that describes the concrete cell type
enum class DataType {
	INT,		// 64-bit signed integer
	FLOAT,		// Double
	DATE,		// Calendar date (dd.mm.yyyy, year >= 1900)
	STRING,		// Quoted string with C-style escapes
	NULLTYPE	// Explicit NULL (no value)
};

/// @brief - tagged union that holds any supported type + NULL
class CellValue {
private:
	DataType type_ = DataType::NULLTYPE;
	bool	 null_ = true;		// explicit NULL flag

	// Single storage of all types (simple, but memory-heavier)
	long long	intVal_ = 0;
	double		floatVal_ = 0.0;
	Date		dateVal_{};
	std::string strVal_ {};

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
	bool isNull() const { return null_; }

	//-----------------------------------------------------
	// Accessors - only call if type matches and !isNull()
	//-----------------------------------------------------
	long long          asInt()   const { return intVal_; }
	double			   asFloat() const { return floatVal_; }
	Date			   asDate()  const { return dateVal_; }
	const std::string& asString() const { return strVal_; }

	//-------------------------------------------------
	// Type query
	//-------------------------------------------------
	DataType getType() const { return type_; }

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
};