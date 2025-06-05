#pragma once

#include "Sound.h"

#include <fstream>

class FileSound : public Sound {
private: 
	void* tempArray = nullptr;

	void* processSamplesFromFile(NumericType type, const char* filename,
		const std::size_t duration, const void* M)
	{
		std::ifstream in(filename, std::ios::binary);
		if (!in)
			throw std::runtime_error("FileSound: Failed to open file.");

		switch (type) {
			case INT:
				int* arr = new int[duration];
				in.read(reinterpret_cast<char*>(arr), sizeof(int) * duration);

				int bound = *static_cast<const int*>(M);
				for (unsigned i = 0; i < duration; ++i) {
					if (arr[i] < -bound) {
						arr[i] = -bound;
					}
					else if (arr[i] > bound) {
						arr[i] = bound;
					}
				}

				tempArray = arr;
				return arr;
			case FLOAT:
				float* arr = new float[duration];
				in.read(reinterpret_cast<char*>(arr), sizeof(float) * duration);

				float bound = *static_cast<const float*>(M);
				for (unsigned i = 0; i < duration; ++i) {
					if (arr[i] < -bound) {
						arr[i] = -bound;
					}
					else if (arr[i] > bound) {
						arr[i] = bound;
					}
				}

				tempArray = arr;
				return arr;
			case DOUBLE:
				double* arr = new double[duration];
				in.read(reinterpret_cast<char*>(arr), sizeof(double) * duration);

				double bound = *static_cast<const double*>(M);
				for (unsigned i = 0; i < duration; ++i) {
					if (arr[i] < -bound) {
						arr[i] = -bound;
					}
					else if (arr[i] > bound) {
						arr[i] = bound;
					}
				}

				tempArray = arr;
				return arr;
		}

		return nullptr;
	}

	void deleteTempArray(NumericType type) {
		switch (type) {
			case INT:	 delete[] static_cast<int*>(tempArray); break;
			case FLOAT:	 delete[] static_cast<float*>(tempArray); break;
			case DOUBLE: delete[] static_cast<double*>(tempArray); break;
		}
	}
public:
	FileSound(NumericType type, const char* filename, size_t duration, const void* M)
		: Sound(type, processSamplesFromFile(type, filename, duration, M), M, duration)
	{
		deleteTempArray(type);
	}
};