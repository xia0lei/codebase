#include <iostream>
#include <string>
using namespace std;

string version1(const string &s1, const string &s2)
{
	string tmp;
	tmp = s2 + s1 + s2;
	return tmp;
}

const string &version2(string &s1, const string &s2)
{
	s1 = s2 + s1 +s2;
	return s1;
}


const string &version3(string &s1, const string &s2)
{
	//此处返回引用会报错，因为tmp是一个临时值
	string tmp;
	tmp = s2 + s1 + s2;
	return tmp;
}

void CoutFormat(const string &enhanced, const string & original)
{
	cout << "enhanced: " << enhanced<< endl;
	cout << "original: " << original<< endl;
	cout << endl;
}

int main()
{
	string input;
	string copy;
	string result;

	cout << "Enter a string:";
	getline(cin, input);
	copy = input;
	cout << "Your String as entered: " << input << endl;
	result = version1(input, "***");
	CoutFormat(result, input);

	result = version2(input, "###");
	CoutFormat(result, input);

	cout<<"Resetting original string"<<endl;
	input = copy;
	result = version3(input, "@@@");
	CoutFormat(result, input);
	return 0;
}