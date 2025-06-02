#pragma once

#include "CellValue.h"

#include <vector>

/// @brief Represents a row in a table, containing a sequence of CellValue pointers.
class Row
{
private:
	std::vector<CellValue *> cells;

public:
	/// @brief Default constructor for Row class.
	Row() = default;

	/// @brief Constructs a Row with a specific number of NULL cells.
	/// @param columnCount The number of NULL cells to initialize.
	Row(size_t columnCount);

	/// @brief Copy constructor (deep copy)
	Row(const Row &other);

	/// @brief Move constructor
	Row(Row &&other) noexcept;

	/// @brief Copy assignment operator (deep copy)
	Row &operator=(const Row &other);

	/// @brief Move assignment operator
	Row &operator=(Row &&other) noexcept;

	/// @brief Destructor
	~Row();

	/// @return Number of cells in the Row.
	size_t size() const { return cells.size(); };

	/// @brief Access cell by index. Throws if index is out of range.
	/// @param i Index of the cell
	/// @return Reference to the CellValue pointer of the i-th element
	/// of cells.
	CellValue *&operator[](size_t i);

	/// @brief Access cell by index (const version). Throws if index
	/// is out of range.
	/// @param i Index of the cell
	/// @return Const pointer to the CellValue at position i in
	/// cells vector.
	const CellValue *operator[](size_t i) const;

	/// @brief Adds a cell to the row (takes ownership)
	/// @param val The CellValue pointer to add
	void addCell(CellValue *val);
};