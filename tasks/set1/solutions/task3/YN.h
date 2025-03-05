#pragma once

#include "Color.h"

enum YN {
	YN_UNKNOWN = -1,
	NO,
	YES,
	YN_COUNT
};

bool isValidYN(YN value);

void printYN(YN choice);