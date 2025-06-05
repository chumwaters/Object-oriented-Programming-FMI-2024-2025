#pragma once

#include "Sound.h"

class Mix : public Sound {
private:
	void* tempArray = nullptr;

	std::size_t calculateDuration(const Sound* const* sounds, const std::size_t cnt) {
		std::size_t maxDur = 0;
		for (unsigned i = 0; i < cnt; ++i) {
			if (sounds[i]->getDuration() > maxDur)
				maxDur = sounds[i]->getDuration();
		}

		return maxDur;
	}

	int calculateSumAtIndexINT(const Sound* const* sounds, const std::size_t cnt,
		const std::size_t pos) 
	{
		int sum = 0;

		for (unsigned i = 0; i < cnt; ++i) {
			sum += static_cast<int>((*sounds[i])[pos]);
		}

		return sum / cnt;
	}

	float calculateSumAtIndexFLOAT(const Sound* const* sounds, const std::size_t cnt,
		const std::size_t pos)
	{
		float sum = 0;

		for (unsigned i = 0; i < cnt; ++i) {
			sum += static_cast<float>((*sounds[i])[pos]);
		}

		return sum / cnt;
	}

	double calculateSumAtIndexDOUBLE(const Sound* const* sounds, const std::size_t cnt,
		const std::size_t pos) 
	{
		double sum = 0;

		for (unsigned i = 0; i < cnt; ++i) {
			sum += (*sounds[i])[pos];
		}

		return sum / cnt;
	}

	void* processSamplesFromSounds(NumericType type, const Sound* const* sounds,
		const std::size_t cnt, const void* M)
	{
		const std::size_t duration = calculateDuration(sounds, cnt);

		switch (type) {
			case INT: {
				int* arr = new int[duration];
				if (!arr)
					throw std::runtime_error("Failed to alocate memory.");

				for (unsigned i = 0; i < duration; ++i) {
					arr[i] = calculateSumAtIndexINT(sounds, cnt, i);

					int bound = *static_cast<const int*>(M);
					if (arr[i] > bound)
						arr[i] = bound;
					else if (arr[i] < -bound)
						arr[i] = -bound;
				}

				tempArray = arr;
				return arr;
			}
			case FLOAT: {
				float* arr = new float[duration];
				if (!arr)
					throw std::runtime_error("Failed to alocate memory.");

				for (unsigned i = 0; i < duration; ++i) {
					arr[i] = calculateSumAtIndexFLOAT(sounds, cnt, i);

					int bound = *static_cast<const float*>(M);
					if (arr[i] > bound)
						arr[i] = bound;
					else if (arr[i] < -bound)
						arr[i] = -bound;
				}

				tempArray = arr;
				return arr;
			}
			case DOUBLE: {
				double* arr = new double[duration];
				if (!arr)
					throw std::runtime_error("Failed to alocate memory.");

				for (unsigned i = 0; i < duration; ++i) {
					arr[i] = calculateSumAtIndexDOUBLE(sounds, cnt, i);

					double bound = *static_cast<const double*>(M);
					if (arr[i] > bound)
						arr[i] = bound;
					else if (arr[i] < -bound)
						arr[i] = -bound;
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
	Mix(NumericType type, const Sound* const* sounds, const std::size_t cnt,
		const void* M)
		: Sound(type, processSamplesFromSounds(type, sounds, cnt, M), M, 
			calculateDuration(sounds, cnt))
	{
		deleteTempArray(type);
	}
};