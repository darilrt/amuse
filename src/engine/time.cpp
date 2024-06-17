#include "engine/time.hpp"

uint64_t time_now()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

Timer::Timer()
{
    start = std::chrono::high_resolution_clock::now();
}

double Timer::tick()
{
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(now - start);
    start = now;
    return duration.count() / 1000000.0f;
}

double Timer::now()
{
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(now - start);
    return duration.count() / 1000000.0f;
}

void Timer::reset()
{
    start = std::chrono::high_resolution_clock::now();
}