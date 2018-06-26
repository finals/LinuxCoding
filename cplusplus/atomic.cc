#include <iostream>
#include <thread>
#include <atomic>
#include <list>

std::atomic_bool bIsReady(false);
std::atomic_int  iCount(100);

void threadfunc1()
{
    if (!bIsReady) {
        std::this_thread::yield();
    }

    while (iCount > 0) {
        std::cout << "iCount: " << iCount-- << std::endl;
    }
}

int main(void)
{
    std::atomic_bool b; 
    std::list<std::thread> lsThread;
    for (int i = 0; i < 10; ++i) {
        lsThread.push_back(std::thread(threadfunc1));
    }

    for (auto &th : lsThread) {
        th.join();
    }

    bIsReady = true;

    std::cin.get();

    return 0;
}

