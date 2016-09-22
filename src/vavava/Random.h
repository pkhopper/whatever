#ifndef _VAVAVA_RANDOM_H__
#define _VAVAVA_RANDOM_H__

#include <boost/random.hpp>
#include <boost/thread.hpp>

namespace vavava
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
class Random
{
public:

    int rand_int(int min, int max)
    {
        return get_gen().random_int(min, max);
    }

    double rand_01()
    {
        return get_gen().random_01();
    }

    double rand_double(double min, double max)
    {
        return get_gen().random_double(min, max);
    }

protected:
    boost::thread_specific_ptr< RandomEnable<boost::mt19937> >   m_rand;

    RandomEnable<boost::mt19937>& get_gen()
    {
        RandomEnable<boost::mt19937> *pRng = m_rand.get();

        if (pRng) 
            return *pRng;

        m_rand.reset(new RandomEnable<boost::mt19937>(std::time(nullptr)));
        return *m_rand.get();
    }
};


} // vavava

#endif
