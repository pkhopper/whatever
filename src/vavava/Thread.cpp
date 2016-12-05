#include "ignore_warnings.h"
#include <string>
#include "Thread.h"
#include "TimeInterval.h"


using namespace vavava;
using namespace vavava::thread;



struct TestTask : public vavava::thread::Task::ITask
{
    typedef vavava::thread::TaskPool<TestTask>  dataCtrl_t;
    int  tag;
    bool done;
    dataCtrl_t*  pCtrl;

    TestTask() : pCtrl(NULL)
    {
        //  逻辑上pop后一定会重新初始化一次
    }
    TestTask(int t, dataCtrl_t* ctrl)
        : tag(t), done(false), pCtrl(ctrl)
    {

    }
    virtual int run(void * pThisThread)
    {
        done = true;
        if (pCtrl)
        {
            pCtrl->doneTask(this);
        }
        return 0;
    }
};


class TestContainer
{
public:
    int init(int num)
    {
        count = 0;
        return thread_pool_.init(num);
    }
    int start()
    {
        return thread_pool_.start();
    }
    int shutdown()
    {
        return thread_pool_.shutdown();
    }
    int push(int tag)
    {
        auto ptr = task_pool_.allocTask();
        if (ptr)
        {
            new (ptr) TestTask(tag, &task_pool_);
        }
        return thread_pool_.push(ptr);
    }
    int tick()
    {
        auto ptr = task_pool_.peekDoneTask();
        if (ptr)
        {
            task_pool_.freeTask(ptr);
            count++;
        }
        return 0;
    }
    std::string dbg_string()
    {
        std::stringstream ss;
        ss << task_pool_.dbg_string() << ",procced=" << count;
        return ss.str();
    }
    int count;
protected:
    Threadpool             thread_pool_;
    TestTask::dataCtrl_t   task_pool_;
};


int vavava::thread::test(bool &bRunningFlag, int argc, char* argv[])
{
    int threadNum = 3;
    if (argc > 1)
    {
        threadNum = atoi(argv[1]);
    }

    vavava::TimeInterval t;
    t.tick();
    TestContainer   pool;
    t.tick();
    auto createTime = t.get_interval();
    t.tick();
    pool.init(threadNum);
    t.tick();
    auto initTime = t.get_interval();
    pool.start();

    int count = 0;
    t.tick();
    while (bRunningFlag)
    {
        pool.push(count++);
        pool.tick();
        //boost::this_thread::sleep(boost::posix_time::microseconds(100));
    }
    t.tick();
    std::cout << "shutdown 1" << std::endl << std::flush;
    pool.shutdown();
    std::cout << "shutdown 2, " << std::endl << std::flush;

    std::stringstream ss;
    ss << "=========================================================" << std::endl;
    ss  << pool.dbg_string() << ",count=" << count << "cost=" << t.get_interval() << std::endl;
    ss << "=========================================================" << std::endl;
    std::cout << ss.str() << std::endl;
    return 0;
}


//
//struct   Test
//{
//    Test(int t)
//    {
//        tag = t;
//    }
//    int run(void* pTh)
//    {
//        //if (count % 100000 == 0)
//        //{
//        //    t.tick();
//        //    std::cout << "count, " << count << ", " << t.get_interval() << std::endl;
//        //}
//        //std::cout << "[" << pTh->th_id() << "]" << tag << std::endl;
//        return 0;
//    }
//    int tag;
//};
//
//int vavava::thread::test(bool &bRunningFlag, int argc, char* argv[])
//{
//    int threadNum = 3;
//    if (argc > 1)
//    {
//        threadNum = atoi(argv[1]);
//    }
//    vavava::TimeInterval t;
//    Threadpool< TaskPtr<Test> > pool;
//    pool.init(threadNum);
//    pool.start();
//
//    int count = 1;
//    t.tick();
//    while (bRunningFlag)
//    {
//        pool.push(new Test(count++));
//        //if (count % 100000 == 0)
//        //{
//        //    t.tick();
//        //    std::cout << "count, " << count << ", " << t.get_interval() << std::endl;
//        //}
//        //boost::this_thread::sleep(boost::posix_time::microseconds(100));
//    }
//    t.tick();
//    std::cout << "shutdown 1" << std::endl << std::flush;
//    pool.shutdown();
//    std::cout << "shutdown 2, " << std::endl << std::flush;
//
//    std::stringstream ss;
//    ss << "=========================================================" << std::endl;
//    ss  << ", push=" << count << ", avg=" << t.get_total_nanoseconds() / count << std::endl
//        << ", done=" << count - pool.task_size() << ", avg=" << t.get_total_nanoseconds() / (count - pool.task_size())  << std::endl
//        ;
//    ss << "=========================================================" << std::endl;
//    std::cout << ss.str() << std::endl;
//    return 0;
//}