#include <iostream>
using namespace std;

// 定义逻辑模块创建器
int main()
{
	int arr[2] = {1,2};
	int value = 0;
	for(int i = 0;i<2;i++)
	{
		int a = 1<<arr[i];
		value |= a;
		cout<<"value "<<value<<endl;
	}
	int b = value&(1<<3);
	cout <<"end "<< b<<endl;
	return 0;
}
