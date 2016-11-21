#ifndef _VAVAVA_THREAD_H__
#define _VAVAVA_THREAD_H__

#include "ignore_warnings.h"
#include <sstream>
#include <string>
#include <iomanip>
#include <boost/function.hpp>
#include <boost/atomic/atomic.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/condition.hpp>
#include <boost/core/noncopyable.hpp>



namespace vavava
{

    namespace thread
    {

        void SetThreadName(unsigned long thID, const char* thName);

        enum WorkType
        {
            WT_ONCE,
            WT_NONSTOP,
        };

        enum ThreadErr
        {
            TE_Ok        =  0,
            TE_Unknown   = -1,
            TE_Timeout   = -2,
            TE_Exception = -3,
        };

        
        class Threadpool : boost::noncopyable
        {
        public:

            class Thread : boost::noncopyable
            {
            public:
                Thread(Threadpool&);
                ~Thread();
                int start();
                void set_stop();
                int join(int timeout=-1); // ms
                bool is_set_stop() const;
                std::string th_id();

            protected:
                Thread(const Thread& kk) : poolRef_(kk.poolRef_) {}
                Thread &Thread::operator =(const Thread &) {}
                void cleanup_();
                int run_();

            protected:
                Threadpool          &poolRef_;
                boost::atomic<bool>  running_;
                boost::atomic<bool>  set_stop_;
                boost::atomic<bool>  exit_on_empty_;
                boost::mutex         mt_th_;
                boost::thread       *pTh_;
                time_t               last_run_;
                std::string          th_id_;
            };

            struct ITask 
            {
                virtual int run(ITask*, Thread*) = 0;
            };

        public:
            Threadpool();
            ~Threadpool();
            int init(int num);
            int start();
            int join();
            int shutdown(int timeout=-1); // s
            int push(ITask* ptr);

        protected:
            void block_current_thread_until_notified();
            ITask* pull_task();

        protected:
            std::vector<Thread*>  pool_;
            boost::mutex          mt_task_;
            std::list<ITask*>     tasks_;
            boost::mutex          mt_notify_;
            boost::condition      notify_;
        };

        int  test(bool &bRunningFlag);

    } // thread

} // vavava

#endif
