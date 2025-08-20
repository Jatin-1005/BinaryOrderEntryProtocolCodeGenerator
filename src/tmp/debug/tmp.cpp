#include <iostream>
#include <thread> // For std::this_thread
#include <chrono> // For std::chrono
int square(int num)
{
    return num * num;
}

int main()
{
    for (int i = 0; i < 10; i++)
    {
        std::cout << square(i) << std::endl;
        // std::this_thread::sleep_for(std::chrono::seconds(1)); // Add a sleep to slow things down
    }
    return 0;
}