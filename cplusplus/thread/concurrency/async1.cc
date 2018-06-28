#include <future>
#include <thread>
#include <chrono>
#include <random>
#include <iostream>
#include <exception>

int do_something(char c)
{
    std::default_random_engine dre(c);
    std::uniform_int_distribution<int> id(10, 1000);

    for (int i = 0; i < 10; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(id(dre)));
        std::cout.put(c).flush();
    }

    return c;
}

int func1()
{
    return do_something('.');
}

int func2()
{
    return do_something('+');
}

int main()
{
    std::cout << "starting func1() in background and func2() in foreground: " << std::endl;

    std::future<int> result1(std::async(func1)); //启动线程，异步计算func1
    //int result1 = func1();

    //std::future<int> result2(std::async(func2));
    int result2 = func2();

    int result = result2 + result1.get();

    std::cout << "\nresult of func1 + func2: " << result << std::endl;

    return 0;
}

