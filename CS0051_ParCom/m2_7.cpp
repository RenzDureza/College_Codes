#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void simpleTask();

int main() {
    thread t(simpleTask);
    // t.join();
    if (t.joinable()) {
        cout << "Thread can be joined\n";
        t.join();
    } else {
        cout << "Thread cannot be joined\n";
    }

    return 0;
}

void simpleTask() {
    cout << "Hello, World\n";
}