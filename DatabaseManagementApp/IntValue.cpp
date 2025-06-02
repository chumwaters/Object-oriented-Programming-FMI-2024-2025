#include "IntValue.h"

bool IntValue::equals(const CellValue* other) const {
	if (other->getType() != DataType::INT) return false;
	
	const IntValue* iv = static_cast<const IntValue*>(other);

	return value == iv->value;
}

bool IntValue::convertTo(DataType target, CellValue*& out) const {
	switch (target) {
		case DataType::INT:
			out = new IntValue(value);
			return true;
		case DataType::FLOAT:
			out = new FloatValue(static_cast<double>(value));
			return true;
		case DataType::STRING:
			out = new StringValue(std::to_string(value));
			return true;
		default:
			return false;
	}
}