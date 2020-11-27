#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

const int MAXM = 100;

void input(double a[][MAXM], int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> a[i][j];
        }
    }
}

void print(double a[][MAXM], int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << setw(4) << a[i][j] << " ";
        }
        cout << endl;
    }
}

void normalization(double a[][MAXM], int n, int m, int step) {
    for (int row = step; row < n; ++row) {
        double norm = a[row][step];
        for (int col = step; col < m; ++col) {
            a[row][col] /= norm;
        }
    }
}

void subtracting(double a[][MAXM], int n, int m, int step) {
    for (int row = step + 1; row < n; ++row) {
        for (int col = step; col < m; ++col) {
            a[row][col] -= a[step][col];
        }
    }
}

void gauss(double a[][MAXM], int n, int m) {
    int step = 0;
    while (step < n) {
        int mx = -1;
        int mxRowNumber;
        for (int row = step; row < n; ++row) {
            if (a[row][step] > mx) {
                mx = a[row][step];
                mxRowNumber = row;
            }
        }
        swap(a[step], a[mxRowNumber]);
        normalization(a, n, m, step);
        subtracting(a, n, m, step);
        ++step;
    }
}

int* getAns(double a[][MAXM], int n, int m) {
    int *ans = new int[n];
    for (int row = n - 1; row >= 0; --row) {
        ans[row] = 0;
        for (int col = 0; col < m; ++col) {
            if (col == m - 1)
                ans[row] += a[row][m - 1];
            else if (col > row) {
                ans[row] -= ans[col] * a[row][col];
            }
        }
    }

    return ans;
}

void solveTask5(int n, int m) {
    if (m > MAXM)
        exit(-1);

    double a[MAXM][MAXM];
    input(a, n, m);
    print(a, n, m);
    gauss(a, n, m);
    cout << endl;
    print(a, n, m);
    int *ans = getAns(a, n, m);
    cout << "Answer: ";
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << " ";
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    solveTask5(n, m);
    return 0;
}
