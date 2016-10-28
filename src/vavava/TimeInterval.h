
#ifndef _VAVAVA_TIME_INTERVAL_H__
#define _VAVAVA_TIME_INTERVAL_H__

#include <cstdint>
#include <boost/chrono.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>



namespace vavava {
// vavava


class TimeInterval
{
    typedef boost::chrono::steady_clock::time_point  time_point_t;
public:
    TimeInterval(void)
    {
        first_ = boost::chrono::high_resolution_clock::now();
    }

    void tick()
    {
        interval_ = get_nanoseconds();
    }

    int64_t get_nanoseconds()
    {
        auto now = boost::chrono::high_resolution_clock::now();
        auto d = now - last_;
        last_ = now;
        return boost::chrono::duration_cast<boost::chrono::nanoseconds>(d).count();
    }

    int64_t get_interval()
    {
        return interval_;
    }

    int64_t get_total_nanoseconds()
    {
        auto now = boost::chrono::high_resolution_clock::now();
        return boost::chrono::duration_cast<boost::chrono::nanoseconds>(now - first_).count();
    }
protected:
    time_point_t last_;
    time_point_t first_;
    int64_t      interval_;
};


} // vavava

#endif