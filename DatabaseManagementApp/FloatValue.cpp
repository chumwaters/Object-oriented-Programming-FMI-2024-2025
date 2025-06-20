#include "FloatValue.h"
#include "IntValue.h"
#include "StringValue.h"

#include <cmath>

std::string FloatValue::toString() const {
	char buff[32];
	std::snprintf(buff, sizeof(buff), "%.2f", value);

	return std::string(buff);
}

bool FloatValue::equals(const CellValue *other) const
{
	if (other->getType() != DataType::FLOAT)
		return false;

	const FloatValue *fv = static_cast<const FloatValue *>(other);

	return std::fabs(value - fv->value) < 1e-9;
}

bool FloatValue::convertTo(DataType target, CellValue *&out) const
{
	switch (target)
	{
	case DataType::FLOAT:
		out = new FloatValue(value);
		return true;
	case DataType::INT:
		out = new IntValue(static_cast<long long>(value));
		return true;
	case DataType::STRING:
		out = new StringValue(this->toString());
		return true;
	default:
		return false;
	}
}