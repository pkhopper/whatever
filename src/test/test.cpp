// test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include <iostream>
#include "test_cmd.h"

int main(int argc, char* argv[])
{
    testtools::TestCommandBase cmd;
    cmd.Loads(std::string("fuck(a,b,c)"));
    std::cout<<"name="<<cmd._name<<std::endl;
    for (auto itr = cmd._params.begin(); itr != cmd._params.end(); ++itr)
    {
        std::cout<<"param:"<<*itr<<std::endl;
    }
	return 0;
}

