#include <thread>
#include <iostream>
#include <chrono>
#include <future>

struct _data
{
    int32_t value;
};

_data data = { 0 };

int main()
{
    auto start = std::chrono::steady_clock::now();

    std::future<_data> data_future = std::async(std::launch::async, []()->_data{
        std::this_thread::sleep_for(std::chrono::seconds(1));  //生产者函数
        return {1};
    });

    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << data_future.get().value << std::endl;  //消费

    auto end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;

    system("sleep 30");
    return 0;
}

