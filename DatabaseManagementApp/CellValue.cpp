#include "CellValue.h"
#include "IntValue.h"
#include "FloatValue.h"
#include "DateValue.h"
#include "StringValue.h"
#include "NullValue.h"

CellValue* CellValue::fromString(const std::string& str, DataType type, bool& ok) {
	ok = true;

	if (str == "NULL") return new NullValue();

	try {
		switch (type) {
			case DataType::INT: return new IntValue(std::stoll(str));
			case DataType::FLOAT: {
				char buff[32];
				std::snprintf(buff, sizeof(buff), "%.2f", std::stod(str));
			
				return new FloatValue(std::stod(str));
			}
			case DataType::DATE: {
				bool valid = false;
				Date d = Date::fromString(str, valid);
				if (!valid) { 
					ok = false; 
					return nullptr; 
				}

				return new DateValue(d);
			}
			case DataType::STRING: return new StringValue(str);
			default:
				ok = false; 
				return nullptr;
		}
	}
	catch (...) {
		ok = false;
		return nullptr;
	}
}