#include <iostream>
#include <iomanip>
using namespace std;

const int MAXN = 100;

template <typename T>
void input(T a[][MAXN], int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> a[i][j];
        }
    }
}

template <typename T>
void print(T a[][MAXN], int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << setw(4) << a[i][j] << " ";
        }
        cout << endl;
    }
}

void normalization(double a[][MAXN], int n, int m, int step) {
    for (int row = step; row < n; ++row) {
        double norm = a[row][step];
        for (int col = step; col < m; ++col) {
            if (norm != 0)
                a[row][col] /= norm;
        }
    }
}

void subtracting(double a[][MAXN], int n, int m, int step) {
    for (int row = step + 1; row < n; ++row) {
        for (int col = step; col < m; ++col) {
            a[row][col] -= a[step][col];
        }
    }
}

void gauss(double a[][MAXN], int n, int m) {
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

double* getAns(double a[][MAXN], int n, int m) {
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
    int a[MAXN][MAXN], b[MAXN * MAXN];
    input(a, m, n);

    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            b[i * n + j] = a[i][j];

    for (int i = 0; i < n * m; ++i)
        cout << b[i] << ' ';
    cout << endl;

    for (int i = 0; i < m * n; ++i) {
        int row = i / n;
        b[i] = a[row][i - n * row];
    }

    for (int i = 0; i < n * m; ++i)
        cout << b[i] << ' ';
}

void fillSymm(int a[][MAXN], int n, int m) {
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

void fillSnake(int a[][MAXN], int n, int m) {
    // N x N
//    for (int row = 0; row < n; ++row) {
//        if (row % 2 == 0)
//            for (int col = 0; col < m; ++col)
//                a[row][col] = row * n + col;
//        else
//            for (int col = m - 1; col >= 0; --col)
//                a[row][col] = row * n + (m - col - 1);
//    }

    int currentNumber = 0;
    int row = 0, col = 0;
    int currentDir = 1;
    while (row != n - 1 or col != m - 1) {
        if (currentDir == 1 && col == m - 1) {
            a[row][col] = currentNumber++;
            if (row < n)
                ++row;
            a[row][col] = currentNumber++;
            --col;
            currentDir = 2;
            continue;
        }

        if (currentDir == 2 && col == 0) {
            a[row][col] = currentNumber++;
            if (row < n)
                ++row;
            a[row][col] = currentNumber++;
            ++col;
            currentDir = 1;
            continue;
        }

        if (currentDir == 1) {
            a[row][col++] = currentNumber++;
        }

        if (currentDir == 2) {
            a[row][col--] = currentNumber++;
        }
    }

    a[n - 1][m - 1] = currentNumber;
}

void initZeros(int a[][MAXN], int n, int m) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            a[i][j] = 0;
}

void solveTask2(int n, int m) {
    if (m > MAXN)
        exit(0);

    int a[MAXN][MAXN];
    initZeros(a, n, m);

    fillSymm(a, n, m);
    print(a, n, m);

    cout << endl;

    fillSnake(a, n, m);
    print(a, n, m);
}

void solveTask3(int n, int m) {
    if (m > MAXN)
        exit(-1);

    int a[MAXN][MAXN];
    input(a, n, m);

    int sum1 = 0;
    for (int i = 0; i < n; ++i) {
        if (i <= n / 2) {
            for (int j = i; j < m - i; ++j) {
                sum1 += a[i][j];
            }
        } else {
            int shift = i - n/2;
            for (int j = n/2 - shift; j <= n/2 + shift; ++j) {
                sum1 += a[i][j];
            }
        }
    }
    cout << endl;
    int sum2 = 0;
    int shift = n/2;
    for (int i = 0; i < n; ++i) {
        if (i <= n/2) {
            for (int j = shift; j <= n/2 + i; ++j) {
                sum2 += a[i][j];
            }
            --shift;
        } else {
            if (shift < 0)
                shift = 0;
            ++shift;
            for (int j = shift; j < (m - shift); ++j) {
                sum2 += a[i][j];
            }

        }
    }

    cout << sum1 << ' ' << sum2;
}


void solveTask4(int n, int m) {
    if (n > MAXN or m > MAXN)
        exit(-1);

    int **a = (int**) malloc(n * sizeof(int*));

    for (int i = 0; i < n; ++i) {
        a[i] = (int*) malloc(m * sizeof(int));
        for (int j = 0; j < m; ++j) {
            cin >> a[i][j];
        }
    }

    // Сортируем по строкам
    int sums[MAXN];
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

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}

void solveTask5(int n, int m) {
    if (m > MAXN)
        exit(-1);

    double a[MAXN][MAXN];
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
    int n, m;
    for (int taskNumber = 1; taskNumber <= 5; ++taskNumber) {
        cout << "Task #" << taskNumber << endl;
        switch (taskNumber) {
            case 1:
                cout << "Input matrix sizes: ";
                cin >> n >> m;
                cout << "Input matrix elements: " << endl;
                solveTask1(m, n);
                cout << endl;
                break;
            case 2:
                cout << "Input matrix sizes: ";
                cin >> n >> m;
                cout << "Input matrix elements: " << endl;
                solveTask2(n, m);
                cout << endl;
                break;
            case 3:
                cout << "Input matrix sizes: ";
                cin >> n >> m;
                cout << "Input matrix elements: " << endl;
                solveTask3(n, m);
                cout << endl;
                break;
            case 4:
                cout << "Input matrix sizes: ";
                cin >> n >> m;
                cout << "Input matrix elements: " << endl;
                solveTask4(n, m);
                cout << endl;
                break;
            case 5:
                cout << "Input matrix sizes: ";
                cin >> n >> m;
                cout << "Input matrix elements: " << endl;
                solveTask5(n, m);
                cout << endl;
        }
    }
    return 0;
}
