#include "DateValue.h"
#include "StringValue.h"

bool DateValue::equals(const CellValue* other) const {
	if (other->getType() != DataType::DATE) return false;

	const DateValue* dv = static_cast<const DateValue*>(other);

	return value == dv->value;
}

bool DateValue::convertTo(DataType target, CellValue*& out) const {
	switch (target) {
		case DataType::DATE:
			out = new DateValue(value);
			return true;
		case DataType::STRING:
			out = new StringValue(value.toString());
			return true;
		default:
			return false;
	}
}