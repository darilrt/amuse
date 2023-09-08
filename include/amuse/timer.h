#pragma once

#include <chrono>

namespace ut {

    class Timer {
    public:
        Timer();
        ~Timer();

        float Elapsed();

        float Reset();

    private:
		  std::chrono::time_point<std::chrono::high_resolution_clock> start;
    };

}