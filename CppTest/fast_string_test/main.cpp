#include "common.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
void test1()
{
    fast_string fs("hello-world");
    show(fs);
}

void test2()
{
    const char* s1 = "hello";
    const char* s2 = "world";

    fast_string fs(s1, 1, s2, 100);
    show(fs);
}

void test3()
{
    fast_string fs1("aaaaaaaaaaaaaaaaaaaa20");
    show(fs1);
    fast_string fs2;
    fs2 = fs1;
    show(fs2);
}

void test4()
{
    fast_string fs1("aaaaaaaaaaaaaaaaaaaa20");
    show(fs1);
    fast_string fs2("aaaaaaaaaa");
    fs2 = fs1;
    show(fs2);
}

void test_bench()
{
    const int count = 10000000;
    auto startTime = clock();
    for(int i = 0;i<count;i++)
    {
        std::string s(std::to_string(i).c_str());
    }
    auto total_t = (double)(clock() - startTime)/CLOCKS_PER_SEC;
    std::cout<<total_t<<""<<total_t*1000<<std::endl;

    startTime = clock();
    for(int i = 0;i<count;i++)
    {
        fast_string s(std::to_string(i).c_str());
    }
    total_t = (double)(clock() - startTime)/CLOCKS_PER_SEC;
    std::cout<<total_t<<""<<total_t*1000<<std::endl;

}

void test999999()
{
    char stack[10];
    stack[0];
    std::cout<<stack<<std::endl;

    char destStack[10] = {'h', 'e', 'l','l','o','w','o','r','l','d'};
    memcpy(destStack, stack, 1);
    std::cout<<sizeof(destStack)<<" "<<destStack<<std::endl;
}

int main()
{
    test3();
    return 0;
}
