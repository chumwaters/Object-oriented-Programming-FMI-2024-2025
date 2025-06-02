#pragma once

#include "CellValue.h"

class StringValue : public CellValue {
private:
	std::string value;

public:
	/// @brief Constructs a StringValue from a given std::string object.
	/// @param v The string to store.
	StringValue(const std::string& v);
};