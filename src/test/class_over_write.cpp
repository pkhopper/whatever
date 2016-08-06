#include <iostream>

struct A
{
    int a;
    void func()
    {
        a = 1;
    }
};

struct B : public A
{
    int a;
    void func()
    {
        a = 2;
    }
};



int test(int argc, char* argv[])
{
    A kk;
    B kkk;

    kk.func();
    kkk.func();

    A* ptr = static_cast<A*>(&kkk);
    ptr->func();

    std::cout<< std::endl;
    std::cout<< sizeof(kk) << std::endl;
    std::cout<< sizeof(kkk) << std::endl;

    return 0;  
}

