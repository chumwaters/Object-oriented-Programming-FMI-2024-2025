#pragma once

#include <fstream>

template<typename T>
class DataSource {
public:
	virtual const T& get() = 0;

	virtual T* getN(const std::size_t n) = 0;

	virtual bool canGet() const = 0;

	virtual bool reset() = 0;

	virtual const T& operator()() = 0;

	virtual DataSource<T>& operator>>(T& t) = 0;

	virtual explicit operator bool() const { return canGet(); };

	virtual DataSource<T>* clone() const = 0;
};