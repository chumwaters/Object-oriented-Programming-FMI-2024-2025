#include "DateValue.h"

bool DateValue::equals(const CellValue* other) const {
	if (other->getType() != DataType::DATE) return false;

	const DateValue* dv = static_cast<const DateValue*>(other);

	return value == dv->value;
}