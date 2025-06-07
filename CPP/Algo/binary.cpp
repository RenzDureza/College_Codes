#include <iostream>
using namespace std;
int binarySearch(int arr[], int n, int target) {
    int left = 0, right = n - 1;

    while (left <= right) {
        int mid = left + (right - left)/2;

        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else if (arr[mid] > target) {
            right = mid - 1;
        }
    }

    return -1;
}

int main() {
    int arr[] = {3, 7, 12, 15, 22, 28, 34, 45, 56, 67, 78, 89, 92};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 78;

    int result = binarySearch(arr, n, target);

    if (result != -1) {
        cout << "Found at: " << result << endl;
    } else {
        cout << "Not Found";
    }
}
