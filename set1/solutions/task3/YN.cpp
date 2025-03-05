#include "YN.h"

bool isValidYN(const YN& value) {
	return value > YN::YN_UNKNOWN && value < YN::YN_COUNT;
}

void printYN(const YN& choice) {
	if (!isValidYN(choice)) {
		std::cout << "Not a valid choice!\n";
		return;
	}

	static const char* choices[(int)YN::YN_COUNT] = { "no", "yes" };
	std::cout << choices[(int)choice] << std::endl;
}