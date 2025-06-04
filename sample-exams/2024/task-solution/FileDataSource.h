#pragma once

#include "DataSource.h"

template <typename T>
class FileDataSource : public DataSource<T> {
private:
	std::ifstream file;
	char filename[256];
	T next;

public:
	FileDataSource(const char* filename) {
		strncpy_s(this->filename, filename, strlen(this->filename));

		file.open(filename);
		if (!file) {
			throw std::runtime_error("Could not open file for reading");
		}
	}

	~FileDataSource() {
		if (file.is_open()) 
			file.close();
	}

	void rewind() {
		file.clear();
		file.seekg(0, std::ios::beg);
	}

	const T& get() override {
		if (!canGet()) {
			throw std::runtime_error("No more elements to get!\n");
		}

		file >> next;

		return next;
	}

	T* getN(const std::size_t n) override {
		T* result = new T[n];

		if (!result) throw std::runtime_error("Failed to allocate memory "
			"for result of getN");

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

	bool canGet() const override { return file.good() && !file.eof(); };

	bool reset() override { 
		rewind();

		return canGet();
	}

	const T& operator()() override { return get(); }

	DataSource<T>& operator>>(T& t) override {
		t = (*this)();

		return *this;
	}

	DataSource<T>* clone() const override {
		return new FileDataSource(filename);
	}
};