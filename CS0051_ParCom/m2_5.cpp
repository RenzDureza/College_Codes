#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void cookRice();

int main() {
    cout << "YOU: Start chopping vegetables" << endl;
    thread f(cookRice);
    f.join();
    cout << "YOU: Serve meal together" << endl;
    return 0;
}

void cookRice() {
    cout << "Friend: Cooking rice (5 sec)" << endl;
    this_thread::sleep_for(chrono::seconds(5));
    cout << "Friend: Rice is ready..." << endl;
}