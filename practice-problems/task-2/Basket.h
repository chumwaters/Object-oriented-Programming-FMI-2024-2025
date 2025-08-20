#pragma once

#include "Egg.h"

class Basket {
private:
	char* owner;
	Egg* eggs;
	int count;
	int capacity;

	void resize() {
		int newCapacity = capacity * 2;
		Egg* newArr = new Egg[newCapacity];
		for (size_t i = 0; i < count; ++i) {
			newArr[i] = eggs[i];
		}
		
		delete[] eggs;
		eggs = newArr;
		capacity = newCapacity;
	}

	void copy(const Basket& other) {
		owner = new char[strlen(other.owner) + 1];
		strcpy(owner, other.owner);
		count = other.count;
		capacity = other.capacity;

		eggs = new Egg[capacity];
		for (size_t i = 0; i < count; ++i) {
			eggs[i] = other.eggs[i];
		}
	}

public:
	Basket(const char* _owner = "") {
		owner = new char[strlen(_owner) + 1];
		strcpy(owner, _owner);
		count = 0;
		capacity = 1;
		eggs = new Egg[capacity];
	}

	Basket(const Basket& other) {
		copy(other);
	}

	Basket& operator=(const Basket& other) {
		if (this != &other) {
			delete[] owner;
			delete[] eggs;
			copy(other);
		}

		return *this;
	}

	~Basket() {
		delete[] owner;
		delete[] eggs;
	}

	const char* getOwner() const { return owner; }

	void addEgg(const Egg& e) {
		if (count >= capacity) {
			resize();
		}

		eggs[count++] = e;
	}

	bool removeEgg(const char* id) {
		for (size_t i = 0; i < count; ++i) {
			if (strcmp(eggs[i].getId(), id) == 0) {
				for (int j = i; j < count - 1; ++j) {
					eggs[j] = eggs[j + 1];
				}
				
				count--;
				return true;
			}
		}

		return false;
	}

	void serialize(const char* filename) const {
		std::ofstream ofs(filename, std::ios::binary);
		if (!ofs) throw std::runtime_error("Cannot open binary file for writing.");

		int len = strlen(owner);
		ofs.write((char*)&len, sizeof(len));
		ofs.write(owner, len);

		ofs.write((char*)&count, sizeof(count));
		for (size_t i = 0; i < count; ++i) {
			eggs[i].serialize(ofs);
		}
	}

	void deserialize(const char* filename) {
		std::ifstream ifs(filename, std::ios::binary);
		if (!ifs) throw std::runtime_error("Cannot open binary file for reading");

		int len;
		ifs.read((char*)&len, sizeof(len));
		delete[] owner;
		owner = new char[len + 1];
		ifs.read(owner, len);
		owner[len] = '\0';

		ifs.read((char*)&count, sizeof(count));
		capacity = (count == 0 ? 1 : count);
		delete[] eggs;
		eggs = new Egg[capacity];
		for (size_t i = 0; i < count; ++i) {
			eggs[i].deserialize(ifs);
		}
	}

	void generateReport() const {
		std::string filename = "report_";
		filename += owner;
		filename += ".txt";
		std::ofstream ofs(filename.c_str());
		if (!ofs) throw std::runtime_error("Cannot open report file");

		for (size_t i = 0; i < count; ++i) {
			ofs << eggs[i].getId() << " " << eggs[i].getSize() << "\n";
		}
	}
};