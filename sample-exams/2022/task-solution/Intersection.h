#pragma once

#include "Set.h"

#include <stdexcept>

template <typename T>
class Intersection : public Set<T> {
private:
	Set** operands;
	std::size_t count;

	void copy(const Intersection<T>& other) {
		operands = new Set<T>*[other.count];

		if (!operands)
			throw std::runtime_error("Intersection: Failed to allocate memory in copy.");

		for (unsigned i = 0; i < other.count; ++i) {
			operands[i] = other.operands[i];
		}
	}
public:
	Intersection(const Set<T>** operands, const std::size_t count) 
		: count(count)
	{
		this->operands = new Set<T>* [count];

		if (!operands)
			throw std::runtime_error("Intersection: Failed to allocate memory in c-tor.");

		for (unsigned i = 0; i < count; ++i) {
			this->operands[i] = operands[i];
		}
	}

	Intersection(const Intersection<T>& other) {
		copy(other);
	}

	Intersection<T>& operator=(const Intersection<T>& other) {
		if (this != &other)
			copy(other);

		return *this;
	}

	~Intersection() {
		if (operands) {
			for (unsigned i = 0; i < count; ++i)
				delete operands[i];

			delete[] operands;
		}

		operands = nullptr;
	}

	bool contains(T elem) const override {
		if (count == 0)
			return false;

		for (unsigned i = 0; i < count; ++i) {
			if (!operands[i]->contains(elem))
				return false;
		}

		return true;
	}

	Set<T>* clone() const override { return new Intersection<T>(*this); }
};
