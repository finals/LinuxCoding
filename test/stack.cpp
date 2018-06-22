#include <iostream>
#include <stack>

using namespace std;

class MinStack {
public:
    stack<int> data;
    stack<int> min;

    void push(int value);
    int pop();
    int top();
    bool empty();
    int size(); 
    int minv();
};

void MinStack::push(int value) 
{
    int v = value;
    if (!data.empty()) {
        v = min.top();
        if (v >= value) {
            min.push(value);
        } else {
            min.push(v);
        }
    } else {
        min.push(value);
    }
    
    data.push(value);
}

int MinStack::pop() 
{
    int v = data.top();
    min.pop();
    data.pop();

    return v;
}

int MinStack::minv()
{
    return min.top();
}

int MinStack::top() 
{
    return data.top();
}

bool MinStack::empty() 
{
    return data.empty();
}

int MinStack::size() 
{
    return (int)data.size();
}


int main(void)
{
    MinStack mstack;

    mstack.push(4);
    mstack.push(2);
    mstack.push(8);
    mstack.push(7);
    mstack.push(1);
    mstack.push(3);

    int size = mstack.size();
    for (int i = 0; i < size; ++i) {
        cout << "i: " << i << "  " << mstack.minv() << endl;
        mstack.pop();
    }
    
    return 0;
}
