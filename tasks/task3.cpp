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

int main() {
    int n, m;
    cin >> n >> m;

    if (m > MAXM)
        return -1;

    int a[n][MAXM];
    input(a, n, m);

    int sum1 = 0;
    for (int i = 0; i < n; ++i) {
        if (i <= n / 2) {
            for (int j = i; j < m - i; ++j)
                sum1 += a[i][j];
        } else {
            for (int j = i - n/2; j < m - (i - n/2); ++j)
                sum1 += a[i][j];
        }
    }

    int sum2 = 0;
    int shift = n/2;
    for (int i = 0; i < n; ++i) {
        if (shift > 0) {
            for (int j = shift; j < (m - shift); ++j) {
                sum2 += a[i][j];
            }
            --shift;
        } else {
            for (int j = shift; j < (m - shift); ++j) {
                sum2 += a[i][j];
            }
            ++shift;
        }
    }

    cout << sum1 << ' ' << sum2;
    return 0;
}
