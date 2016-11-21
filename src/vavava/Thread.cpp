#include <boost\lexical_cast.hpp>
#include <string>
#include "Thread.h"
#include "boost\date_time\posix_time\posix_time_duration.hpp"


using namespace vavava;
using namespace vavava::thread;


void vavava::thread::SetThreadName(unsigned long thID, const char* thName)
{
#ifdef WIN32
    const DWORD MS_VC_EXCEPTION = 0x406D1388;

#progma pack(push, 8)

    typedef struct tagTHREADNAME_INFO
    {
        DWORD dwType;
        LPCSTR szName;
        DWORD dwThreadID;
        DWORD dwFlags;
    } THREADNAME_INFO;

#progma pack(pop)

    THREADNAME_INFO INFO;
    INFO.dwType = 0X1000;
    INFO.szName = thName;
    INFO.dwThreadID = thID;
    INFO.dwFlags = 0;

    _try
    {
        RaiseException(MS_VC_EXCEPTION, 0, sizeof(INFO)/sizeof(ULONG_PTR), (ULONG_PTR*)&INFO);
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {

    }

#endif
}

Threadpool::Thread::Thread(Threadpool& ref)
    : poolRef_(ref)
{
    cleanup_();
}

Threadpool::Thread::~Thread()
{
    if (pTh_)
    {
        delete pTh_;
        pTh_ = NULL;
    }
}

int Threadpool::Thread::start()
{
    boost::mutex::scoped_lock l(mt_th_);
    if (running_)
        return -1;

    if (pTh_)
    {
        delete pTh_;
        pTh_ = nullptr;
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

void Threadpool::Thread::set_stop()
{
    set_stop_ = true;
}

int Threadpool::Thread::join(int timeout)
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

bool Threadpool::Thread::is_set_stop() const
{
    return set_stop_;
}

std::string Threadpool::Thread::th_id()
{
    boost::mutex::scoped_lock l(mt_th_);
    return th_id_;
}

void Threadpool::Thread::cleanup_()
{
    boost::mutex::scoped_lock l(mt_th_);
    pTh_ = NULL;
    running_ = false;
    set_stop_ = true;
    exit_on_empty_ = true;
    last_run_ = 0;
    th_id_ = "";
}

int Threadpool::Thread::run_()
{
#ifdef WIN32
    SetThreadName(-1, "work-thread");
#endif

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
        while (true)
        {
            poolRef_.block_current_thread_until_notified();
            if (is_set_stop())
            {
                break;
            }
            auto pTask = poolRef_.pull_task();
            if (pTask)
            {
                pTask->run(pTask, this);
                delete pTask;
            }
        }
    }
    catch (std::exception& e)
    {
        assert(0);
    }
    catch (...)
    {
        assert(0);
    }

LB_RUN_CLEAN:

    {
        boost::mutex::scoped_lock l(mt_th_);
        running_ = false;
        set_stop();
    }
    return 0;
}

int Threadpool::init(int num)
{
    if (num > 0)
    {
        for (int i=0; i < num; ++i)
        {
            pool_.push_back(new Thread(*this));
        }
        return pool_.size();
    }
    return -1;
}

int Threadpool::start()
{
    int count = 0;
    for (auto it=pool_.begin(); it != pool_.end(); ++it)
    {
        auto ptr = *it;
        if (ptr)
        {
            if (ptr->start() == 0)
            {
                count ++;
            }
        }
    }
    return count;
}

int Threadpool::join()
{
    while (pool_.size() > 0)
    {
        for (auto it=pool_.begin(); it != pool_.end(); ++it)
        {
            auto ptr = *it;
            if (ptr)
            {
                auto ret = ptr->join(300);
                switch (ret)
                {
                case TE_Timeout:
                    continue;
                case TE_Ok:
                case TE_Unknown:
                    break;
                }
            }
            it = pool_.erase(it);
            if (ptr)
            {
                delete ptr;
            }
        }
    }
    return TE_Ok;
}

int Threadpool::shutdown(int timeout)
{
    try
    {
        auto now = time(NULL);
        for (auto it=pool_.begin(); it != pool_.end(); ++it)
        {
            auto ptr = *it;
            if (ptr)
            {
                ptr->set_stop();
            }
        }
        notify_.notify_all();

        if (timeout < 0)
        {
            for (auto it=pool_.begin(); it != pool_.end(); ++it)
            {
                auto ptr = *it;
                if (ptr)
                {
                    ptr->join();
                }
            }
            pool_.clear();
            return TE_Ok;
        }

        while (time(NULL) - now <= timeout*1000)
        {
            for (auto it=pool_.begin(); it != pool_.end(); ++it)
            {
                auto ptr = *it;
                if (ptr)
                {
                    auto ret = ptr->join(300);
                    switch (ret)
                    {
                    case TE_Timeout:
                        continue;
                    case TE_Ok:
                    case TE_Unknown:
                        break;
                    }
                }
                it = pool_.erase(it);
                if (ptr)
                {
                    delete ptr;
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
                it = pool_.erase(it);
            }
            return TE_Unknown;
        }
        return TE_Ok;
    }
    catch (...)
    {
    }
    return TE_Exception;
}

int Threadpool::push(ITask* ptr)
{
    if (ptr)
    {
        {
            boost::unique_lock<boost::mutex> l(mt_task_);
            tasks_.push_back(ptr);
        }
        notify_.notify_one();
        return 0;
    }
    return -1;
}

void Threadpool::block_current_thread_until_notified()
{
    boost::unique_lock<boost::mutex> l(mt_notify_);
    notify_.wait(l);
}

Threadpool::ITask* Threadpool::pull_task()
{
    boost::unique_lock<boost::mutex> l(mt_task_);
    if (tasks_.size() > 0)
    {
        auto ptr = *tasks_.begin();
        tasks_.pop_front();
        return ptr;
    }
    return NULL;
}

Threadpool::Threadpool()
{

}

Threadpool::~Threadpool()
{
    if (pool_.size() > 0)
    {
        for (auto it=pool_.begin(); it != pool_.end(); ++it)
        {
            auto ptr = *it;
            if (ptr)
            {
                delete ptr;
            }
            it = pool_.erase(it);
        }
    }
}

struct   Test : public Threadpool::ITask
{
    Test(int t)
    {
        tag = t;
    }
    virtual int run(Threadpool::ITask* pTask,  Threadpool::Thread* pTh)
    {
        std::cout << "[" << pTh->th_id() << "]" << tag << std::endl;
        return 0;
    }
    int tag;
};

int vavava::thread::test(bool &bRunningFlag)
{
    Threadpool pool;
    pool.init(4);
    pool.start();

    int count = 0;
    while (bRunningFlag)
    {
        pool.push(new Test(count++));
        boost::this_thread::sleep(boost::posix_time::microseconds(100));
    }
    pool.join();
    return 0;
}