#pragma once

#include "Set.h"

template <typename T>
class ConstructedSet : public Set<T> {
private:
	bool (*predicate)(T);

public:
	ConstructedSet(bool (*predicate)(T) : predicate(predicate) {
		if (!predicate)
			throw std::invalid_argument("ConstructedSet: Null predicate passed to c-tor.");
	}

	bool contains(T value) const override { return predicate(value); }

	Set<T>* clone() const override { return new ConstructedSet<T>(predicate); }
};