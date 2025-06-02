#include "FloatValue.h"

bool FloatValue::equals(const CellValue* other) const {
	if (other->getType() != DataType::FLOAT) return false;

	const FloatValue* fv = static_cast<const FloatValue*>(other);

	return std::fabs(value - fv->value) < 1e-9;
}