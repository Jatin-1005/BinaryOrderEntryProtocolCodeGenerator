#include <iostream>

int foo(char c) { return (int)c; }

void printASCIIcode(char c, int(*func_ptr)(char))
{
    int ascii = func_ptr(c);
    std::cout << "ASCII code of " << c << " is: " << ascii << std::endl;
}

int main()
{
    printASCIIcode('a', &foo);
    return 0;
}