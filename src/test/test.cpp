// test.cpp : 定义控制台应用程序的入口点。
//

#include <stdio.h>
#include <iostream>
//#include "test_cmd.h"
#include <boost/program_options.hpp>

namespace po = boost::program_options;

int main(int argc, char* argv[])
{
    //int level;  
    po::options_description desc("Allowed options");  
    desc.add_options()  
        ("help,h", "produce help message")  
        //("help,h", "produce help message")  
        ("compression,c", po::value<int>(), "set compression level")
        ;

    po::variables_map vm;  
    po::store(po::parse_command_line(argc, argv, desc), vm);  
    po::notify(vm);  

    if(vm.count("help"))  
    {  
        std::cout<<desc<<std::endl;  
        return 1;  
    }  

    if(vm.count("compression"))  
    {  
        std::cout<<"compression level was set to "<<vm["compression"].as<int>()<<"."<<std::endl;  
        //cout<<"compression level: "<<level<<endl;  
    }  
    else  
    {  
        std::cout<<"compression level was not set."<<std::endl;  
    }  

    return 0;  
}

