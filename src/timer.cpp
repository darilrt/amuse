#include "amuse/timer.h"

ut::Timer::Timer() {
	start = std::chrono::high_resolution_clock::now();
}

ut::Timer::~Timer() { }

float ut::Timer::Elapsed() {
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	return duration.count() / 1000000.0f;
}

float ut::Timer::Reset() {
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	
	start = std::chrono::high_resolution_clock::now();

	return duration.count() / 1000000.0f;
}
