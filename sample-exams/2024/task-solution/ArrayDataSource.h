#pragma once

#include "DataSource.h"

template <typename T>
class ArrayDataSource : public DataSource<T> {
private:
	T* data;
	size_t size;
	T next;	
	std::size_t iter;
public:
	ArrayDataSource() : data(nullptr), size(size), next() {}

	ArrayDataSource(T* data, const size_t size) 
		: data(data), size(size), next(data[0]), iter(0) {}

	ArrayDataSource(const ArrayDataSource& other) {
		copy(other);
	}

	ArrayDataSource(ArrayDataSource&& other) noexcept  {
		move(other);
	}

	ArrayDataSource& operator=(const ArrayDataSource& other) {
		if (this != &other) {
			copy(other);
		}

		return *this;
	}

	ArrayDataSource& operator=(ArrayDataSource&& other) noexcept {
		if (this != &other) {
			move(other);
		}

		return *this;
	}

	~ArrayDataSource() noexcept {
		clear();
	}

	void push(const T& t) {
		T* newData = new T[size + 1];

		for (unsigned i = 0; i < size; i++) {
			newData[i] = data[i];
		}
		newData[size] = t;

		delete[] data;
		data = newData;

		if (size == 0) { // if size was 0 before pushing
			next = t;
		}
		size++;

	}

	void clear() {
		delete[] data;
		data = nullptr;
		size = 0;
	}

	void copy(const ArrayDataSource& other) {
		clear();

		data = other.data;
		size = other.size;
		next = other.next;
		iter = other.iter;
	}

	void move(ArrayDataSource&& other) noexcept {
		data = other.data;
		size = other.size;
		next = std::move(other.next);
		iter = other.iter;
		other.data = nullptr;
		other.size = 0;
		other.iter = 0;
	}

	const T& get() override {
		if (!canGet()) 
			throw std::runtime_error("No more elements to get!\n");

		next = data[iter];

		iter++;

		return next;
	}

	T* getN(const size_t n) override {
		T* result = new T[n];

		for (unsigned i = 0; i < n; ++i) {
			try {
				result[i] = get();
			}
			catch (...){
				delete[] result;
				throw;
			}
		}

		return result;
	}

	bool canGet() const override { return iter != size; }

	bool reset() override { 
		iter = 0;

		return true;
	}

	const T& operator()() override { return get(); }

	DataSource<T>& operator>>(T& t) override {
		t = (*this)();

		return *this;
	}

	DataSource<T>* clone() const override {
		return new ArrayDataSource(*this);
	}
};