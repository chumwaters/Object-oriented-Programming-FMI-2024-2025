#pragma once

#include "DataSource.h"

template <typename T>
class AlternateDataSource : public DataSource<T> {
private:
	DataSource<T>** DSArray;
	std::size_t size;
	std::size_t iter;

public:
	AlternateDataSource() : DSArray(nullptr), size(0), iter(0) {}

	AlternateDataSource(DataSource<T>** dataSources, const size_t size)
		: DSArray(dataSources), size(size), iter(0) {}

	AlternateDataSource(const AlternateDataSource& other) {
		copy(other);
	}

	AlternateDataSource& operator=(const AlternateDataSource& other) {
		if (this != &other) {
			copy(other);
		}

		return *this;
	}

	AlternateDataSource(AlternateDataSource&& other) noexcept
	{
		move(other);
	}

	AlternateDataSource& operator=(AlternateDataSource&& other) noexcept {
		if (this != &other) {
			move(other);
		}

		return *this;
	}

	~AlternateDataSource() {
		clear();
	}

	void copy(const AlternateDataSource& other) {
		clear();

		DSArray = new DataSource<T>*[other.size];
		for (unsigned i = 0; i < other.size; ++i) {
			DSArray[i] = other.DSArray[i]->clone();
		}

		size = other.size;
		iter = other.iter;
	}

	void move(AlternateDataSource&& other) noexcept {
		DSArray = other.DSArray;
		size = other.size;
		iter = other.iter;
		other.DSArray = nullptr;
		other.size = 0;
		other.iter = 0;
	}

	void clear() {
		if (DSArray) {
			for (unsigned i = 0; i < size; ++i) {
				delete DSArray[i];
			}
			delete[] DSArray;
			DSArray = nullptr;
		}
		size = 0;
		iter = 0;
	}

	const T& get() override {
		if (!static_cast<bool>(*this))
			throw std::runtime_error("All data sources are empty!\n");

		while (!DSArray[iter]->canGet()) {
			iter++;

			if (iter == size)
				iter = 0;
		}

		T result = DSArray[iter]->get();

		iter++;

		if (iter == size)
			iter = 0;

		return result;
	}

	T* getN(const std::size_t n) override {
		T* result = new T[n];

		try {
			for (unsigned i = 0; i < n; ++i) {
				result[i] = get();
			}
		}
		catch (...){
			delete[] result;
			throw;
		}

		return result;
	}

	bool canGet() const override { 
		for (unsigned i = 0; i < size; ++i) {
			if (DSArray[i]->canGet())
				return true;
		}

		return false;
	}

	bool reset() override {
		bool allSucceeded = true;

		for (unsigned i = 0; i < size; ++i) {
			if (!DSArray[i]->reset())
				allSucceeded = false;
		}

		iter = 0;

		return allSucceeded;
	}

	const T& operator()() override { return get(); }

	DataSource<T>& operator>>(T& t) override {
		t = get();

		return *this;
	}

	DataSource<T>* clone() const override {
		return new AlternateDataSource(*this);
	}
};