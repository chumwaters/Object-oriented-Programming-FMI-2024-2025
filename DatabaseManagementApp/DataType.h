#pragma once

/// @brief DataType - tag that describes the concrete cell type
enum class DataType
{
	INT,	 // 64-bit signed integer
	FLOAT,	 // Double
	DATE,	 // Calendar date (dd.mm.yyyy, year >= 1900)
	STRING,	 // Quoted string with C-style escapes
	NULLTYPE // Explicit NULL (no value)
};

struct DataTypeHelpers {
    static bool fromString(const std::string& str, DataType& out) {
        if (str == "INT") {
            out = DataType::INT;
            return true;
        }
        else if (str == "FLOAT") {
            out = DataType::FLOAT;
            return true;
        }
        else if (str == "DATE") {
            out = DataType::DATE;
            return true;
        }
        else if (str == "STRING") {
            out = DataType::STRING;
            return true;
        }

        return false;
    }
};
