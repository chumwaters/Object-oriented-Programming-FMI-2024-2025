#pragma once

#include "Column.h"
#include "Row.h"

#include <string>
#include <vector>
#include <exception>

class Table {
private:
	std::string name;
	std::vector<Column> columns;
	std::vector<Row> rows;

public:

};