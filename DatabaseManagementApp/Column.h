#pragma once

#include "DataType.h"

#include <string>

struct Column {
	std::string name;
	DataType type;
};