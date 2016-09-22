
#ifndef _VAVAVA_WORK_THREAD_H__
#define _VAVAVA_WORK_THREAD_H__


#include <sstream>
#include <string>
#include <iomanip>
#include <boost/function.hpp>
#include <boost/atomic/atomic.hpp>
#include <boost/thread/thread.hpp>



namespace vavava
{

    namespace thread
    {

        class WorkThread;

        enum WorkType
        {
            WT_ONCE,
            WT_NONSTOP,
        };

        class Work
        {
            typedef boost::function<int(Work*, WorkThread*)> work_func_t;
        public:
            work_func_t run;

            // args

            Work() : type_(WT_ONCE)
            {

            }

            Work(const Work& w)
            {
                run = w.run;
                type_ = w.GetType();
            }

            WorkType GetType() const
            {
                return type_;
            }

            void SetType(WorkType t)
            {
                type_ = t;
            }

        protected:
            WorkType type_;
        };


        class WorkThread
        {
        public:
            WorkThread();
            ~WorkThread();
            int start();
            int add(Work&);
            void set_stop();
            int join(int timeout=-1);
            int shutdown(int timeout=-1);
            bool is_set_stop() const;
            std::string th_id();

        protected:
            WorkThread(const WorkThread&) {}
            void cleanup_();
            int run_();

        protected:
            boost::mutex          mt_th_;
            boost::thread       * th_;

            boost::mutex          mt_wk_;
            std::list<Work>       works_;
            
            boost::atomic<bool>   running_;
            boost::atomic<bool>   set_stop_;
            boost::atomic<bool>   exit_on_empty_;
            time_t                last_run_;
            std::string           th_id_;
        };
    }

} // vavava

#endif
