#include <iostream>
#include <vector>
#pragma pack(1)

class Group
{
    char a_;
    int b_;
    char c_;

public:
    char getA() { return a_; }
    int getB() { return b_; }
    char getC() { return c_; }
    void setA(char a) { a_ = a; }
    void setB(int b) { b_ = b; }
    void setC(char c) { c_ = c; }
};

int main()
{
    std::cout << sizeof(Group) << std::endl;
    std::cout << sizeof(char) + sizeof(int) + sizeof(char) << std::endl;
    std::vector<Group> vG;
    std::cout << sizeof(vG) << std::endl;
    vG.resize(2);
    std::cout << sizeof(vG) << std::endl;
    char bytes[100];
    char *start = bytes;
    std::cout << sizeof(bytes) << std::endl;
    Group *gPtr = reinterpret_cast<Group *>(start);
    std::cout << sizeof(gPtr) << std::endl;
    gPtr->setA('a');
    Group tmpG;
    Group *tmpGPtr = &tmpG;
    *tmpGPtr = *gPtr;
    std::cout << tmpG.getA() << std::endl;
    for (int i = 0; i < 10; i++)
    {
        std::cout << bytes[i];
    }
    std::cout << std::endl;
    bytes[0] = 'c';
    for (int i = 0; i < 10; i++)
    {
        std::cout << bytes[i];
    }
    std::cout << std::endl;
    std::cout << tmpG.getA() << std::endl;
    return 0;
}