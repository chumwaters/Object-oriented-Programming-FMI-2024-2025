#pragma once

#include "Egg.h"

class Basket {
private:
	char* owner;
	Egg* eggs;
	size_t count;
	size_t capacity;

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

	Egg& operator[](const size_t index) { 
		if (index >= count)
			throw std::out_of_range("Invalid basket index.");
		
		return eggs[index]; 
	}

	const Egg& operator[](const size_t index) const {
		if (index >= count)
			throw std::out_of_range("Invalid basket index.");

		return eggs[index];
	}

	Egg& operator[](const std::string& str) {
		for (size_t i = 0; i < count; ++i) {
			if (strcmp(str.c_str(), eggs[i].getId()) == 0) {
				return eggs[i];
			}
		}

		throw std::invalid_argument("No egg has this id.");
	}

	const Egg& operator[](const std::string& str) const {
		for (size_t i = 0; i < count; ++i) {
			if (strcmp(str.c_str(), eggs[i].getId()) == 0) {
				return eggs[i];
			}
		}

		throw std::invalid_argument("No egg has this id.");
	}

	Basket& operator+=(const Basket& other) {
		appendEggs(other);

		return *this;
	}

	std::string& operator+=(std::string& str) const {
		appendIdsToString(str);

		return str;
	}

	Basket& operator*=(const size_t coeff) {
		scaleEggs(coeff);

		return *this;
	}

	Basket& operator/=(const size_t div) {
		if (div == 0) throw std::invalid_argument("Cannot divide by zero.");

		scaleEggs(1 / div);

		return *this;
	}

	Basket& operator%=(const Basket& other) {
		removeUnique(other);

		return *this;
	}

	bool operator==(const Basket& other) const {
		for (size_t i = 0; i < count; ++i) {
			if (eggs[i] != other.eggs[i])
				return false;
		}

		return true;
	}

	bool operator!=(const Basket& other) const { return !(*this == other); }

	bool operator<(const Basket& other) const {
		for (size_t i = 0; i < count; ++i) {
			if (other.eggs[i] < eggs[i]) return false;
			if (eggs[i] < other.eggs[i]) return true;
		}

		return false;
	}

	bool operator<=(const Basket& other) const {
		return (*this < other || *this == other);
	}

	bool operator>=(const Basket& other) const {
		return !(*this < other);
	}

	char* getOwner() const { return owner; }

	size_t getCount() const { return count; }

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

	void appendEggs(const Basket& other) {
		for (size_t i = 0; i < other.getCount(); ++i) {
			this->addEgg(other[i]);
		}
	}

	void appendIdsToString(std::string& str) const {
		for (size_t i = 0; i < count; ++i) {
			str += eggs[i].getId();
		}
	}

	void scaleEggs(const size_t coeff) {
		for (size_t i = 0; i < count; ++i) {
			eggs[i].setSize(eggs[i].getSize() * coeff);
		}
	}

	void removeUnique(const Basket& other) {
		for (size_t i = 0; i < count; ++i) {
			bool unique = true;
			for (size_t j = 0; j < other.getCount(); ++j) {
				if (eggs[i] == other.eggs[j]) {
					unique = false;
					break;
				}
			}
			if (unique == true) removeEgg(eggs[i].getId());
		}
	}
};

Basket operator+(const Basket& lhs, const Basket& rhs) {
	Basket result = Basket(lhs);
	
	result.appendEggs(rhs);

	return result;
}

std::string operator+(std::string& str, const Basket& b) {
	b.appendIdsToString(str);

	return str;
}

Basket operator*(const Basket& b, const size_t coeff) {
	Basket result(b);

	result.scaleEggs(coeff);

	return result;
}

Basket operator/(const Basket& b, const size_t div) {
	if (div == 0) throw std::invalid_argument("Cannot divide by zero.");

	Basket result(b);

	result.scaleEggs(1 / div);

	return result;
}

Basket operator%(const Basket& lhs, const Basket& rhs) {
	Basket result(lhs);

	result.removeUnique(rhs);

	return result;
}