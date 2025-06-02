#include "CellValue.h"

class IntValue : public CellValue {
private:
	long long value;

public:
	IntValue(long long v) : value(v) {}

	DataType getType() const override { return DataType::INT; }

	std::string toString() const override { return std::to_string(value); }

	bool isNull() const override { return false; }
};