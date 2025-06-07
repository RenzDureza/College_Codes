#include <iostream>
using namespace std;

int rMul(int x, int y) {
    int product = 0;
    if (x % 2 != 0) {
        product += y;
    }

    while (x != 1) {
        x = x / 2;
        y = y * 2;

        if (x % 2 != 0) {
            product += y;
        }
    }

    return product;
}

int main() {
    int x = 16;
    int y = 26;
    
    cout << rMul(x, y);
}
