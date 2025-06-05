#pragma once

#include "Sound.h"

class Silence : public Sound {
private:
	void* tempZeroArray = nullptr;
	void* tempZeroValue = nullptr;

	void* makeZeroArray(NumericType type, const std::size_t duration) {
		switch (type) {
			case INT:{
				int* arr = new int[duration]();
				tempZeroArray = arr;
				return arr;
			}	
			case FLOAT: {
				float* arr = new float[duration]();
				tempZeroArray = arr;
				return arr;
			}			
			case DOUBLE: {
				double* arr = new double[duration]();
				tempZeroArray = arr;
				return arr;
			}		
		}
		
		return nullptr;
	}
	
	void* makeZeroValue(NumericType type) {
		switch (type) {
			case INT: 
				tempZeroValue = new int(0);
				return tempZeroValue;
			case FLOAT:
				tempZeroValue = new float(0);
				return tempZeroValue;
			case DOUBLE:
				tempZeroValue = new double(0);
				return tempZeroValue;
		}

		return nullptr;
	}

	void deleteTempZeroArray(NumericType type) {
		switch (type) {
			case INT:
				delete[] static_cast<int*>(tempZeroArray);
				break;
			case FLOAT:
				delete[] static_cast<float*>(tempZeroArray);
				break;
			case DOUBLE:
				delete[] static_cast<double*>(tempZeroArray);
				break;
		}

		tempZeroArray = nullptr;
	}

	void deleteTempZeroValue(NumericType type) {
		switch (type) {
			case INT:
				delete static_cast<int*>(tempZeroValue);
				break;
			case FLOAT:
				delete static_cast<float*>(tempZeroValue);
				break;
			case DOUBLE:
				delete static_cast<double*>(tempZeroValue);
				break;
		}

		tempZeroValue = nullptr;
	}
public:
	Silence(NumericType type, size_t duration) 
		: Sound(type, makeZeroArray(type, duration), makeZeroValue(type), duration)
	{
		deleteTempZeroArray(type);
		deleteTempZeroValue(type);
	}
};