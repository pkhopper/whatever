#include <iostream>
#include <sstream>
#include <vavava/TimeInterval.h>
#include <vavava/Random.h>
//#include "vavava/util.h"
#include <unordered_map>
#include "test_dump/proto/cpp/mytype.pb.h"
#include <consoleapi.h>
#include "MyCrushDump.h"
#include <DbgHelp.h>


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


bool myfunction (int i, int j) {
    return (i==j);
}

bool myfunction1 (int i, int j) {
    return (i<j);
}

int appmain(int argc, char *argv[]);

int main(int argc, char *argv[]) 
{
    //接管控制台信号
    if(0 == SetConsoleCtrlHandler(MyCMDCtrlHandle , TRUE))
    {
        std::cout << "SetConsoleCtrlHandler failed " << std::endl;
    }
    //Crash处理
    InitialCrushDump(MiniDumpWithFullMemory);
    //AddCrashCallBackFunc(DealWithCrash);//我的处理
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    int ret = appmain(argc, argv);
    google::protobuf::ShutdownProtobufLibrary(); // for memcheck
    return ret;
}

int test_array(std::vector<int>& ref, int count)
{
    vavava::NanoInterval t;
    std::stringstream ss;
    ss << "array: ";

    auto datas = new int[ref.size()];
    int i=0;
    t.tick();
    for (auto it=ref.begin(); it != ref.end(); ++it)
    {
        datas[i++] = *it;
    }
    t.tick();
    ss << t.get_interval();

    auto a1 = t.get_interval();
    t.tick();
    for (int round=0; round < count; ++round)
    {
        for (int find=0; find < ref.size(); ++find)
        {
            for (int i=0; i < ref.size(); ++i)
            {
                if (datas[i] == find) break;
            }
        }
    }
    t.tick();
    ss << ", " << t.get_interval() << ", " << t.get_interval() / (count * ref.size() * 1.1) << std::endl;

    std::cout << ss.str();
    return 0;
}

int test_vector(std::vector<int>& ref, int count)
{
    vavava::NanoInterval t;
    std::stringstream ss;
    ss << "vector: ";

    std::vector<int> datas;
    t.tick();
    for (auto it=ref.begin(); it != ref.end(); ++it)
    {
        datas.push_back(*it);
    }
    t.tick();
    ss << t.get_interval();

    auto a1 = t.get_interval();
    t.tick();
    for (int round=0; round < count; ++round)
    {
        for (int find=0; find < ref.size(); ++find)
        {
            for (int i=0; i < ref.size(); ++i)
            {
                if (datas.at(i) == find) break;
            }
        }
    }
    t.tick();
    ss << ", " << t.get_interval() << ", " << t.get_interval() / (count * ref.size() * 1.1) << std::endl;

    std::cout << ss.str();
    return 0;
}

int test_map(std::vector<int>& ref, int count)
{
    vavava::NanoInterval t;
    std::stringstream ss;
    ss << "map: ";

    std::unordered_map<int, int> datas;
    t.tick();
    for (auto it=ref.begin(); it != ref.end(); ++it)
    {
        datas.insert(std::make_pair(*it, *it));
    }
    t.tick();
    ss << t.get_interval();


    t.tick();
    for (int round=0; round < count; ++round)
    {
        for (int find=0; find < ref.size(); ++find)
        {
            auto tmp = datas.find(find);
        }
    }
    t.tick();
    ss << ", " << t.get_interval() << ", " << t.get_interval() / (count * ref.size() * 1.1) << std::endl;
    std::cout << ss.str();
    return 0;
}

int test_map1(std::vector<int>& ref, int count)
{
    vavava::NanoInterval t;
    std::stringstream ss;
    ss << "map1: ";

    std::map<int, int> datas;
    t.tick();
    for (auto it=ref.begin(); it != ref.end(); ++it)
    {
        datas.insert(std::make_pair(*it, *it));
    }
    t.tick();
    ss << t.get_interval();


    t.tick();
    for (int round=0; round < count; ++round)
    {
        for (int find=0; find < ref.size(); ++find)
        {
            auto tmp = datas.find(find);
        }
    }
    t.tick();
    ss << ", " << t.get_interval() << ", " << t.get_interval() / (count * ref.size() * 1.1) << std::endl;
    std::cout << ss.str();
    return 0;
}

int test_list(std::vector<int>& ref, int count)
{
    vavava::NanoInterval t;
    std::stringstream ss;
    ss << "list: ";

    std::list<int> datas;
    t.tick();
    for (auto it=ref.begin(); it != ref.end(); ++it)
    {
        datas.push_back(*it);
    }
    t.tick();
    ss << t.get_interval();

    for (int round=0; round < count; ++round)
    {
        for (int find=0; find < ref.size(); ++find)
        {
            for (auto it=datas.begin(); it != datas.end(); ++it)
            {
                if (*it == find)
                {
                    break;
                }
            }
        }
    }
    t.tick();
    ss << ", " << t.get_interval() << ", " << t.get_interval() / (count * ref.size() * 1.1) << std::endl;
    std::cout << ss.str();
    return 0;
}

int appmain(int argc, char *argv[])
{
    int count = atoi(argv[1]);
    int round = atoi(argv[2]);

    std::vector<int> cases;
    for (int i=0; i < count; ++i)
    {
        cases.push_back(vavava::random::Random::Inst().rand_int<int>(1, 10000000));
    }
    test_array(cases, round);
    test_vector(cases, round);
    test_list(cases, round);
    test_map(cases, round);
    test_map1(cases, round);
    return 0;

    //std::map<int, int> kk, cc;
    //kk.insert(std::make_pair(1, 1));
    //kk.insert(std::make_pair(1, 2));
    //kk.insert(std::make_pair(1, 3));
    //kk.insert(std::make_pair(1, 4));
    //kk.insert(std::make_pair(1, 5));
    //for (auto it=kk.begin(); it != kk.end(); ++it)
    //{
    //    cc.swap(kk);
    //    cc.insert(std::make_pair(1, 6));
    //    kk.erase(it);
    //}

    //return 0;

    // test thread
    //return test_WorkThread(argc, argv, gRunning);

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

