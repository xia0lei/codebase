#include <iostream>

#include "FastStr.h"
typedef TFastStr<char, 128> fast_string;
int main()
{
    fast_string fs("hello-world");
    std::cout<<fs.c_str()<<" "<<fs.length()<<" "<<fs.capacity()<<std::endl;
    return 0;
}
