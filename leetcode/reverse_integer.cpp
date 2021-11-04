#include <iostream>
#include <string>
#include <cmath>
#include <math.h>
#include <vector>
using namespace std;

int calcBitNum(int num){
	int gap = 10;
	int count = 1;
	int t = gap;
	while(t <= num)
	{
		count += 1;
		t = pow(gap, count);
	}
	return count;
}

int reverse(int x){
	bool isNag = (x < 0);
	int absX = abs(x);
	int bitNum = calcBitNum(absX);
	cout<<"bitNum "<<bitNum<<endl;
	if(bitNum <=1)
	{
		return x;
	}
	else{
		vector<int> vec;
		int left = absX;
		for(int i = bitNum;i>1;i--)
		{
			int first = left/(pow(10, i-1));
			left = left - pow(10, i-1);
			vec.push_back(first);
		}
		int tail = absX;
		for(int i = 1;i<bitNum;i++)
		{
			tail= tail-(vec[i-1]*pow(10, bitNum-i));
		}
		vec.push_back(tail);
		left = 0;
		for(int i = bitNum;i>0;--i)
		{
			left = left + vec[bitNum-i]*pow(10, i-1);
		}
		cout<<left<<endl;
		return isNag ? (-1)*left:left;
	}
}

int main()
{
	string a;
	cin>>a;
	int num = atoi(a.c_str());
	reverse(123);
	return 0;
}