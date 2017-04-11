#include <vavava/Random.h>
#include <vavava/Thread.h>




int test_WorkThread(int argc, char* argv[], bool& running)
{
    vavava::thread::test(running, argc, argv);
    return 0;
}
