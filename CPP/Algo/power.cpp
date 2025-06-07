#include <iostream>
using namespace std;

int powerP(int n, int e) {
    if (e == 0) {
        return 1;
    } else {
        return n * powerP(n, e - 1);
    }
}

int main() {
    int n = 5;
    int e = 2;

    cout << powerP(n, e);
}

