#include <iostream>
using namespace std;

const int MAXM = 1000;

void solveTask1(int m, int n) {
    int a[MAXM][MAXM], b[MAXM * MAXM];
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            cin >> a[i][j];

    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            b[i * m + j] = a[i][j];

    for (int i = 0; i < m * n; ++i) {
        int row = i / m;
        b[i] = a[row][i - m * row];
    }
}

int main() {
    int m, n;
    cin >> m >> n;
    solveTask1(m, n);
    return 0;
}
