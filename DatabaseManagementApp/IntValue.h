#include "CellValue.h"

class IntValue : public CellValue {
private:
	long long value;

public:
	IntValue(long long v) : value(v) {}
};