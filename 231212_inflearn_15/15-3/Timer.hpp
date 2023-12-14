#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

class Timer
{
    using clock_t = std::chrono::high_resolution_clock;
    using second_t = std::chrono::duration<double, std::ratio<1>>;

    std::chrono::time_point<clock_t> start_time = clock_t::now();   // class가 만들어지는 시점에 시간 측정 시작.

public:
    void elapsed()
    {
        std::chrono::time_point<clock_t> end_time = clock_t::now(); // 끝난 시간 체크

        cout << std::chrono::duration_cast<second_t>(end_time - start_time).count() << endl;
    }
};