//回文检测
#include <iostream>
#include <string>
using namespace std;
/*
 * 对于数字 1221，如果执行 1221 % 10，我们将得到最后一位数字 1，要得到倒数第二位数字，
 * 我们可以先通过除以 10 把最后一位数字从 1221 中移除，1221 / 10 = 122，
 * 再求出上一步结果除以 10 的余数，122 % 10 = 2，就可以得到倒数第二位数字。
 * 如果我们把最后一位数字乘以 10，再加上倒数第二位数字，1 * 10 + 2 = 12，就得到了我们想要的反转后的数字。如果继续这个过程，我们将得到更多位数的反转数字。
 *
 * 现在的问题是，我们如何知道反转数字的位数已经达到原始数字位数的一半？
 *
 * 由于整个过程我们不断将原始数字除以 10，然后给反转后的数字乘上 10，所以，当原始数字小于或等于反转后的数字时，就意味着我们已经处理了一半位数的数字了。
 *
 */

bool palidrome(int x){
    if(x< 0 || (x %10 == 0 && x!=0)){
        return false;
    }
    int revertNumber = 0;
    while(x > revertNumber){
        revertNumber = revertNumber *10 + x%10;
        x/=10;
    }
    return x== revertNumber || x==revertNumber/10;
}

int main(){
    string a;
    cin>>a;
    int num = atoi(a.c_str());
    palidrome(num);
}
