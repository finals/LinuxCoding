#include <iostream>
#include <thread>

void func(int &a)
{
    a++;
}

int main(void)
{
    int a = 42;

    std::thread t(func, std::ref(a));
    //std::thread t(func, a);
    t.join();

    std::cout << a << std::endl;

    return 0;
}
