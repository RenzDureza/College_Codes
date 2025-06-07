#include <iostream>
using namespace std;

int factorial(int n) {
    if (n == 1) {
        return n;
    } else {
        return n * factorial(n - 1);
    }
}

int factIterative(int n) {
    int fact = 1;
    for (int i = 1; i <= n; i++) {
        fact *= i;
    }
    return fact;
}

int main() {
    int n = 5;
    cout << "Recursive way:\n";
    cout << factorial(n);
    cout << "\nIterative way\n";
    cout << factIterative(n);
    
    return 0;
}
