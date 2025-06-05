#pragma once

#include <utility>
#include <stdexcept>

class Sound {
public:
	enum NumericType { INT, FLOAT, DOUBLE };

private:
	NumericType type;
	void* samples;
	void* M;
	size_t duration;

	void copy(const Sound& other) {
		type = other.type;
		duration = other.duration;

		setSamples(type, other.samples, duration);
		setBound(type, other.M);
	}

	void move(Sound&& other) noexcept {
		type = other.type;
		duration = other.duration;
		samples = other.samples;
		M = other.M;
		other.samples = nullptr;
		other.M = nullptr;
		other.duration = 0;
	}

	void setSamples(const NumericType type, const void* samples, const size_t duration) {
		switch (type) {
		case INT:
			this->samples = new int[duration];
			const int* src = static_cast<const int*>(samples);
			int* dst = static_cast<int*>(this->samples);
			for (unsigned i = 0; i < duration; ++i) dst[i] = src[i];
			break;
		case FLOAT:
			this->samples = new float[duration];
			const float* src = static_cast<const float*>(samples);
			float* dst = static_cast<float*>(this->samples);
			for (unsigned i = 0; i < duration; ++i) dst[i] = src[i];
			break;
		case DOUBLE:
			this->samples = new double[duration];
			const double* src = static_cast<const double*>(samples);
			double* dst = static_cast<double*>(this->samples);
			for (unsigned i = 0; i < duration; ++i) dst[i] = src[i];
			break;
		}
	}

	void setBound(NumericType type, const void* src) {
		switch (type) {
		case INT:
			M = new int(*static_cast<const int*>(src));
			break;
		case FLOAT:
			M = new float(*static_cast<const float*>(src));
			break;
		case DOUBLE:
			M = new double(*static_cast<const double*>(src));
			break;
		}
	}

	void clear() {
		switch (type) {
			case INT:    
				delete[] static_cast<int*>(samples);
				delete   static_cast<int*>(M);
			case FLOAT:  
				delete[] static_cast<float*>(samples);
				delete   static_cast<float*>(M);
			case DOUBLE: 
				delete[] static_cast<double*>(samples);
				delete   static_cast<double*>(M);
		}
	}
public:
	Sound() : type(DOUBLE), samples(nullptr), M(nullptr), duration(0) {}

	Sound(const NumericType type, const void* samples, const void* M, const size_t duration)
		: type(type), duration(duration)
	{
		setSamples(type, samples, duration);
		setBound(type, M);
	}

	Sound(const Sound& other) { copy(other); }

	Sound& operator=(const Sound& other) {
		if (this != &other)
			copy(other);

		return *this;
	}

	Sound(Sound&& other) noexcept { move(std::move(other)); }

	Sound& operator=(Sound&& other) {
		if (this != &other)
			move(std::move(other));

		return *this;
	}

	virtual ~Sound() { clear(); }

	std::size_t getDuration() const { return duration; }

	double operator[](const size_t pos) const {
		if (pos >= duration)
			throw std::out_of_range("Sound::operator[] - index out of bounds.");

		switch (type) {
		case INT:
			return static_cast<double>(static_cast<int*>(samples)[pos]);
		case FLOAT:
			return static_cast<double>(static_cast<float*>(samples)[pos]);
		case DOUBLE:
			return static_cast<double*>(samples)[pos]; 
		default:
			throw std::runtime_error("Sound::operator[] - unknown NumericType");
		}
	}
};