#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

const int MAXN = 100;
const double eps = 1e-3;

template <typename tmp>
void input(tmp a[][MAXN], int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> a[i][j];
        }
    }
}

template <typename tmp>
void print(tmp a[][MAXN], int n, int m) {
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
    int *tmp = a;
    b = a;
    a = tmp;
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
        for (int i = 0; i < m; ++i)
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

double* gauss(double **a, double *y, int n) {
    double *coef, mx, tmp;
    coef = (double*) malloc(n * sizeof(double));

    int k = 0, idx;
    while (k < n) {
        mx = abs(a[k][k]);
        idx = k;
        for (int i = k + 1; i < n; ++i) {
            if (abs(a[i][k]) > mx) {
                mx = abs(a[i][k]);
                idx = i;
            }
        }
        
        for (int j = 0; j < n; ++j)  {
            tmp = a[k][j];
            a[k][j] = a[idx][j];
            a[idx][j] = tmp;
        }

        tmp = y[k];
        y[k] = y[idx];
        y[idx] = tmp;
        
        for (int i = k; i < n; ++i) {
            double tmp1 = a[i][k];
            if (abs(tmp1) < eps) continue;
            
            for (int j = 0; j < n; ++j) {
                a[i][j] = a[i][j] / tmp1;
            }
            
            y[i] = y[i] / tmp1;
            if (i == k)  continue;
            for (int j = 0; j < n; ++j) {
                a[i][j] = a[i][j] - a[k][j];
            }
            y[i] = y[i] - y[k];
        }
        ++k;
    }
    
    for (k = n - 1; k >= 0; --k) {
        coef[k] = y[k];
        for (int i = 0; i < k; ++i) {
            y[i] = y[i] - a[i][k] * coef[k];
        }
    }
    
    return coef;
}

void solveTask5(int n) {
    double **a;
    a = new double* [n];
    for (int i = 0; i < n; ++i) {
        a[i] = new double [n + 1];
    }
    double *b = (double*) malloc(n * sizeof(double));
    cout << "Input matrix elements: " << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> a[i][j];
        }
        cin >> b[i];
    }

    double *ans = gauss(a, b, n);

    bool first = false;
    for (int i = 0; i < n; ++i) {
        if (first) {
            cout << "; ";
            first = false;
        }
        first = true;
        cout << "x[" << i << "]=" << ans[i];
    }
}

double *extGauss(double **a, double **coef, int n) {
    int k = 0, idx;
    double m, tmp, tmp1;
    while (k < n) {
        m = a[k][k];
        if (m == 0) {
            for (int i = 0; i < n; ++i) {
                if (a[i][k] != 0) {
                    idx = i;
                    break;
                }
            }

            for (int i = 0; i < n; ++i) {
                tmp = a[k][i];
                tmp1 = coef[k][i];
                a[k][i] = a[idx][i];
                coef[k][i] = coef[idx][i];
                a[idx][i] = tmp;
                coef[idx][i] = tmp1;
            }

            m = a[k][k];
        }

        for (int i = 0; i < n; ++i) {
            a[k][i] = a[k][i] / m;
            coef[k][i] = coef[k][i] / m;
        }

        for (int i = k + 1; i < n; ++i) {
            m = a[i][k];
            for (int j = 0; j < n; ++j) {
                a[i][j] = a[i][j] - a[k][j] * m;
                coef[i][j] = coef[i][j] - coef[k][j] * m;
            }
        }

        ++k;
    }
    for (k = n - 1; k > 0; --k) {
        for (int j = k - 1; j >= 0; --j) {
            m = a[j][k];
            a[j][k] = a[j][k] - a[k][k] * m;
            for (int i = n - 1; i >= 0; --i) {
                coef[j][i] = coef[j][i] - coef[k][i] * m;
            }
        }
    }

    return *coef;
}

void solveTask6(int n) {
    double **a = (double**) malloc(n * sizeof(double*));
    double **x = (double**) malloc(n * sizeof(double*));
    double **y = (double**) malloc(n * sizeof(double*));

    cout << "Input matrix elements: ";
    for (int i = 0; i < n; ++i) {
        x[i] = (double*) malloc(n * sizeof(double));
        a[i] = (double*) malloc(n * sizeof(double));
        for (int j = 0; j < n; ++j) {
            cin >> a[i][j];
            x[i][j] = a[i][j];
        }
    }
    
    for (int i = 0; i < n; ++i) {
        y[i] = (double*) malloc(n * sizeof(double));
        for (int j = 0; j < n; ++j)
            y[i][j] = (i == j) ? 1 : 0;
    }

    extGauss(a, y, n);
    cout.precision(4);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            cout << fixed << y[i][j] << " ";
        cout << endl;
    }
    
    cout << endl;
    double **c = new double *[n];
    for (int i = 0; i < n; ++i) {
        c[i] = new double[n];
        for (int j = 0; j < n; ++j) {
            c[i][j] = 0;
            for (int k = 0; k < n; k++) {
                c[i][j] += x[i][k] * y[k][j];
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (c[i][j] < eps) 
                c[i][j] = 0;
            cout << fixed << c[i][j] << " ";
        }
        cout << endl;
    }
}

void solveTask7(int n) {
    // TO-DO
}

int main() {
    int i = 1;
    int n, m;
    while (i) {
        cin >> i;
        cout << "Task #" << i << endl;
        switch (i) {
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
            case 6:
                cout << "Input matrix sizes: ";
                cin >> n;
                solveTask6(n);
            case 7:
                cout << "Input matrix size: ";
                cin >> n;
                solveTask7(n);
        }
    }
    return 0;
}
