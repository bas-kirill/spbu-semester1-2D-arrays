#include <iostream>
#include <iomanip>
using namespace std;

const int MAXM = 100;

template <typename T>
void input(T a[][MAXM], int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> a[i][j];
        }
    }
}

template <typename T>
void print(T a[][MAXM], int n, int m) {
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
        double mx = -1;
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

double* getAns(double a[][MAXM], int n, int m) {
    double *ans = new double[n];
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

void solveTask1(int m, int n) {
    int a[MAXM][MAXM], b[MAXM * MAXM];
    input(a, m, n);

    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            b[i * m + j] = a[i][j];

    for (int i = 0; i < m * n; ++i) {
        int row = i / m;
        b[i] = a[row][i - m * row];
    }
}

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

void solveTask3(int n, int m) {
    if (m > MAXM)
        exit(0);

    int a[MAXM][MAXM];
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

void solveTask5(int n, int m) {
    if (m > MAXM)
        exit(-1);

    double a[MAXM][MAXM];
    input(a, n, m);
    print(a, n, m);
    gauss(a, n, m);
    cout << endl;
    print(a, n, m);
    double *ans = getAns(a, n, m);
    cout << "Answer: ";
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << " ";
    }
}

int main() {
    int taskNumber = 1;
    int n, m;
    switch (taskNumber) {
        case 1:
            cout << "Input matrix's sizes: ";
            cin >> n >> m;
            cout << "Input matrix's elements: " << endl;
            solveTask1(m, n);
            cout << endl;
            break;
        case 2:
            cout << "Input matrix's sizes: ";
            cin >> n >> m;
            cout << "Input matrix's elements: " << endl;
            solveTask2(n, m);
            cout << endl;
            break;
        case 3:
            cout << "Input matrix's sizes: ";
            cin >> n >> m;
            cout << "Input matrix's elements: " << endl;
            solveTask3(n, m);
            cout << endl;
            break;
        case 4:
            cout << "Input matrix's sizes: ";
            cin >> n >> m;
            cout << "Input matrix's elements: " << endl;
            solveTask4(n, m);
            cout << endl;
            break;
        case 5:
            cout << "Input matrix's sizes: ";
            cin >> n >> m;
            cout << "Input matrix's elements: " << endl;
            solveTask5(n, m);
            cout << endl;
    }
    return 0;
}
