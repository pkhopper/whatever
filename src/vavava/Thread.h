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
#include <boost/lexical_cast.hpp>



namespace vavava
{

    namespace thread
    {

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



        struct Task
        {
            struct ITask 
            {
                virtual int run(void *) = 0;
            };

            ITask* ptr_;

            Task() : ptr_(NULL)
            {

            }
            Task(ITask* ptr) : ptr_(ptr)
            {

            }
            bool valid()
            {
                return ptr_ != NULL;
            }
            int operator()(void* pThread)
            {
                if (valid())
                {
                    return ptr_->run(pThread);
                }
                return -1;
            }
        };



        class Threadpool : boost::noncopyable
        {
        public:
            typedef std::list<Task>  task_list_t;

            class Thread : boost::noncopyable
            {
            public:

                Thread(Threadpool& ref)
                    : poolRef_(ref),
                    running_(false),
                    set_stop_(true),
                    exit_on_empty_(true),
                    pTh_(NULL),
                    last_run_(0),
                    th_id_("")
                {

                }

                ~Thread()
                {
                    if (pTh_)
                    {
                        delete pTh_;
                        pTh_ = NULL;
                    }
                }

                int start()
                {
                    boost::mutex::scoped_lock l(mt_th_);
                    if (running_)
                        return -1;

                    if (pTh_)
                    {
                        delete pTh_;
                        pTh_ = NULL;
                    }

                    try
                    {
                        set_stop_ = false;
                        running_ = true;
                        pTh_ = new boost::thread(boost::bind(&Threadpool::Thread::run_, this));
                        return 0;
                    }
                    catch (...)
                    {
                        running_ = false;
                        set_stop();
                        return -2;
                    }
                }

                void set_stop()
                {
                    set_stop_ = true;
                }

                int join(int timeout=-1)
                {
                    if (pTh_->joinable())
                    {
                        if (timeout < 0)
                        {
                            pTh_->join();
                        }
                        else if (!pTh_->timed_join(boost::posix_time::microseconds(timeout)))
                        {
                            return TE_Timeout;
                        }
                        return TE_Ok;
                    }
                    return TE_Unknown;
                }

                bool is_set_stop() const
                {
                    return set_stop_;
                }

                std::string get_thread_id()
                {
                    boost::mutex::scoped_lock l(mt_th_);
                    return th_id_;
                }

            protected:

                int run_()
                {
                    {
                        boost::mutex::scoped_lock l(mt_th_);
                        if (is_set_stop() || !running_)
                        {
                            goto LB_RUN_CLEAN;
                        }
                        th_id_ = boost::lexical_cast<std::string>(boost::this_thread::get_id());
                    }

                    try
                    {
                        int count = 0;
                        task_list_t tasks;
                        while (!is_set_stop())
                        {
                            poolRef_.block_current_thread_until_notified();
                            while (!is_set_stop())
                            {
                                poolRef_.pull_tasks(tasks);
                                if (tasks.size() <= 0)
                                {
                                    break;
                                }
                                for (auto it=tasks.begin(); !is_set_stop() && it != tasks.end(); )
                                {
                                    (*it)(this);
                                    it = tasks.erase(it);
                                }
                            }
                        } // while
                    }
                    catch (std::exception& e)
                    {
                        std::cout << e.what() << std::endl;
                        assert(0);
                    }
                    catch (...)
                    {
                        std::cout << "unknown exception" << std::endl;
                        assert(0);
                    }

LB_RUN_CLEAN:
                    std::cout << "thread finished: " << get_thread_id() << std::endl << std::flush;

                    {
                        boost::mutex::scoped_lock l(mt_th_);
                        running_ = false;
                        set_stop();
                    }
                    return 0;
                }

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

        public:
            Threadpool()
            {

            }

            ~Threadpool()
            {
                if (pool_.size() > 0)
                {
                    for (auto it=pool_.begin(); it != pool_.end(); )
                    {
                        auto pThread = *it;
                        if (pThread)
                        {
                            delete pThread;
                        }
                        it = pool_.erase(it);
                    }
                }
            }

            int init(int num)
            {
                if (num > 0)
                {
                    for (int i=0; i < num; ++i)
                    {
                        pool_.push_back(new Thread(*this));
                    }
                    return 0;
                }
                return -1;
            }

            int start()
            {
                int ret = -1;
                for (auto it=pool_.begin(); it != pool_.end(); ++it)
                {
                    auto pThread = *it;
                    if (pThread)
                    {
                        if (pThread->start() != 0)
                        {
                            ret = shutdown();
                            return -1;
                        }
                    }
                }
                return 0;
            }

            int join()
            {
                while (pool_.size() > 0)
                {
                    for (auto it=pool_.begin(); it != pool_.end(); )
                    {
                        auto pThread = *it;
                        if (pThread)
                        {
                            auto ret = pThread->join(300);
                            switch (ret)
                            {
                            case TE_Timeout:
                                ++it;
                                continue;
                            case TE_Ok:
                            case TE_Unknown:
                                break;
                            }
                        }
                        it = pool_.erase(it);
                        if (pThread)
                        {
                            delete pThread;
                        }
                    }
                }
                return TE_Ok;
            }

