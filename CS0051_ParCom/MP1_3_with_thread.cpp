#include <cstdlib>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;
mutex mtx;

const int stockNum = 1000;
int lowStocks = 0;

void alertSystem(int stock[], int start, int end);
void printArr(int arr[]);

int main() {
  srand(time(0));
  int categories = stockNum / 4;
  int stocks[stockNum];

  for (int i = 0; i < stockNum; i++) {
    stocks[i] = rand() % 101;
  }

  fill_n(stocks, stockNum, 5);
  thread t1(alertSystem, stocks, 0, categories - 1);
  thread t2(alertSystem, stocks, categories, 2 * categories - 1);
  thread t3(alertSystem, stocks, 2 * categories, 3 * categories - 1);
  thread t4(alertSystem, stocks, 3 * categories, stockNum - 1);

  t1.join();
  t2.join();
  t3.join();
  t4.join();

  cout << "Number of low-stock items: " << lowStocks << "\n"
       << "Aldrin Renz Dureza" << endl;
}

void alertSystem(int stock[], int start, int end) {
  mtx.lock();
  for (int i = start; i <= end; i++) {
    if (stock[i] < 10) {
      cout << "[ALERT] Product " << i << ": " << stock[i] << " units left"
           << endl;
      lowStocks++;
    }
  }
  mtx.unlock();
}
