#pragma once

#include "Sound.h"

class PeriodicSound : public Sound {
private:
	void* tempArray = nullptr;

	std::size_t calculateDuration(const std::size_t repetitions,
		const std::size_t templateSize)
	{
		return templateSize * repetitions;
	}

	void* processSamplesFromTemplate(NumericType type, const void* sampleTemplate,
		const std::size_t templateSize, const std::size_t repetitions, const void* M)
	{
		const std::size_t duration = calculateDuration(repetitions, templateSize);

		switch (type) {
			case INT: {
				int* arr = new int[duration];
				if (!arr)
					throw std::runtime_error("Failed to alocate memory.");

				for (unsigned i = 0; i < repetitions; ++i) {
					for (unsigned j = 0; j < templateSize; ++j) {
						arr[i * templateSize + j] =
							static_cast<const int*>(sampleTemplate)[j];
					}
				}

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
			}
			case FLOAT: {
				float* arr = new float[duration];
				if (!arr)
					throw std::runtime_error("Failed to alocate memory.");

				for (unsigned i = 0; i < repetitions; ++i) {
					for (unsigned j = 0; j < templateSize; ++j) {
						arr[i * templateSize + j] =
							static_cast<const float*>(sampleTemplate)[j];
					}
				}

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
			}
			case DOUBLE: {
				double* arr = new double[duration];
				if (!arr)
					throw std::runtime_error("Failed to alocate memory.");

				for (unsigned i = 0; i < repetitions; ++i) {
					for (unsigned j = 0; j < templateSize; ++j) {
						arr[i * templateSize + j] =
							static_cast<const double*>(sampleTemplate)[j];
					}
				}

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
	PeriodicSound(NumericType type, const void* sampleTemplate, 
		std::size_t templateSize, std::size_t repetitions, const void* M) 
		: Sound(type, processSamplesFromTemplate(type, sampleTemplate, 
			templateSize, repetitions, M), M, 
			calculateDuration(repetitions, templateSize))
	{
		deleteTempArray(type);
	}
};
