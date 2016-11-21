
#ifndef _VAVAVA_UTILITIES_SINGLETON_H__
#define _VAVAVA_UTILITIES_SINGLETON_H__


namespace vavava {


namespace util
{

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

    private:
        // ref: http://www.cnblogs.com/liyuan989/p/4264889.html
        class Dummy
        {
        public:
            Dummy()
            {
                Singleton<T>::Inst();
            }
        };

        static Dummy dummy_;
    };
    
    template<typename T>
    typename Singleton<T>::Dummy Singleton<T>::dummy_;

} // util


} // vavava

#endif
