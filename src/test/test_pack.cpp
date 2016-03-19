//// test.cpp : 定义控制台应用程序的入口点。
////
//
//#include <stdio.h>
//#include <iostream>
////#include "test_cmd.h"
//#include <boost/program_options.hpp>
//
//// pragma_directives_pack_2.cpp
//// compile with: /W1 /c
//#pragma pack()   // n defaults to 8; equivalent to /Zp8
//#pragma pack(show)   // C4810
//#pragma pack(4)   // n = 4
//#pragma pack(show)   // C4810
//#pragma pack(push, r1, 16)   // n = 16, pushed to stack
//#pragma pack(show)   // C4810
//#pragma pack(pop, r1, 2)   // n = 2 , stack popped
//#pragma pack(show)   // C4810
//#pragma pack()
//#pragma pack(show)   // C4810
//
//#pragma pack(1)
//class A
//{
//
//};
//
//class Tag
//{
//
//};
//
//class B : public A
//{
//public:
//    int a;
//};
//
//class C : public B, public Tag
//{
//public:
//    int b;
//};
//#pragma pack()
//
//int main(int argc, char* argv[])
//{
//
//    A a;
//    B b;
//    C c;
//    c.a = 1;
//    c.b = 2;
//    printf("%u,%u,%u", sizeof(a),sizeof(b),sizeof(c));
//
//    if (__alignof(C) == 1)
//        printf("yes\n");
//    else
//        printf("no\n");
//
//    return 0;
//}
//
