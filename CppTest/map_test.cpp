#include <iostream>
#include <map>
#include <vector>
using namespace std;

int main(int agc, char** args){
	cout << "Hello World\n"<<endl;

	map<int, vector<int>> map1;
	map1[1].push_back(1);
	map1[1].push_back(2);
	for(auto it = map1.begin();it!=map1.end();it++)
	{
		cout<<"key "<<it->first<<endl;
		vector<int> vec = it->second;
		for(int i = 0;i< vec.size();++i)
		{
			cout<<vec[i]<<endl;
		}
	}
	return 0;
}