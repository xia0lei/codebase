#include<iostream>
using namespace std;

int test()
{
	static int i = 0;
	cout<<"i "<<i<<endl;
	int j = i++;
	return j;
}

int main()
{
	for(int i = 0; i<10; i++)
	{
		int j = test();
		cout<<"j "<<j<<endl;
	}
	return 0;
}