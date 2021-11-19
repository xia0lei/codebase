#include <stdio.h>

#define TEST(param1, param2) (param1##param2)
int main()
{
    int num = TEST(12, 34);
    printf("num = %d\n", num);

    return 0;
}
