#include "IntValue.h"

bool IntValue::equals(const CellValue* other) const {
	if (other->getType() != DataType::INT) return false;
	
	const IntValue* iv = static_cast<const IntValue*>(other);

	return value == iv->value;
}