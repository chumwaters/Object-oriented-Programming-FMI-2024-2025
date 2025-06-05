#pragma once

#include "Sound.h"

class Sequence : public Sound {
	void* tempArray = nullptr;

	std::size_t calculateDuration(const Sound* const* sounds, const std::size_t cnt) {
		std::size_t sumDur = 0;
		for (unsigned i = 0; i < cnt; ++i) {
			sumDur += sounds[i]->getDuration();
		}

		return sumDur;
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

				std::size_t pos = 0;
				for (unsigned i = 0; i < cnt; ++i) {
					unsigned currDuration = sounds[i]->getDuration();
				
					for (unsigned j = 0; j < currDuration; ++j) {
						arr[pos] = static_cast<int>((*sounds[i])[j]);
					}
				}

				tempArray = arr;
				return arr;
			}
			case FLOAT: {
				float* arr = new float[duration];
				if (!arr)
					throw std::runtime_error("Failed to alocate memory.");

				std::size_t pos = 0;
				for (unsigned i = 0; i < cnt; ++i) {
					unsigned currDuration = sounds[i]->getDuration();

					for (unsigned j = 0; j < currDuration; ++j) {
						arr[pos] = static_cast<float>((*sounds[i])[j]);
					}
				}

				tempArray = arr;
				return arr;
			}
			case DOUBLE: {
				double* arr = new double[duration];
				if (!arr)
					throw std::runtime_error("Failed to alocate memory.");

				std::size_t pos = 0;
				for (unsigned i = 0; i < cnt; ++i) {
					unsigned currDuration = sounds[i]->getDuration();

					for (unsigned j = 0; j < currDuration; ++j) {
						arr[pos] = (*sounds[i])[j];
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
	Sequence(NumericType type, const Sound* const* sounds, const std::size_t cnt,
		const void* M)
		: Sound(type, processSamplesFromSounds(type, sounds, cnt, M), M,
			calculateDuration(sounds, cnt))
	{
		deleteTempArray(type);
	}
};