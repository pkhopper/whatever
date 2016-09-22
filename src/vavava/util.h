
#ifndef _VAVAVA_UTILITIES_H__
#define _VAVAVA_UTILITIES_H__


#include <sstream>
#include <string>
#include <iomanip>


namespace vavava
{

    namespace util
    {

        inline std::string hex_dump(const void * ptr, std::size_t len)
        {
            if (ptr && len > 0)
            {
                ::std::ostringstream ss;
                ss.fill('0');
                ss.width(2);
                unsigned char const *b = reinterpret_cast<unsigned char const*>(ptr);
                ss << std::setw(2) << std::hex << (unsigned int)*b;
                auto n = len > 10000 ? 10000: len;
                for (unsigned char const* e=b+n; ++b != e; )
                {
                ss << " " << std::setw(2) << std::hex << (unsigned int)*b;
                }
                if (len > n)
                {
                    ss << "....... out of buf";
                }
                ss << '\0';
                return ss.str();
            }
            if (len <= 0)
            {
                return "err len <= 0";
            }
            else if (!ptr)
            {
                return "err ptr == NULL";
            }
            return "err unknown";
        }

        template<typename T>
        class Singleton
        {
        public:
            static T& Inst()
            {
                static T  _inc;
                return _inc;
            }
        protected:
            Singleton() {}
            Singleton(const Singleton&) {}
        };

        template<typename T>
        T RandomIteger(T mean, T sigma)
        {
            static boost::mt19937 rng(static_cast<unsigned>(std::time(0)));
            boost::uniform_int<T> norm_dist(mean, sigma);
            boost::variate_generator<boost::mt19937&, boost::uniform_int<T> > normal_sampler(rng, norm_dist);
            return normal_sampler();
        }

        class Random_Class
        {
            friend class Singleton<Random_Class>;

        public:
            int Int(int min, int max)
            {
                s_seed=214013*s_seed + 2531011;
                return min+(s_seed ^ s_seed>>15)%(max-min+1);
            }

            float Float(float min, float max)
            {
                s_seed=214013*s_seed + 2531011;
                return min+(s_seed>>16)*(1.0f/65535.0f)*(max-min);
            }

            template<typename T>
            T Iteger(T mean, T sigma)
            {
                RandomIteger<T>(mean, sigma);
            }

        protected:
            Random_Class()
            {
                s_seed = (unsigned int) time(NULL);
            }
            static unsigned int s_seed;
        };

        typedef Singleton<Random_Class>  Random;

        // data lock
        struct DataLock 
        {
            int count;

            bool IsLocked()
            {
                return count != 0;
            }

            DataLock() : count(0) 
            {

            }
        };
        struct DataLockGuard
        {
            DataLockGuard(DataLock& l) : l_(l)
            {
                l_.count++;
            }
            ~DataLockGuard()
            {
                l_.count--;
            }
            DataLock& l_;
        };
    }


} // vavava

#endif
