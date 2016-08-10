#include <iostream>
#include <sstream>
#include <vavava/TimeInterval.h>

int test_dump(int argc, char* argv[]);
int test_dump_performance(int argc, char* argv[]);

int main(int argc, char *argv[]) 
{
    test_dump_performance(argc, argv); 
    return 0;
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

