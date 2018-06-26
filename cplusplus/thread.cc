#include <iostream>
#include <chrono>
#include <thread>

void threadfunc1()
{
    std::cout << "threadfunc1 - 1\r\n" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "threadfunc1 - 2" << std::endl;
}

void threadfunc2(int iParam, std::string sParam)
{
    std::cout << "threadfunc2 - 1" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << "threadfunc2 - 2" << std::endl;
}

int main()
{
    std::thread t1(threadfunc1);
    std::thread t2(threadfunc2, 10, "abc");
    t1.join();
    std::cout << "t1 join" << std::endl;
    t2.detach();
    std::cout << "t2 detach" << std::endl;


    std::cin.get();
    return 0;
}

