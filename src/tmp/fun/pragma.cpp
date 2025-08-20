#include <iostream>

void func1();
void func2();
// GCC does not support #pragma startup or exit.
#pragma startup func1
#pragma exit func2

void func1(){
    std::cout << "Inside func1()" << std::endl;
}

void func2(){
    std::cout << "Inside func2()" << std::endl;
}

int main(){
    std::cout << "Inside main()" << std::endl;
    return 0;
}