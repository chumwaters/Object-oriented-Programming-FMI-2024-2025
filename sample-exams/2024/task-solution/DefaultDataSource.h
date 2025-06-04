#pragma once

#include "DataSource.h"

template<typename T>
class DefaultDataSource : public DataSource<T> {
private:
	T data;
public:
	const T& get() override { return data; }

	T* getN(const std::size_t n) override {
		T* result = new T[n];

		if (!result) throw std::runtime_error("Failed to allocate memory!\n");

		for (unsigned i = 0; i < n; ++i) {
			result[i] = get();
		}

		return result;
	}

	bool canGet() const override { return true; };

	bool reset() override { return true; };

	const T& operator()() override { return get(); };

	DataSource<T>& operator>>(T& t) override {
		t = get();

		return *this;
	}

	DataSource<T>* clone() const override {
		return new DefaultDataSource(*this);
	}
};