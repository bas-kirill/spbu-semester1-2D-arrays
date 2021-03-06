#include <iostream>
#include <iomanip>
using namespace std;

const int MAXM = 100;

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

void swap(int *a, int *b) {
    int *t = a;
    b = a;
    a = t;
}

void swap(int *a, int *b, int size) {
    for (int i = 0; i < size; ++i) {
        swap(a[i], b[i]);
    }
}

void solveTask4(int n, int m) {
    if (n > MAXM or m > MAXM)
        exit(-1);

    int a[MAXM][MAXM];
    input(a, n, m);

    // Сортируем по строкам
    int sums[MAXM];
    int idx = 0;
    for (int row = 0; row < n; ++row) {
        int sum = 0;
        for (int col = 0; col < m; ++col)
            sum += a[row][col];
        sums[idx++] = sum;
    }

    bool flag = true;
    while (flag) {
        flag = false;
        for (int i = 0; i < n - 1; ++i) {
            if (sums[i] > sums[i + 1]) {
                swap(sums[i], sums[i + 1]);
                swap(a[i], a[i + 1], m);

                flag = true;
            }
        }
    }

    print(a, n, m);
}

int main() {
    int n, m;
    cin >> n >> m;
    solveTask4(n, m);
    return 0;
}
