#pragma once

#include <string>

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
    /// @brief Converts a string to its corresponding DataType enum value.
    ///
    /// Accepts the following case-sensitive string values: "INT", "FLOAT", "DATE", "STRING", and "NULL".
    /// If the string matches a known type, `out` is set to the corresponding DataType and the function returns true.
    /// If the string is unrecognized, `out` is not modified and the function returns false.
    ///
    /// @param str The string representation of the data type.
    /// @param out Output parameter set to the corresponding DataType if conversion succeeds.
    /// @return True if the conversion was successful; false otherwise.
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

    /// @brief Converts a DataType enum to its string representation.
    /// @param type The DataType to convert.
    /// @return A string representation such as "INT", "FLOAT", "DATE", "STRING", or "NULL".
    static std::string toString(DataType type) {
        switch (type) {
        case DataType::INT: return "INT";
        case DataType::FLOAT: return "FLOAT";
        case DataType::DATE: return "DATE";
        case DataType::STRING: return "STRING";
        case DataType::NULLTYPE: return "NULL";
        default: return "UNKNOWN";
        }
    }
};
