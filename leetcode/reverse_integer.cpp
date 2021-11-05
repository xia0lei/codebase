#include <iostream>
#include <string>
#include <cmath>
#include <math.h>
#include <vector>
using namespace std;

int calcBitNum(long num){
	int gap = 10;
	int count = 1;
	long t = gap;
	while(t <= num)
	{
		count += 1;
		t *= 10;/*pow(gap, count)*/
        cout<<"t"<<t<<endl;
	}
	return count;
}

int reverseVec(const vector<int>& vec)
{
    int size = vec.size();
    long value = 0;
    for(int i = 1; i<= size;i++){
        value += vec[size - i]*pow(10, size - i);
        cout << "i "<<i<<"  "<<value<<endl;
    }
    if(value >= (-1)*pow(2, 31) &&value <=(pow(2, 31)-1))
        return value;
    else
        return 0;
}

int reverse(int x){
    if(x<((-1)*pow(2, 31))|| x >(pow(2,31)-1))
        return 0;

	bool isNag = (x < 0);
    //int 的范围是-(2^15=-1) (2^15-1)
	long absX = fabs(x);
    cout<<"absX "<<absX<<endl;
	int bitNum = calcBitNum(absX);
	cout<<"bitNum "<<bitNum<<endl;
	if(bitNum <=1)
	{
		return x;
	}
	else{
		vector<int> vec(bitNum, 0);
		long left = absX;
		for(int i = bitNum;i>1;i--)
		{
			long first = left/(pow(10, i-1));
			left = left - (first*pow(10, i-1));
			vec[bitNum - i] = first;
        }
        for(auto v:vec){
            cout<<v;
        }
        cout<<endl;

		long tail = absX;
		for(int i = 1;i<bitNum;i++)
		{
			tail= tail-(vec[i-1]*pow(10, bitNum-i));
		}
        cout<<"tail "<<tail<<endl;
        if(tail > 0)
            vec[bitNum -1] = tail;
        for(auto v:vec){
            cout<<v;
        }
        cout<<endl;
        left = reverseVec(vec);
		cout<<left<<endl;
		return isNag ? (-1)*left:left;
	}
}

int main()
{
	string a;
	cin>>a;
	int num = atoi(a.c_str());
	reverse(-2147483648);
	return 0;
}
