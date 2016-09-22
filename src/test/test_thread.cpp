#include <vavava/Random.h>
#include <vavava/WorkThread.h>


vavava::Random gRandom;

int thread_run(vavava::thread::Work* pWork, vavava::thread::WorkThread* pTh)
{
    std::cout << pTh->th_id() << ", " << gRandom.rand_int(1, 1000) << std::endl;
    return 0;
}


int test_WorkThread(int argc, char* argv[])
{
    std::vector< std::shared_ptr<vavava::thread::WorkThread> >  threads;

    for (int i=0; i < 10; ++i)
    {
        auto ptr = std::shared_ptr<vavava::thread::WorkThread>(new vavava::thread::WorkThread);
        threads.push_back(ptr);
    }

    for (auto it=threads.begin(); it != threads.end(); ++it)
    {
        auto ptr = *it;
        vavava::thread::Work  w;
        w.run = thread_run;  // boost::bind(&run, _1, _2);
        w.SetType(vavava::thread::WT_NONSTOP);
        ptr->add(w);
        ptr->start();
    }

    for (auto it=threads.begin(); threads.begin() != threads.end(); )
    {
        auto ptr = *it;
        if (ptr->join(10) != -2)
        {
            it = threads.erase(it);
        }
        else
        {
            ++it;
        }

        if (it == threads.end())
        {
            it = threads.begin();
        }
    }
    return 0;
}
