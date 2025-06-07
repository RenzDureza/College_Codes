#include <iostream>
#include <stack>
using namespace std;

#define MAX 5

int graph[MAX][MAX] {
    {0, 1, 1, 1, 0},  // S -> A, B, C
    {1, 0, 0, 1, 0},  // A -> S, D
    {1, 0, 0, 0, 0},  // B -> S
    {1, 0, 0, 0, 1},  // C -> S, D
    {0, 1, 0, 1, 0}   // D -> A, C
};

void dfs(int start) {
    stack<int> s;
    bool visited[MAX] = {false};

    visited[start] = true;
    s.push(start);

    while (!s.empty()) {
        int current = s.top();
        s.pop();
        if (!visited[current]) {
            visited[current] = true;
            cout << current << " ";

            for (int i = MAX - 1; i >= 0; i--) {
                if (graph[current][i] == 1  && !visited[i]) {
                    s.push(i);
                }
            }
        }
    }
    cout << endl;
}

int main() {
    dfs(0);
}
