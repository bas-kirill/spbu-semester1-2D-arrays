#include <iostream>
using namespace std;

int main() {
    int m, n;
    cin >> m >> n;
    int a[m][n], b[m * n];
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

    return 0;
}
