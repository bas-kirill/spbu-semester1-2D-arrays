#include <iostream>
#include <iomanip>
#include <cstring>

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

void solveTask1(int choice) {
    if (choice == 1) {
        double** arr;
        int n, m;
        cout << "Input matrix sizes: ";
        cin >> n >> m;
        arr = new double* [n];

        for (int i = 0; i < n; ++i)
            arr[i] = new double[m];

        cout << "Input matrix elements: ";
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                cin >> arr[i][j];

        int* a = new int[n * m];
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                a[i * m + j] = arr[i][j];

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j)
                cout << arr[i][j] << " ";
            cout << endl;
        }

        for (int i = 0; i < n * m; ++i)
            cout << a[i] << " ";
    }
    else {
        double **arr;
        int m, n;
        cout << "Input matrix sizes: ";
        cin >> m >> n;
        arr = new double* [m];
        for (int i = 0; i < m; i++)
            arr[i] = new double[n];

        cout << "Input array elements: ";
        int* a = new int[m * n];
        for (int i = 0; i < m * n; ++i)
            cin >> a[i];

        for (int i = 0; i < m * n; ++i)
            arr[i / n][i % n] = a[i];

        for (int i = 0; i < n * m; ++i)
            cout << a[i] << " ";

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j)
                cout << arr[i][j] << " ";
            cout << endl;
        }
    }
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

void fillSpiral(int a[][MAXN], int n, int m) {
    int currentNumber = 1;
    int row = 0, col = 0;
    int step = 0;
    while (currentNumber <= n * m) {
        while (col < m - step) {
            a[row][col++] = currentNumber++;

        }

        --col;

        if (row == n/2 && col == m/2)
            break;

        ++row;

        while (row < n - step) {
            a[row++][col] = currentNumber++;
        }

        --row;

        if (row == n/2 && col == m/2)
            break;

        --col;

        while (col >= step) {
            a[row][col--] = currentNumber++;
        }

        ++step;

        ++col;

        if (row == n/2 && col == m/2)
            break;

        --row;

        while (row >= step) {
            a[row--][col] = currentNumber++;
        }

        ++row;

        if (row == n/2 && col == m/2)
            break;

        ++col;
    }
}

void solveTask2(int n, int m) {
    if (m > MAXN)
        exit(0);

    int a[MAXN][MAXN];
    memset(a, 0, n * m);

    fillSymm(a, n, m);
    print(a, n, m);

    cout << endl;
    memset(a, 0, n * m);
    fillSpiral(a, n, m);
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

void gauss(double** a, int n) {
    double k;
    for (int i = 0; i < n; i++) {
        k = a[i][i];
        for (int j = i; j < n + 1; j++) {
            a[i][j] /= k;
        }
        for (int c = i + 1; c < n; c++) {
            double m = a[c][i];
            for (int g = i; g < n + 1; g++) {
                a[c][g] -= a[i][g] * m;
            }
        }
    }
}

void solveTask5(int n) {
    double **a;
    a = new double* [n];
    for (int i = 0; i < n; i++) {
        a[i] = new double [n + 1];
    }

    cout << "Input matrix elements: " << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n + 1; ++j) {
            cin >> a[i][j];
        }
    }

    gauss(a, n);

    double k;
    for (int i = n - 1; i >= 0; --i) {
        for (int j = i; j > 0; --j) {
            double m = a[j - 1][i];
            for (int g = i; g < n + 1; ++g) {
                a[j - 1][g] -= a[i][g] * m;
            }
        }
    }

    cout << "Answer: " << a[0][3] << " " << a[1][3] << " " << a[2][3] << endl;
}

int main() {
    int n, m;
    for (int taskNumber = 5; taskNumber <= 5; ++taskNumber) {
        cout << "Task #" << taskNumber << endl;
        switch (taskNumber) {
            case 1:
                cout << endl << "Input choice: k = 1 - a[][] -> b[], b[] -> a[][]: ";
                int choice; cin >> choice;
                solveTask1(choice);
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
                int n;
                cout << "Input matrix size: ";
                cin >> n;
                solveTask5(n);
                cout << endl;
        }
    }
    return 0;
}
