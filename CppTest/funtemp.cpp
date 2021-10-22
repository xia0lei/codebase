#include <iostream>
using namespace std;

template <typename T>
void Swap(T &a, T &b)
{
	T tmp;
	tmp = a;
	a = b;
	b = tmp;
}

int main()
{
	int i = 0;
	int j = 20;

	cout << "i, j = "<<i<<","<<j<<".\n";
	cout <<"Using compiler-generated int swapper:"<<endl;
	Swap(i, j);

	double x = 24.5;
	double y = 81.7;
	cout <<"x, y="<<x<<","<<y<<".\n";
	Swap(x, y);
	cout <<"Now x, y = "<<x<<","<<y<<endl;
	return 0;
}