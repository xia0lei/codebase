#include <iostream>
#include <cmath>

//求一个数是不是完全平方数 16为true 9为true 10为false
//耗时7
bool isPerfectSquare1(int num){
	if(num < 1|| num>(pow(2,31)-1))
	{
		std::cout<<"num is unavaliable "<<(pow(2,31) -1 )<<std::endl;
		return false;
	}

	for (int i = 1; i <= num; i++)
	{
		int tmp = num / i;
		int left = num % i;
		if (tmp == i && left == 0)
		{
			return true;
		}
	}
	return false;
}

//耗时0.096毫秒
bool isPerfectSquare2(int num){
	//原理 4 = 1+3  9 = 1+3+5 16 = 1+3+5+7
	int num1 = 1;
	while (num > 0)
	{
		num -= num1;
		num1 += 2;
        }
        return num == 0;
}

//耗时11
bool isPerfectSquare3(int num){
long l = 0, r = num;
        while (l < r) {
            long mid = l + r + 1 >> 1;
            if (mid * mid <= num) l = mid;
            else r = mid - 1;
        }
        return r * r == num;
}


int main(){
	//效率不够
	//isPerfectSquare1(2000105819);
	auto startTime = clock();
	double total_t;
	bool ret = isPerfectSquare3(2000105819);
	total_t = (double)(clock()- startTime) / CLOCKS_PER_SEC;
	std::cout<<ret<<" "<<total_t*1000<<std::endl;
	return 0;
}