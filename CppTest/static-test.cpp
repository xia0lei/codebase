#include<iostream>
using namespace std;

class A
{
    public:
        A(int i)
        {
            a = i;
        }

        int GetValue()
        {
            return a;
        }

        static int a;
};

int A::a = 0;

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

    auto a1 = new A(1);
    auto a2 = new A(2);
    cout <<a1->GetValue()<<" "<<a2->GetValue()<<endl;
	return 0;
}
