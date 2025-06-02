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