
#ifndef _VAVAVA_TIME_INTERVAL_H__
#define _VAVAVA_TIME_INTERVAL_H__

#include <cstdint>
#include <chrono>


namespace vavava {


template<typename T>
class TimeInterval
{
    typedef std::chrono::time_point<std::chrono::high_resolution_clock>  time_point_t;
public:
    TimeInterval()
    {
        first_ = std::chrono::high_resolution_clock::now();
    }

    void tick()
    {
        auto now = std::chrono::high_resolution_clock::now();
        auto d = now - last_;
        last_ = now;
        interval_ = std::chrono::duration_cast<T>(d).count();
    }
    
    int64_t get_interval()
    {
        return interval_;
    }

    int64_t get_total()
    {
        auto now = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<T>(now - first_).count();
    }

protected:
    time_point_t last_;
    time_point_t first_;
    int64_t interval_;
};

typedef TimeInterval<std::chrono::nanoseconds>  NanoInterval;
typedef TimeInterval<std::chrono::microseconds>  MicroInterval;
typedef TimeInterval<std::chrono::seconds>  SecondsInterval;


} // vavava

#endif