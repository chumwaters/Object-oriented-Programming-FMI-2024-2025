#include "FloatValue.h"
#include "IntValue.h"
#include "StringValue.h"

bool FloatValue::equals(const CellValue* other) const {
	if (other->getType() != DataType::FLOAT) return false;

	const FloatValue* fv = static_cast<const FloatValue*>(other);

	return std::fabs(value - fv->value) < 1e-9;
}

bool FloatValue::convertTo(DataType target, CellValue*& out) const {
	switch (target) {
		case DataType::FLOAT:
			out = new FloatValue(value);
			return true;
		case DataType::INT:
			out = new IntValue(static_cast<long long>(value));
			return true;
		case DataType::STRING:
			out = new StringValue(std::to_string(value));
			return true;
		default: 
			return false;
	}
}