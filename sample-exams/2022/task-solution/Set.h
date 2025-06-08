#pragma once

template <typename T>
class Set {
public:
	// Passing argument by value for use convenience 
	virtual bool contains(T value) const = 0;

	virtual Set<T>* clone() const = 0;

	virtual ~Set() = default;
};
