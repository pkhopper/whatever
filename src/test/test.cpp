#include <iostream>
#include <sstream>
#include <vavava/TimeInterval.h>
//#include "vavava/util.h"
#include <unordered_map>
#include "test_dump/proto/cpp/mytype.pb.h"
#include <consoleapi.h>


//控制台消息接管
bool gRunning = true;
BOOL WINAPI MyCMDCtrlHandle(DWORD dwCtrlType)
{
    switch(dwCtrlType)
    {
    case CTRL_C_EVENT:
    case CTRL_BREAK_EVENT:
    case CTRL_CLOSE_EVENT:
    case CTRL_LOGOFF_EVENT:
    case CTRL_SHUTDOWN_EVENT:
        {
            MessageBeep(-1);
            gRunning = false;
            Sleep(1000);
            return TRUE;
        }break;
    default:
        return FALSE;
    }
}

int test_dump(int argc, char* argv[], bool& running);
int test_dump_performance(int argc, char* argv[], bool& running);
int test_pb_reflection(int argc, char* argv[], bool& running);
int test_WorkThread(int argc, char* argv[], bool& running);


int main(int argc, char *argv[]) 
{
    //接管控制台信号
    if(0 == SetConsoleCtrlHandler(MyCMDCtrlHandle , TRUE))
    {
        std::cout << "SetConsoleCtrlHandler failed " << std::endl;
    }

    return test_WorkThread(argc, argv, gRunning);

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

