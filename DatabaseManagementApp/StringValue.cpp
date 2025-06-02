#include "StringValue.h"

std::string StringValue::toString() const {
	std::string out = "\"";

	for (char c : value) {
		if (c == '"' || c == '\\') out += '\\';
		out += c;
	}

	out += '"';

	return out;
}

bool StringValue::equals(const CellValue* other) const {
	if (other->getType() != DataType::STRING) return false;

	const StringValue* sv = static_cast<const StringValue*>(other);

	return value == sv->value;
}

bool StringValue::containsSubstring(const std::string& s) const {
	return value.find(s) != std::string::npos;
}