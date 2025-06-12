#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void task(string taskName);
void hello();

int main() {
    cout << "Hello from main() function, with thread ID: " << this_thread::get_id() << endl;
    thread t1(hello); // created a thread
    t1.join(); // wait for the thread to finish
    cout << "Main function ends..." << endl; 
    return 0; 
}

void task(string taskName) {
    cout << "Starting " << taskName << " on thread ID " << this_thread::get_id() << " ..." << endl;
    this_thread::sleep_for (chrono::seconds(2));
    cout << taskName << " Done !" << endl; 
}

void hello() {
    cout << "Hi form function hello(), with thread ID: " << this_thread::get_id << endl;
}