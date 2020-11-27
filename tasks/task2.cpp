#include <iostream>
#include <iomanip>
using namespace std;

const int MAXM = 100;

void fillSymm(int a[][MAXM], int n, int m) {
    for (int col = 0; col < m; ++col)
        a[0][col] = col + 1;

    for (int row = 0; row < n; ++row)
        a[row][0] = row + 1;

    for (int row = 1; row < n; ++row) {
        for (int col = 1; col < m; ++col) {
            a[row][col] = a[row - 1][col - 1];
        }
    }
}

void fillSnake(int a[][MAXM], int n, int m) {
    for (int row = 0; row < n; ++row) {
        if (row % 2 == 0)
            for (int col = 0; col < m; ++col)
                a[row][col] = row * n + col;
        else
            for (int col = m - 1; col >= 0; --col)
                a[row][col] = row * n + (m - col - 1);
    }
}

void initZeros(int a[][MAXM], int n, int m) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            a[i][j] = 0;
}

void input(int a[][MAXM], int n, int m) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> a[i][j];
}

void print(int a[][MAXM], int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j)
            cout << setw(4) <<  a[i][j] << " ";
        cout << endl;
    }
}

void solveTask2(int n, int m) {
    if (m > MAXM)
        exit(0);

    int a[MAXM][MAXM];
    initZeros(a, n, m);

    fillSymm(a, n, m);
    print(a, n, m);

    cout << endl;

    fillSnake(a, n, m);
    print(a, n, m);
}

int main() {
    int n, m;
    cin >> n >> m;
    solveTask2(n, m);
    return 0;
}
