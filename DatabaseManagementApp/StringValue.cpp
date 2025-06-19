#include "StringValue.h"
#include "IntValue.h"
#include "FloatValue.h"

std::string StringValue::toString() const
{
	std::string out = "\"";

	for (char c : value)
	{
		if (c == '"' || c == '\\')
			out += '\\';
		out += c;
	}

	out += '"';

	return out;
}

bool StringValue::equals(const CellValue *other) const
{
	if (other->getType() != DataType::STRING)
		return false;

	const StringValue *sv = static_cast<const StringValue *>(other); // TODO?

	return value == sv->value;
}

bool StringValue::containsSubstring(const std::string &s) const
{
	return value.find(s) != std::string::npos;
}

bool StringValue::convertTo(DataType target, CellValue *&out) const
{
	switch (target)
	{
		case DataType::STRING:
			out = new StringValue(value);
			return true;
		case DataType::INT:
		{
			char *endptr = nullptr;
			long long val = std::strtoll(value.c_str(), &endptr, 10);

			if (*endptr != '\0')
				return false;

			out = new IntValue(val);

			return true;
		}
		case DataType::FLOAT:
		{
			char *endptr = nullptr;
			double val = std::strtod(value.c_str(), &endptr);

			if (*endptr != '\0')
				return false;

			out = new FloatValue(val);

			return true;
		}
		default:
			return false;
		}
}