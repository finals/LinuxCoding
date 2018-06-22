#include <iostream>

//识别两个类型是否相同，提前进入模板元编程
template<typename T1, typename T2> //通例，返回false
class theSameType {
public:
    enum { ret = false };
};

template<typename T>        //特例，两类型相同时返回true
class theSameType<T, T> {
public:
    enum { ret = true };
};

template<typename T, int i>
class aTMP {
};

int main()
{
    typedef unsigned int uint; //typedef定义类型别名而不是引入新类型
    typedef uint uint2;

    std::cout << theSameType<unsigned, uint2>::ret << std::endl;

    std::cout << theSameType<aTMP<unsigned, 2>, aTMP<uint2, 2>>::ret << std::endl;
    std::cout << theSameType<aTMP<int, 2>, aTMP<int, 2>>::ret << std::endl;

    std::cin.get();

    return 0;
}
