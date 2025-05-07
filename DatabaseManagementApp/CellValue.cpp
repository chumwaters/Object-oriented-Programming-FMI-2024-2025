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