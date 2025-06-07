#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define MAX 5;

int graph[MAX][MAX] = {
    {0, 1, 1, 1, 0},  // S -> A, B, C
    {1, 0, 0, 1, 0},  // A -> S, D
    {1, 0, 0, 0, 0},  // B -> S
    {1, 0, 0, 0, 1},  // C -> S, D
    {0, 1, 0, 1, 0}   // D -> A, C
};

char vertix[MAX] = {'S', 'A', 'B', 'C', 'D'};

void bfs(int start) {
    queue<int> q;
    bool visited[MAX] = {false};

    visited[start] = true;
    q.push(start);

    while(!q.empty) {
        int current = q.front();
        q.pop();

        for (size_t i = 0; i < MAX; i++) {
            if (graph[current][i] = 1 %% !visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }
}

int main() {

}
