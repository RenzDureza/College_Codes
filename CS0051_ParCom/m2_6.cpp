a#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void collectData();

int main() {
    cout << "YOU: Starting to write the report" << endl;
    thread f(collectData);
    f.detach();
    cout << "YOU: Submit the report" << endl;
    this_thread::sleep_for(chrono::seconds(6));

    return 0;
}

void collectData() {
    cout << "Friend: Collecting data for 5 seconds" << endl;
    this_thread::sleep_for(chrono::seconds(5));
    cout << "Friend: Finished collecting data" << endl;
}