// test.cpp : 定义控制台应用程序的入口点。
//

#include <iostream>
#include "test_cmd.h"

int main(int argc, char* argv[])
{
    //testtools::TestCommandBase cmd;
    //cmd.Loads(std::string("fuck(a,b,c)"));
    //std::cout<<"name="<<cmd._name<<std::endl;
    //for (auto itr = cmd._params.begin(); itr != cmd._params.end(); ++itr)
    //{
    //    std::cout<<"param:"<<*itr<<std::endl;
    //}
    int count = 21;
    if(argc > 1)
    { 
        count = atoi(argv[1]);
    }
    testtools::StaticCircularQueue<int,10,false> squeue;
    for(int i=0; i < count; ++i)
    {
        auto ptr = squeue.push(i);
        if (!ptr)
        {
            printf("push() -> null \n");
        }
    }
    printf("count=%d\n", squeue.count());
    for(int i=0; i < squeue.count(); ++i)
    {
        printf("%d=%d\n", i, *squeue.get(i));
    }
	return 0;
}

