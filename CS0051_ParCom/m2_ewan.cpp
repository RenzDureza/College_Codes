#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;
mutex mtx;

void printer(string name) {
    mtx.lock();
    cout << name << " is printing...\n";
    this_thread::sleep_for(chrono::seconds(1));
    cout << name << " is done printing\n";
    mtx.unlock(); 
}

int main() {
    thread user[] = {
        thread(printer, "Renz"),
        thread(printer, "Cielo")
    };
    
    for (int i = 0; i < 2; i++)
    {
        user[i].join();
    }
    
}