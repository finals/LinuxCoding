#include <iostream>
#include <sstream>

using namespace std;

template <typename T> std::string debug_rep(const T &t)
{
    std::ostringstream ret;
    ret << t;
    return ret.str();
}

template<typename T> std::ostream &print(std::ostream &os, const T &t)
{
    return os << t;
}

//可变参数模板, "..."是包扩展(Pack Expansion)  
template <typename T, typename... Args>
std::ostream &print(std::ostream &os, const T &t, const Args&... rest)
{
    os << t << ", ";
    return print(os, rest...); //递归输出
}

//函数模板的包扩展
template <typename... Args>
std::ostream &errorMsg(std::ostream &os, const Args&... rest)
{
    return print(os, debug_rep(rest)...); //使用模板的包扩展
}

int main()
{
    int i(10);
    std::string s("girls");

    errorMsg(std::cout, i, s, 10, "ladies");

    cout << endl;

    return 0;
}
