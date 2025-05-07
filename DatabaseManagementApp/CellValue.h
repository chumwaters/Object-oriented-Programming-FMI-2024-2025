#pragma once

#include <iostream>
#include <string.h>

/// @brief DataType - tag that describes the concrete cell type
enum class DataType {
	INT,		// 64-bit signed integer
	FLOAT,		// Double
	DATE,		// Calendar date (dd.mm.yyyy, year >= 1900)
	STRING,		// Quited string with C-style escapes
	NULLTYPE	// Explicit NULL (no value)
};

/// @brief - tagged union that holds any supported type + NULL
class CellValue {
private:
	DataType type = DataType::NULLTYPE;
	bool	 null = true;		// explicit NULL flag

	// Single storage of all types (simple, but memory-heavier)
	long long	intVal_ = 0;
	double		floatVal = 0.0;
	Date		dateVal_{};
	std::string strVal_ {};

public:
	// Constructors
	CellValue() = default;		// null by default
	CellValue(long long v) { setInt(v); }
	CellValue(double v) { setFloat(v); }
	CellValue(const Date& v) { setDate(v); }
	CellValue(const std::string& v) { setString(v); }
	CellValue(std::string&& v) { setString(std::move(v)); }

	// Setters - set value AND type, clear NULL flag
	void setInt(long long v);
	void setFloat(double v);
	void setDate(const Date& v);
	void setString(const std::string& v);
	void setString(std::string&& v);
};