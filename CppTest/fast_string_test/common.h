#ifndef _FST_COMMON_H_
#define _FST_COMMON_H_

#include <iostream>
#include "FastStr.h"
typedef TFastStr<char, 10> fast_string;

void show(const fast_string& fs)
{
    std::cout<<fs.c_str()<<" "<<fs.length()<<" "<<fs.capacity()<<" "<<(void*)fs.c_str()<<std::endl;
}


#endif