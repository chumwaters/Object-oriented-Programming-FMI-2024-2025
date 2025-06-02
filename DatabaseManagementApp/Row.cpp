#include "Row.h"
#include "NullValue.h"

Row::Row(size_t columnCount) {
	for (size_t i = 0; i < columnCount; ++i) {
		cells.push_back(new NullValue());
	}
}