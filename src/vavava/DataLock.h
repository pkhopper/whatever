
#ifndef _VAVAVA_UTILITIES_DATALOCK_H__
#define _VAVAVA_UTILITIES_DATALOCK_H__


namespace vavava
{

    namespace util
    {

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
