#include <thread>
#include <iostream>
#include <future>

struct _data
{
    int32_t value;
};

_data data = { 0 };

int main()
{
    std::packaged_task<_data()> prepare_data_task([]()->_data{
        std::this_thread::sleep_for(std::chrono::seconds(2));

        return {1}; //返回_data
    });
    auto data_future = prepare_data_task.get_future();

    std::thread do_task_thread([](std::packaged_task<_data()> &task){ //生产者线程
        task();
    }, std::ref(prepare_data_task));

    std::thread process_data_thread([](std::future<_data> &data_future){ //消费者线程
        std::cout << data_future.get().value << std::endl;
    }, std::ref(data_future));

    do_task_thread.join();
    process_data_thread.join();

    system("sleep 30");

    return 0;
}
