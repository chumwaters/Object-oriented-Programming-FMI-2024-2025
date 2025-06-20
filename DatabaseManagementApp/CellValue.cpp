#include "CellValue.h"
#include "IntValue.h"
#include "FloatValue.h"
#include "DateValue.h"
#include "StringValue.h"
#include "NullValue.h"

#include <stdexcept>

CellValue* CellValue::fromString(const std::string& str, DataType type, bool& ok) {
    ok = true;

    if (str == "NULL") {
        return new NullValue();
    }

    try {
        switch (type) {
        case DataType::INT: {
            std::size_t pos = 0;
            long long val = std::stoll(str, &pos);
            if (pos != str.length()) {
                ok = false;
                return nullptr;
            }
            return new IntValue(val);
        }
        case DataType::FLOAT: {
            std::size_t pos = 0;
            double val = std::stod(str, &pos);
            if (pos != str.length()) {
                ok = false;
                return nullptr;
            }
            return new FloatValue(val);
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
        case DataType::STRING: {
            return new StringValue(str);
        }
        default: {
            ok = false;
            return nullptr;
        }
        }
    }
    catch (const std::invalid_argument&) {
        ok = false;
        return nullptr;
    }
    catch (const std::out_of_range&) {
        ok = false;
        return nullptr;
    }
}
