#include <stdio.h>

int func();
int main()
{
    func();
    //此处使用extern
    extern int num;
    //找不到num的声明
    printf("$d", num);
    return 0;
}

int num = 3;
int func()
{
    printf("func %d\n", num);
}