            int shutdown(int timeout=-1)
            {
                try
                {
                    auto now = time(NULL);
                    for (auto it=pool_.begin(); it != pool_.end(); ++it)
                    {
                        auto pThread = *it;
                        if (pThread)
                        {
                            pThread->set_stop();
                        }
                    }
                    notify_.notify_all();

                    if (timeout < 0)
                    {
                        for (auto it=pool_.begin(); it != pool_.end(); ++it)
                        {
                            auto pThread = *it;
                            if (pThread)
                            {
                                pThread->join();
                                delete pThread;
                            }
                        }
                        pool_.clear();
                        return TE_Ok;
                    }

                    while (time(NULL) - now <= timeout*1000)
                    {
                        for (auto it=pool_.begin(); it != pool_.end(); )
                        {
                            auto pThread = *it;
                            if (pThread)
                            {
                                auto ret = pThread->join(300);
                                switch (ret)
                                {
                                case TE_Timeout:
                                    ++it;
                                    continue;
                                case TE_Ok:
                                case TE_Unknown:
                                    break;
                                }
                            }
                            it = pool_.erase(it);
                            if (pThread)
                            {
                                delete pThread;
                            }
                        }
                    }

                    if (pool_.size() > 0)
                    {
                        for (auto it=pool_.begin(); it != pool_.end(); ++it)
                        {
                            auto ptr = *it;
                            if (ptr)
                            {
                                delete ptr;
                            }
                        }
                        pool_.clear();
                        return TE_Unknown;
                    }
                    return TE_Ok;
                }
                catch (...)
                {
                }
                return TE_Exception;
            }

            int push(Task task)
            {
                if (task.valid())
                {
                    {
                        boost::unique_lock<boost::mutex> l(mt_task_);
                        tasks_.push_back(std::move(task));
                    }
                    notify_.notify_one();
                    return 0;
                }
                return -1;
            }

            std::size_t task_size() // for test
            {
                boost::unique_lock<boost::mutex> l(mt_task_);
                return tasks_.size();
            }

        protected:
            void block_current_thread_until_notified()
            {
                boost::unique_lock<boost::mutex> l(mt_notify_);
                notify_.wait(l);
            }

            Task pull_task()
            {
                boost::unique_lock<boost::mutex> l(mt_task_);
                if (tasks_.size() > 0)
                {
                    auto task = *tasks_.begin();
                    tasks_.pop_front();
                    return task;
                }
                return Task();
            }

            void pull_tasks(task_list_t& out)
            {
                boost::unique_lock<boost::mutex> l(mt_task_);
                if (tasks_.size() > 0)
                {
                    out.swap(tasks_);
                }
            }

        protected:
            std::vector<Thread*>  pool_;
            boost::mutex          mt_task_;
            task_list_t           tasks_;
            boost::mutex          mt_notify_;
            boost::condition      notify_;
        };



        // 线程之间共享任务列表 [11/24/2016 liletian]
        template<typename TaskType>
        class TaskPool
        {
        public:
            TaskPool()
            {
                resize(5*10000);
            }
            void resize(int capacity)
            {
                vct_.resize(capacity);
                for (std::size_t i=0; i < vct_.size(); ++i)
                {
                    idel_.push_back(vct_.data() + i);
                }
            }
            TaskType* allocTask()
            {
                boost::mutex::scoped_lock l(idel_m_);
                if (idel_.begin() != idel_.end())
                {
                    auto ptr = *idel_.begin();
                    assert(ptr);
                    idel_.pop_front();
                    return ptr;
                }
                assert(0);
                return NULL;
            }
            void freeTask(TaskType* ptr)
            {
                if (_check_ptr(ptr))
                {
                    boost::mutex::scoped_lock l(idel_m_);
                    idel_.push_front(ptr);
                }
            }
            void doneTask(TaskType* ptr)
            {
                if (_check_ptr(ptr))
                {
                    boost::mutex::scoped_lock l(done_m_);
                    done_.push_front(ptr);
                }
            }
            TaskType* peekDoneTask()
            {
                boost::mutex::scoped_lock l(done_m_);
                if (done_.begin() != done_.end())
                {
                    auto ptr = *done_.begin();
                    assert(ptr);
                    done_.pop_front();
                    total_ ++;
                    return ptr;
                }
                return NULL;
            }
            void peekDoneTasks(std::list<TaskType*>& out)
            {
                boost::mutex::scoped_lock l(done_m_);
                if (done_.size() > 0)
                {
                    out.swap(done_);
                    total_ += out.size();
                }
            }

            std::string dbg_string()
            {
                std::size_t idelSize = 0;
                std::size_t doneSize = 0;
                {
                    boost::mutex::scoped_lock l(idel_m_);
                    idelSize = idel_.size();
                }
                {
                    boost::mutex::scoped_lock l(done_m_);
                    doneSize = done_.size();
                }
                std::stringstream ss;
                ss << "idel=" << idelSize << ",done=" << doneSize << ",total=" << vct_.size();
                return ss.str();
            }

            int dbg_total()
            {
                boost::mutex::scoped_lock l(done_m_);
                return total_;
            }

        protected:
            bool _check_ptr(const TaskType* ptr) const
            {
                assert(vct_.data() <= ptr && ptr < vct_.data() + vct_.size());
                return vct_.data() <= ptr && ptr < vct_.data() + vct_.size();
            }
        protected:
            std::vector<TaskType> vct_;
            boost::mutex          idel_m_;
            std::list<TaskType*>  idel_;
            boost::mutex          done_m_;
            std::list<TaskType*>  done_;
            std::size_t           total_; // for test
        };


        int  test(bool &bRunningFlag, int argc, char* argv[]);

    } // thread

} // vavava

#endif
