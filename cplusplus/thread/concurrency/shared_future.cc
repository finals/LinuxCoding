#include <future>
#include <thread>
#include <iostream>
#include <exception>
#include <stdexcept>

using namespace std;

int query_number()
{
    cout << "read number: ";
    int num;
    cin >> num;

    if (!cin) {
        throw runtime_error("no number read");
    }

    return num;
}

void do_something(char c, shared_future<int> f)
{
    try {
        int num = f.get();

        for (int i = 0; i < num; ++i) {
            this_thread::sleep_for(chrono::milliseconds(100));
            cout.put(c).flush();
        }
    } catch (const exception &e) {
        cerr << "EXCEPTION in thread " << this_thread::get_id() << ": " << e.what() << endl;
    }
}

int main() 
{
    try {
        shared_future<int> f = async(query_number);

        auto f1 = async(launch::async, do_something, '.', f);
        auto f2 = async(launch::async, do_something, '+', f);
        auto f3 = async(launch::async, do_something, '*', f);

        f1.get(); 
        f2.get();
        f3.get();
    } catch (const exception &e) {
        cout << "\nEXCEPTION: " << e.what() << endl;
    }
    cout << "\ndone" << endl;
}

