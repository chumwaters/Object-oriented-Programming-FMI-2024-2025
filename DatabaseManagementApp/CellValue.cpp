#include "CellValue.h"

// Setters
void CellValue::setInt(long long v) {
	type_ = DataType::INT;
	null_ = false;
	intVal_ = v;
}

void CellValue::setFloat(double v) {
	type_ = DataType::FLOAT; 
	null_ = false;  
	floatVal_ = v;
}

void CellValue::setDate(const Date& v) {
	type_ = DataType::DATE;  
	null_ = false;  
	dateVal_ = v;
}

void CellValue::setString(const std::string& v) {
	type_ = DataType::STRING; 
	null_ = false; 
	strVal_ = v;
}

void CellValue::setString(std::string&& v) {
	type_ = DataType::STRING; 
	null_ = false; 
	strVal_ = std::move(v);
}

// NULL handling
void CellValue::setNull() {
	null_ = true;
	type_ = DataType::NULLTYPE;
}

// toString()
std::string CellValue::toString() const {
	switch (type_) {
		case DataType::INT: return std::to_string(intVal_);
		case DataType::FLOAT: return std::to_string(floatVal_);
		case DataType::DATE: return dateVal_.toString();
		case DataType::STRING:
		{
			std::string out = "\"";
			for (char c : strVal_) {
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
	if (type_ != DataType::STRING)
		return false;

	return strVal_.find(sub) != std::string::npos;
}

// Equality
bool CellValue::operator==(const CellValue& rhs) const {
	if (null_ || rhs.isNull())
		return null_ && rhs.isNull();

	if (type_ != rhs.type_)
		return false;

	switch (type_) {
		case DataType::INT:	   return intVal_  == rhs.intVal_;
		case DataType::FLOAT:  return std::fabs(floatVal_ - rhs.floatVal_) < 1e-9;
		case DataType::DATE:   return dateVal_ == rhs.dateVal_;
		case DataType::STRING: return strVal_  == rhs.strVal_;
		default: return false;
	}
}