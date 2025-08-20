#include <iostream>

#define PI 3.14
#define foo(l, b) (l*b)

int main()
{
    int l1 = 10, l2=5, area;
    #ifndef PI
        std::cout << "PI is not defined\n";
    #elif defined(foo)
        std::cout << "MACRO foo with arguments (l, b) is defined\n";
    #endif
    area = PI * foo(l1, l2);
    std::cout << area << std::endl;
    return 0;
}