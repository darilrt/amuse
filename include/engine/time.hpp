#pragma once
#include <chrono>

uint64_t time_now();

class Timer
{
public:
    Timer();

    double tick();

    double now();

    void reset();

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
};