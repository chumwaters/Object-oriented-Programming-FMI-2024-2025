#pragma once

#include "Color.h"

enum YN {
	YN_UNKNOWN = -1,
	NO,
	YES,
	YN_COUNT
};

bool isValidYN(const YN& value);

void printYN(const YN& choice);