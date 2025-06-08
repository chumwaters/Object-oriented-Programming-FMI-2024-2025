#pragma once

#include "Set.h"

#include <stdexcept>

template <typename T>
class Union : public Set<T> {
private:
	Set** operands;
	std::size_t count;

	void copy(const Union<T>& other) {
		operands = new Set<T>*[other.count];

		if (!operands)
			throw std::runtime_error("Union: Failed to allocate memory in copy.");

		for (unsigned i = 0; i < other.count; ++i) {
			operands[i] = other.operands[i];
		}
	}
public:
	Union(const Set<T>** operands, const std::size_t count) 
		: count(count)
	{
		this->operands = new Set<T>*[count];

		if (!operands)
			throw std::runtime_error("Union: Failed to allocate memory in c-tor.");

		for (unsigned i = 0; i < count; ++i) {
			this->operands[i] = operands[i];
		}
	}

	Union(const Union<T>& other) {
		copy(other);
	}

	Union<T>& operator=(const Union<T>& other) {
		if (this != &other)
			copy(other);

		return *this;
	}

	~Union() {
		if (operands) {
			for (unsigned i = 0; i < count; ++i)
				delete operands[i];

			delete[] operands;
		}

		operands = nullptr;
	}

	bool contains(T elem) const override {
		for (unsigned i = 0; i < count; ++i) {
			if (!operands[i]->contains(elem))
				return true;
		}

		return false;
	}

	Set<T>* clone() const override { return new Union<T>(*this); }
};