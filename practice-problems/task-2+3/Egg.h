#pragma once

#include <cstring>
#include <fstream>

class Egg {
private:
	char* id; // unique string
	double size;

	void copy(const Egg& other) {
		id = new char[strlen(other.id) + 1];
		strcpy(id, other.id);
		size = other.size;
	}

public:
	Egg(const char* _id = "", double _size = 0.0) {
		id = new char[strlen(_id) + 1];
		strcpy(id, _id);
		size = _size;
	}

	Egg(const Egg& other) {
		copy(other);
	}

	Egg& operator=(const Egg& other) {
		if (this != &other) {
			delete[] id;
			copy(other);
		}

		return *this;
	}

	bool operator==(const Egg& other) const { return strcmp(id, other.getId()) == 0; }

	bool operator!=(const Egg& other) const { return !(*this == other); }

	bool operator<(const Egg& other) const { return strcmp(id, other.getId()) < 0; }

	~Egg() {
		delete[] id;
	}

	const char* getId() const { return id; }
	double getSize() const { return size; }

	void setSize(const size_t newSize) { size = newSize; }

	void serialize(std::ostream& os) const {
		int len = strlen(id);
		os.write((char*)&len, sizeof(len));
		os.write(id, len);
		os.write((char*)&size, sizeof(size));
	}

	void deserialize(std::istream& is) {
		int len = 0;
		is.read((char*)&len, sizeof(len));
		
		delete[] id;
		id = new char[len + 1];
		is.read(id, len);
		id[len] = '\0';

		is.read((char*)&size, sizeof(size));
	}
};
