#include <iostream>
#include <thread>
#include <chrono>
#include <stdlib.h>
#include <string.h>


void segv()
{        
    // sigsegv
    int* ptr = 0;
    *ptr = 1;
}

void abrt()
{
    // sigabrt
    char buffer[3];
    strcpy(buffer, "123456");
}

int main(int argc, char *argv[]) 
{
    int cmd;
    std::cin >> cmd;
    switch(cmd)
    {
    case 1: segv(); break;
    case 2: abrt(); break;
    default:
        std::cout << "what u want" << std::endl;
        break;
    }
    return 0;
}

