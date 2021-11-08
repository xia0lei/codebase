#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <string.h>
using namespace std;

std::map<string, int> dict;
int revert(const string& str){
    int count = 0;
    int sum = 0;
    const char* sz = str.c_str();
    int max = strlen(sz);
    cout <<sz<<" max "<<max<<endl;
    stringstream stream;
    while(count <=max)
    {
        char ch = *(sz+count);
        cout <<"1 "<<ch<<endl;
        int cursor = count;
        if(ch == 'I' || ch == 'C' || ch == 'X')
        {
            stream<<ch;
            cursor += 1;
            char nCh = *(sz+cursor);
            stream <<nCh;
            std::map<string, int>::const_iterator iter = dict.find(stream.str());
            if(iter != dict.end())
            {
                sum += iter->second;
                count = cursor + 1;
                stream.str("");
                continue;
            }
            else{
                stream.str("");
                stream<<ch;
                std::map<string, int>::const_iterator iter = dict.find(stream.str());
                sum += iter->second;
                count += 1;
            }
        }
        else{
            stream << ch;
            map<string, int>::const_iterator it = dict.find(stream.str());
            if(it != dict.end())
            {
                sum += it->second;
            }
            count += 1;
        }
        stream.str("");
    }
    return sum;
}

int main(){
    dict.insert(make_pair<string, int>("I", 1));
    dict.insert(make_pair<string, int>("V", 5));
    dict.insert(make_pair<string, int>("X", 10));
    dict.insert(make_pair<string, int>("L", 50));
    dict.insert(make_pair<string, int>("C", 100));
    dict.insert(make_pair<string, int>("D", 500));
    dict.insert(make_pair<string, int>("M", 1000));
    dict.insert(make_pair<string, int>("IV", 4));
    dict.insert(make_pair<string, int>("IX", 9));
    dict.insert(make_pair<string, int>("XL", 40));
    dict.insert(make_pair<string, int>("XC", 90));
    dict.insert(make_pair<string, int>("CD", 400));
    dict.insert(make_pair<string, int>("CM", 900));


    string a;
    cin>>a;
    cout<<revert(a)<<endl;
}
