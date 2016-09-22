#include <boost\lexical_cast.hpp>
#include <string>
#include "WorkThread.h"


using namespace vavava;
using namespace vavava::thread;


void SetThreadName(unsigned long thID, const char* thName)
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

WorkThread::WorkThread()
{
     cleanup_();
}

WorkThread::~WorkThread()
{
   shutdown();
}

int WorkThread::start()
{
    boost::mutex::scoped_lock l(mt_th_);
    if (running_)
        return -1;

    if (th_)
    {
        delete th_;
        th_ = NULL;
    }

    try
    {
        set_stop_ = false;
        running_ = true;
        th_ = new boost::thread(boost::bind(&WorkThread::run_, this));
        return 0;
    }
    catch (...)
    {
    	running_ = false;
        set_stop();
        return -2;
    }
}

int WorkThread::add(Work& w)
{
    if (w.run.empty())
    {
        return -1;
    }
    boost::mutex::scoped_lock l(mt_wk_);
    works_.push_back(w);
    return 0;
}

void WorkThread::set_stop()
{
    set_stop_ = true;
}

int WorkThread::join(int timeout)
{
    int ret = -1;
    for (int i=0; timeout <= 0 || i < timeout; ++i)
    {
        if (!running_)
        {
            ret = 0;
            break;
        }
        else if (timeout > 0 && i > timeout)
        {
            boost::mutex::scoped_lock l(mt_th_);
            ret = -2;
            break;
        }
        boost::this_thread::sleep(boost::posix_time::seconds(1));
    }

    //{
    //    boost::mutex::scoped_lock l(mt_th_);

    //}
    return 0;
}

int WorkThread::shutdown(int timeout)
{
    set_stop();
    return join(timeout);
}

bool WorkThread::is_set_stop() const
{
    return set_stop_;
}

std::string WorkThread::th_id()
{
    boost::mutex::scoped_lock l(mt_th_);
    return th_id_;
}

void WorkThread::cleanup_()
{
    boost::mutex::scoped_lock l(mt_th_);
    th_ = NULL;
    running_ = false;
    set_stop_ = true;
    exit_on_empty_ = true;
    last_run_ = 0;
    th_id_ = "";
}

int WorkThread::run_()
{
    SetThreadName(-1, "work-thread");

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
        while (!is_set_stop())
        {
            Work work;
            bool isContinue = false;

            {
                boost::mutex::scoped_lock l(mt_wk_);
                if (works_.size() == 0)
                {
                    if (exit_on_empty_)
                        break;
                    isContinue = true;
                }
                else
                {
                    work = *works_.begin();
                    works_.pop_front();
                }
            }

            if (isContinue)
            {
                boost::this_thread::sleep(boost::posix_time::seconds(1));
                continue;
            }

            if (!work.run.empty())
            {
                auto ret = work.run(&work, this);
                if (work.GetType() == WorkType::WT_NONSTOP)
                {
                    boost::mutex::scoped_lock l(mt_wk_);
                    works_.push_back(std::move(work));
                }
            }

            //////////////
        }
    }
    catch (std::exception& e)
    {
    	
    }
    catch (...)
    {

    }

LB_RUN_CLEAN:

    {
        boost::mutex::scoped_lock l(mt_th_);
        running_ = false;
        set_stop();
    }
    return 0;
}
