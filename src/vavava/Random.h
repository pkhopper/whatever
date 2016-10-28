#ifndef _VAVAVA_RANDOM_H__
#define _VAVAVA_RANDOM_H__

#include "ignore_warnings.h"
#include <boost/random.hpp>
#include <boost/thread.hpp>
#include <boost/core/noncopyable.hpp>
#include "Singleton.h"

namespace vavava {

namespace random
{

    template<class T = boost::rand48>
    class RandomEnable
    {
    public:
        RandomEnable(int seed) :m_rand(seed)
        {

        }

        template<typename T>
        T random_int(T min, T max)
        {
            boost::uniform_int<T> ui(min,max);
            return ui(m_rand);
        }

        int random_int(int min, int max)
        {
            boost::uniform_int<> ui(min,max);
            return ui(m_rand);
        }

        double random_01()
        {
            static boost::uniform_01<> ui;
            return ui(m_rand);
        }

        double random_double(double min, double max)
        {
            boost::uniform_real<> ui(min, max);
            return ui(m_rand);
        }

    private:
        T m_rand;
    };


    //È«¾ÖËæ»ú
    class RandomUniq : public boost::noncopyable
    {
        friend class vavava::util::Singleton<RandomUniq>;
    public:
        template<typename T>
        T rand_int(T min, T max)
        {
            auto ptr = get_thread_data_ptr_();
            if (ptr)
            {
                return ptr->random_int<T>(min, max);
            }
            return min;
        }

        int rand_int(int min, int max)
        {
            auto ptr = get_thread_data_ptr_();
            if (ptr)
            {
                return ptr->random_int(min, max);
            }
            return min;
        }

        double rand_01()
        {
            auto ptr = get_thread_data_ptr_();
            if (ptr)
            {
                return ptr->random_01();
            }
            return 0;
        }

        double rand_double(double min, double max)
        {
            auto ptr = get_thread_data_ptr_();
            if (ptr)
            {
                return ptr->random_double(min, max);
            }
            return min;
        }

    protected:
        RandomEnable<boost::mt19937>* get_thread_data_ptr_()
        {
            RandomEnable<boost::mt19937> *pRng = m_rand.get();

            if (pRng) 
                return pRng;

            m_rand.reset(new RandomEnable<boost::mt19937>(static_cast<int>(std::time(nullptr))));
            return m_rand.get();
        }

    protected:
        boost::thread_specific_ptr< RandomEnable<boost::mt19937> >   m_rand;
    };

    typedef vavava::util::Singleton<RandomUniq>  Random;

} // random

} // vavava

#endif
