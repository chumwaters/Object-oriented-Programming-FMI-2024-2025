#include "Column.h"
#include "Row.h"

#include <iostream>

/// @brief Print header and separator line under header from a given column structure, and
/// pre-calculated widths array for padding. Used in printRowsFormatted().
/// @param columns Metadata describing column structure.
/// @param widths Pre-calculated array containing maximum entry-width for each column, used
/// for padding.
static void printHeader(const std::vector<Column>& columns, const std::vector<std::size_t>& widths) {
	// Printing header itself
	std::cout << "| ";
	for (std::size_t i = 0; i < columns.size(); ++i) {
		std::cout << columns[i].name;

		std::size_t padding = widths[i] > columns[i].name.size() ? widths[i] - columns[i].name.size() : 0;
		for (std::size_t p = 0; p < padding; ++p) std::cout << ' ';
		if (i + 1 < columns.size()) std::cout << "| ";
	}
	std::cout << " |\n";

	// Printing  the line on the second row of the visualization
	std::cout << '|';
	for (std::size_t i = 0; i < columns.size(); ++i) {
		for (std::size_t j = 0; j < widths[i] + 1; ++j) std::cout << '-';
		if (i + 1 < columns.size()) std::cout << "+";
	}
	std::cout << "-|\n";
}

/// @brief Prints a collection of Rows with a common column structure to standart output with aligned
/// columns. Used in print and select.
/// 
/// Supports paginated output through optional parameter. By defualt, this mode is disabled,
/// when optional parameter is passed, paginated output is enabled with given rows per page.
///  Paginated output is in dialogue mode with support for <first page>, <next page>, 
/// <previous page>, <last page> and <exit>.
/// 
/// @param columns The metadata describing each column (names and types).
/// @param rows The rows of data to print. These must match the column structure.
/// @param rowsPerPage Optional parameter. Zero by default, representing non-paginated output.
/// if set to non-zero value, enables paginated output and represents the number of rows per 
/// page of output.
static void printRowsFormatted(const std::vector<Column>& columns, const std::vector<Row>& rows,
	std::size_t rowsPerPage = 0) {
	std::vector<std::size_t> widths(columns.size(), 0);

	// Finding the maximum entry size in each column and storing in widths
	for (std::size_t c = 0; c < columns.size(); ++c) {
		std::size_t maxLen = columns[c].name.length();

		for (std::size_t r = 0; r < rows.size(); ++r) {
			std::size_t len = rows[r][c]->toString().length();

			if (len > maxLen) maxLen = len;
		}

		widths[c] = maxLen;
	}

	// If only 1 page of output is necessary:
	if (rowsPerPage == 0 || rows.size() <= rowsPerPage) {
		printHeader(columns, widths);
		for (const Row& row : rows) {
			for (std::size_t c = 0; c < columns.size(); ++c) {
				std::string cellStr = row[c]->toHumanString();
				std::cout << "| " << cellStr;
				
				std::size_t padding = widths[c] > cellStr.size() ? widths[c] - cellStr.size() : 0;
				for (std::size_t p = 0; p < padding; ++p) std::cout << ' ';
			}
			std::cout << " |\n";
		}

		return;
	}

	// If more than 1 page of output is necessary:
	std::size_t pageCount = (rows.size() + rowsPerPage - 1) / rowsPerPage; // ceiling
	std::size_t currentPage = 0;
	std::string input;

	while (true) {
		std::size_t start = currentPage * rowsPerPage;
		std::size_t end = std::min(start + rowsPerPage, rows.size());

		std::cout << "\n[Page " << (currentPage + 1) << "/" << pageCount << "]\n";
		printHeader(columns, widths);
		for (std::size_t r = start; r < end; ++r) {
			for (std::size_t c = 0; c < columns.size(); ++c) {
				std::string cellStr = rows[r][c]->toHumanString();
				std::cout << "| " << cellStr;

				std::size_t padding = widths[c] > cellStr.size() ? widths[c] - cellStr.size() : 0;
				for (std::size_t p = 0; p < padding; ++p) std::cout << ' ';
			}
			std::cout << " |\n";
		}

		bool validCommand = false;
		do {
			std::cout << "\nAvailable options (exit will exit dialogue mode, but not program): \n"
				"<first page>, <next page>, <previous page>, <last page>, <exit>\n> ";
			std::getline(std::cin, input);

			if (input == "next page" && currentPage + 1 < pageCount) {
				++currentPage;
				validCommand = true;
			}
			else if (input == "previous page" && currentPage > 0) {
				--currentPage;
				validCommand = true;
			}
			else if (input == "first page") {
				currentPage = 0;
				validCommand = true;
			}
			else if (input == "last page") {
				currentPage = pageCount - 1;
				validCommand = true;
			}
			else if (input == "exit") {
				std::cout << "Exiting dialogue mode.\n";
				return;
			}
			else {
				std::cout << "Invalid command. Please try again.\n";
			}
		} while (!validCommand);
	}
}