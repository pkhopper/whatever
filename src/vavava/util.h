
#ifndef _VAVAVA_UTILITIES_H__
#define _VAVAVA_UTILITIES_H__

#include <cstdint>
#include <chrono>


namespace vavava {

namespace util {


    //inline std::string hex_dump(const void * ptr, std::size_t len)
    //{
    //    if (ptr && len > 0)
    //    {
    //        ::std::ostringstream ss;
    //        ss.fill('0');
    //        ss.width(2);
    //        unsigned char const *b = reinterpret_cast<unsigned char const*>(ptr);
    //        ss << std::setw(2) << std::hex << (unsigned int)*b;
    //        auto n = len > 10000 ? 10000: len;
    //        for (unsigned char const* e=b+n; ++b != e; )
    //        {
    //        ss << " " << std::setw(2) << std::hex << (unsigned int)*b;
    //        }
    //        if (len > n)
    //        {
    //            ss << "....... out of buf";
    //        }
    //        ss << '\0';
    //        return ss.str();
    //    }
    //    if (len <= 0)
    //    {
    //        return "err len <= 0";
    //    }
    //    else if (!ptr)
    //    {
    //        return "err ptr == NULL";
    //    }
    //    return "err unknown";
    //}
                
} // util


} // vavava

#endif
