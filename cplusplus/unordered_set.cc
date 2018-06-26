#include <iostream>
#include <string>
#include <unordered_set>
#include <set>

int main(void) 
{
    std::unordered_set<int> unorder_set;
    unorder_set.insert(7);
    unorder_set.insert(5);
    unorder_set.insert(3);
    unorder_set.insert(4);
    unorder_set.insert(6);
    std::cout << "unorder_set: " << std::endl;
    for (auto iter : unorder_set) {
       std::cout << iter << std::endl;
    }

    std::set<int> set;
    set.insert(7);
    set.insert(5);
    set.insert(3);
    set.insert(4);
    set.insert(6);
    std::cout << "set: " << std::endl;
    for (auto iter : set) {
        std::cout << iter << std::endl;
    }

    return 0;
}

