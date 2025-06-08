#pragma once

#include "Set.h"

#include <stdexcept>

template <typename T>
class FiniteSet : public Set<T> {
private:
	T* elements;
	std::size_t size;

	void copy(const FiniteSet<T>& other) {		
		elements = new T[other.size];

		if (!elements) {
			throw std::runtime_error("FiniteSet: Failed to allocate memory for copy.");
		}

		for (unsigned i = 0; i < other.size; ++i) {
			elements[i] = other.elements[i];
		}

		size = other.size;
	}

	static bool validate(const T* elements, const std::size_t size) {
		for (unsigned i = 0; i < size; ++i) {
			for (unsigned j = i + 1; j < size; ++j) {
				if (elements[i] == elements[j]) {
					return false;
				}
			}
		}

		return true;
	}
public:
	FiniteSet(const T* elements, const std::size_t size) 
		: size(size)
	{
		if (!validate(elements, size))
			throw std::invalid_argument("FiniteSet: Invalid arguments passed to c-tor.");

		this->elements = new T[size];
		if (!this->elements) 
			throw std::runtime_error("FiniteSet: Failed to allocate memory in c-tor.");

		for (unsigned i = 0; i < size; ++i) {
			this->elements[i] = elements[i];
		}
	}

	FiniteSet(const FiniteSet<T>& other) {
		copy(other);
	}

	FiniteSet<T>& operator=(const FiniteSet<T>& other) {
		if (this != &other) 
			copy(other);


		return this;
	}

	~FiniteSet() {
		delete[] elements;
	}

	bool contains(T elem) const override {
		for (unsigned i = 0; i < size; ++i) {
			if (elements[i] == elem)
				return true;
		}

		return false;
	}

	Set<T>* clone() const override { return new FiniteSet<T>(*this); }
};
