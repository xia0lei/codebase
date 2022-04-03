#include <iostream>

int main()
{
    for(int i = 0; i<100;i++)
    {
        std::cout<<"value "<<i;
        int left = i %2;
        switch(left)
        {
            case 0:
                {
                    std::cout<<"left is zero"<<std::endl;
                }
                break;
            case 1:
                {
                    std::cout<<"left is one"<<std::endl;
                }
                break;
            default:
                break;
        }
    }
    std::cout<<"end"<<std::endl;
    return 0;
}
