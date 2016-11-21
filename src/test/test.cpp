#include <iostream>
#include <sstream>
#include <vavava/TimeInterval.h>
//#include "vavava/util.h"
#include <unordered_map>
#include "test_dump/proto/cpp/mytype.pb.h"

int test_dump(int argc, char* argv[]);
int test_dump_performance(int argc, char* argv[]);
int test_pb_reflection(int argc, char* argv[]);
int test_WorkThread(int argc, char* argv[]);



int main(int argc, char *argv[]) 
{
    return test_WorkThread(argc, argv);

    //TestRequiredField test;
    //auto ptr = test.mutable_val();
    //if (ptr)
    //{
    //    ptr->set_id(1);
    //}

    //return 0;

    //return test_WorkThread(argc,  argv);
    
    //int count = 1;

    //for (int i=0; i < 7; ++i, count=count*10)
    //{
    //    vavava::TimeInterval t;
    //    t.tick();
    //    std::unordered_map<int64_t, int> test;
    //    test.rehash(10000000);
    //    t.tick();
    //    std::cout << count << ", " << t.get_interval() / (1000*1000*1000) << "s" << std::endl;
    //}

    //return 0;

    //vavava::util::DataLock lock;
    //vavava::util::DataLockGuard guard(lock);
    //std::cout << lock.count << std::endl;
    //guard.~DataLockGuard();
    //std::cout << lock.count << std::endl;
    //return 0;

    //test_pb_reflection(argc, argv);
    //return 0;

    //test_dump_performance(argc, argv); 
    //return 0;
    
    //std::stringstream ss;
    //vavava::TimeInterval t;
    //t.tick();
    //test_dump(argc, argv);
    //t.tick();
    //ss << t.get_interval();
    //std::cout << ss.str() << std::endl;
    //getchar();
    //return 0;
}

