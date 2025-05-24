#pragma once

#include "DataType.h"

#include <string>

struct Column {
	std::string name;
	DataType type;

	Column() = default;
	Column(const std::string& n, DataType t) : name(n), type(t) {};
};