#include <iostream>
#include <set>

int main()
{
    std::set<int> iSet;
    iSet.insert(100);
    iSet.insert(100);

    std::cout<<iSet.count(100)<<std::endl;

    return 0;
}
