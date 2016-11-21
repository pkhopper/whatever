#ifndef _VAVAVA_THREAD_POOL_H__
#define _VAVAVA_THREAD_POOL_H__

#include "ignore_warnings.h"
#include <sstream>
#include <string>
#include <iomanip>
#include <boost/function.hpp>
#include <boost/atomic/atomic.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/condition.hpp>
#include "Thread.h"



namespace vavava
{

    namespace thread
    {

        class Threadpool
        {
        public:
            int init(int minThreadNum, int maxThreadNum, int maxTaskNum)
            {

            }
        protected:
            boost::mutex         mt_task_;
            std::list<Task>      tasks_;
            boost::mutex         mt_notify_;
            boost::condition     notify_;
            boost::thread_group  pool_;
        }



    } // thread

} // vavava

#endif
