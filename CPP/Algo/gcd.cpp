#include <iostream>
using namespace std;

int gcd(int x, int y) {
    while (y != 0) {
        int r = x % y;
        x = y;
        y = r;
    }

    return x;
}

int recursionGCD(int x, int y) {
    if (x == 0) {
        return y;
    }

    cout << y << " = " << x << " * " << y / x << " + " << y % x << endl;

    // Recursive call
    return recursionGCD(y % x, x);
}

int main() {
    int x = 50;
    int y = 180;

    cout << recursionGCD(x, y);

    return 0;
}
