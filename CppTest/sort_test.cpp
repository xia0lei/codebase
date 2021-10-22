#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Item{
    int m_index;
    int m_seq;

    public:

    Item(int index, int seq)
    {
        m_index = index;
        m_seq = seq;
    }
};

bool compare(const Item& a, const Item& b)
{
    return a.m_seq < b.m_seq;
}

int main()
{

    std::vector<Item> vec;
    vec.push_back(Item(1, 10));
    vec.push_back(Item(2, 30));
    vec.push_back(Item(3, 30));
    sort(vec.begin(), vec.end(), compare);
    for(auto it = vec.begin();it != vec.end();++it)
    {
        cout<<it->m_index<<" "<<it->m_seq<<endl;
    }
    return 0;
}
