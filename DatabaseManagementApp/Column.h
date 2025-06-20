#pragma once

#include "DataType.h"

#include <string>

/// @brief Represents a column in a table with a name and data type.
struct Column {
	std::string name;
	DataType type;

	/// @brief Default constructor for Column class.
	Column() = default;

	/// @brief Constructs a Column with from a given name and data type.
	/// @param name Name to give to the constructed Column.
	/// @param type Data type for the constructed Column.
	Column(const std::string& name, DataType type) : name(name), type(type) {};
};