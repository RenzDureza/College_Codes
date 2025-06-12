#include <iostream>
#include <thread>
#include <mutex>

using namespace std;
mutex mtx;
int balance = 1000;

void withdrawMoney(string name, int amount);

int main() {
    thread user1(withdrawMoney, "Cielo", 500);
    thread user2(withdrawMoney, "Renz", 1000);

    user1.join();
    user2.join();
}

void withdrawMoney(string name, int amount) {
    mtx.lock();

    if (balance >= amount) {
        cout << name << " withdrawing " << amount << endl;
        this_thread::sleep_for(chrono::seconds(2));
        balance -= amount;
        cout << name << " successfully withdrew " << amount << endl;
        cout << "Remaining balance: " << balance << endl;
    } else {
        cout << name << " failed to withdraw " << amount << endl;
    }

    mtx.unlock();

}
