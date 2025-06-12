#include <iostream>
#include <cstdlib>
using namespace std;

const int stockNum = 1000;

void alertSystem(int stock[]);
void printArr(int arr[]);

int main() {
    srand(time(0));
    int stocks[stockNum];

    for (int i = 0; i < stockNum; i++) {
       stocks[i] = rand() % 101; 
    }

    alertSystem(stocks);
    
}

void alertSystem(int stock[]) {
    int lowStocks = 0;
    for (int i = 0; i < stockNum + 1; i++) {
        if(stock[i] < 10) {
            cout << "[ALERT] Product " << i << ": " << stock[i] << " units left" << endl; 
            lowStocks++;
        }
    }
    cout << "Number of low-stock items: " << lowStocks << "\n" << "Aldrin Renz Dureza" << endl;
}
