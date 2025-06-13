#pragma once

#include <string>
#include <vector>

/// @brief Unescapes C++-style string literals.
/// @param val string literal to unescape.
/// @return Unescaped modification of val parameter.
static std::string unescapeString(const std::string& val) {
	std::string parsed;

	for (size_t j = 1; j + 1 < val.size(); ++j) {
		if (val[j] == '\\' && j + 1 < val.size() - 1) {
			char next = val[j + 1];
			if (next == '"' || next == '\\') {
				parsed += next;
				++j;
			}
			else {
				parsed += val[j];
			}
		}
		else {
			parsed += val[j];
		}
	}

	return parsed;
}

/// @brief Simple token splitter helper method.
/// @param line Line to split up.
/// @return Vector of space-separated words of input line.
static std::vector<std::string> splitCommandLine(const std::string& line) {
	std::vector<std::string> tokens;
	std::string current;
	bool inQuotes = false;

	for (std::size_t i = 0; i < line.length(); ++i) {
		char c = line[i];

		if (inQuotes) {
			if (c == '\\' && i + 1 < line.length()) {
				// Handle escaped characters
				current += line[i + 1];
				++i;
			}
			else if (c == '"') {
				inQuotes = false;
				tokens.push_back(unescapeString(current));  // unescape before storing
				current.clear();
			}
			else {
				current += c;
			}
		}
		else {
			if (c == '"') {
				inQuotes = true;
			}
			else if (std::isspace(c)) {
				if (!current.empty()) {
					tokens.push_back(current);
					current.clear();
				}
			}
			else {
				current += c;
			}
		}
	}

	if (!current.empty()) {
		tokens.push_back(current);
	}

	return tokens;
}