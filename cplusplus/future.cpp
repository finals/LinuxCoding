#include <thread>
#include <iostream>
#include <future>
#include <chrono>

struct _data
{
    int32_t value;
};

_data data = { 0 };

int main()
{
    std::promise<_data> data_promise;
    std::future<_data> data_future = data_promise.get_future();

    std::thread prepare_data_thread([](std::promise<_data> &data_promise){
        std::this_thread::sleep_for(std::chrono::seconds(2));
        data_promise.set_value({ 1 });
    }, std::ref(data_promise));

    std::thread process_data_thread([](std::future<_data> &data_future){
        std::cout << data_future.get().value << std::endl;
    }, std::ref(data_future));


    prepare_data_thread.join();
    process_data_thread.join();

    system("sleep 30");
    return 0;
}

