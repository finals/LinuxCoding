#include <time.h>
#include <iostream>
#include <memory>
#include <string>

#include "thread_pool.h"
#include "test/task_test.h"

using namespace std;

int main(void)
{
    thread::ThreadPool::ThreadPoolConfig threadPoolConfig;
    threadPoolConfig.nMaxThreadsNum = 50;
    threadPoolConfig.nMinThreadsNum = 2;
    threadPoolConfig.dbTaskAddThreadRate = 3;
    threadPoolConfig.dbTaskSubThreadRate = 0.5;

    clock_t start = clock();

    {
        std::shared_ptr<thread::ThreadPool> threadPool(new thread::ThreadPool);
        threadPool->init(threadPoolConfig);

        while (true) {
            std::shared_ptr<TaskTest> request = std::shared_ptr<TaskTest>(new TaskTest());
            threadPool->add_task(request);
        }

        threadPool->release();
    }

    clock_t finish = clock();
    std::cout << "duration: " << finish - start << "ms" << std::endl;
    getchar();

    return 0;
}

