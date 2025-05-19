#include "CellValue.h"

// Setters
void CellValue::setInt(long long v) {
	type = DataType::INT;
	null = false;
	intVal = v;
}

void CellValue::setFloat(double v) {
	type = DataType::FLOAT; 
	null = false;  
	floatVal = v;
}

void CellValue::setDate(const Date& v) {
	type = DataType::DATE;  
	null = false;  
	dateVal = v;
}

void CellValue::setString(const std::string& v) {
	type = DataType::STRING; 
	null = false; 
	strVal = v;
}

void CellValue::setString(std::string&& v) {
	type = DataType::STRING; 
	null = false; 
	strVal = std::move(v);
}

// NULL handling
void CellValue::setNull() {
	null = true;
	type = DataType::NULLTYPE;
}

// toString()
std::string CellValue::toString() const {
	switch (type) {
		case DataType::INT: return std::to_string(intVal);
		case DataType::FLOAT: return std::to_string(floatVal);
		case DataType::DATE: return dateVal.toString();
		case DataType::STRING:
		{
			std::string out = "\"";
			for (char c : strVal) {
				if (c == '"' || c == '\\')
					out += '\\';
				out += c;
			}
			out += '"';
			return out;
		}
		default: return "NULL";
	}
}

// containsSubstring(std::string&)
bool CellValue::containsSubstring(const std::string& sub) const {
	if (type != DataType::STRING)
		return false;

	return strVal.find(sub) != std::string::npos;
}

// Equality
bool CellValue::operator==(const CellValue& rhs) const {
	if (null || rhs.isNull())
		return null && rhs.isNull();

	if (type != rhs.type)
		return false;

	switch (type) {
		case DataType::INT:	   return intVal  == rhs.intVal;
		case DataType::FLOAT:  return std::fabs(floatVal - rhs.floatVal) < 1e-9;
		case DataType::DATE:   return dateVal == rhs.dateVal;
		case DataType::STRING: return strVal  == rhs.strVal;
		default: return false;
	}
}

// Conversion
bool CellValue::convertTo(DataType newType) {
	if (null) {
		type = newType; 
		return true;
	}
	if (type == newType)
		return true;

	switch (newType) {
		case DataType::INT:
		{
			long long tmp = 0;
			bool ok = false;
			
			switch (type) {
				case DataType::FLOAT:
					tmp = static_cast<long long>(floatVal);
					ok = true;
					break;
				case DataType::STRING:
					char* endptr = nullptr;
					tmp = std::strtoll(strVal.c_str(), &endptr, 10);
					ok = (endptr && *endptr == '\0');
					break;
				default: 
					ok = false;
					break;
			}
			if (ok) { 
				setInt(tmp);
				return true;
			}
			break;
		}
		case DataType::FLOAT:
		{
			double tmp = 0.0;
			bool ok = false;
			switch (type) {
				case DataType::INT:
					tmp = static_cast<double>(intVal);
					ok = true;
					break;
				case DataType::STRING:
					char* endptr = nullptr;
					tmp = std::strtod(strVal.c_str(), &endptr);
					ok = (endptr && *endptr == '\0');
					break;
				default:
					ok = false;
					break;
			}
			if (ok) {
				setFloat(tmp); 
				return true;
			}
			break;
		}
		case DataType::STRING:
		{
			setString(toStringRaw());
			return true;
		}
		case DataType::DATE:
		{
			Date tmp;
			bool ok = false;
			if (type == DataType::STRING) {
				tmp = Date::fromString(strVal, ok);
			}
			if (ok) {
				setDate(tmp);
				return true;
			}
			break;
		}
		case DataType::NULLTYPE:
		{
			setNull();
			return true;
		}
	}

	// failure - convert to NULL of target type
	type = newType;
	null = true;
	return false;
}

std::string CellValue::toStringRaw() const {
	if (null) return "NULL";

	switch (type) {
		case DataType::INT:	   return std::to_string(intVal);
		case DataType::FLOAT:  return std::to_string(floatVal);
		case DataType::DATE:   return dateVal.toString();
		case DataType::STRING: return strVal;
		default:			   return "NULL";
	}
}
