#include <iostream>

#include "FastStr.h"
typedef TFastStr<char, 10> fast_string;

void show(const fast_string& fs)
{
    std::cout<<fs.c_str()<<" "<<fs.length()<<" "<<fs.capacity()<<std::endl;
}

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

int main()
{
    test2();
    return 0;
}
