#include <iostream>

#define SIZE 4

using namespace std;

int index[SIZE] = {0, 1, 2, 3};

void show(double matrix[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%f\t", matrix[index[i]][j]);
        }
        cout << endl;
    }
    cout << endl;
}

void partial_pivoting(double matrix[SIZE][SIZE], int k) {
    if (matrix[index[k]][k] == 0.0) {
        int max_row = k + 1;
        double max = fabs(matrix[index[k + 1]][k]);

        for (int i = k + 1; i < SIZE; i++) {
            double value = fabs(matrix[index[i]][k]);
            if (value > max) {
                max = value;
                max_row = i;
            }
        }
        swap(index[max_row], index[k]);
    }
}

void gauss_elimination(double u[SIZE][SIZE], double l[SIZE][SIZE], int k) {
    for (int i = k; i < SIZE - 1; i++) {
        double coefficient = u[index[i + 1]][k] / u[index[k]][k];
        for (int j = k; j < SIZE; j++) {
            u[index[i + 1]][j] -= u[index[k]][j] * coefficient;
        }
        l[index[i + 1]][k] = coefficient;
    }
}

void decomposition(double a[SIZE][SIZE], double l[SIZE][SIZE], double u[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            u[i][j] = a[i][j];
        }
    }
    for (int k = 0; k < SIZE - 1; k++) {
        partial_pivoting(u, k);
        gauss_elimination(u, l, k);
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i == j) {
                l[index[i]][j] = 1.0;
            } else if (i < j) {
                l[index[i]][j] = 0.0;
            }
        }
    }
    cout << "Upper:" << endl;
    show(u);
    cout << "Lower:" << endl;
    show(l);
}

void count_y(double l[SIZE][SIZE], double b[SIZE], double y[SIZE]) {
    double sum;
    for (int i = 0; i < SIZE; i++) {
        sum = 0.0;
        for (int j = 0; j < i; j++) {
            sum += l[index[i]][j] * y[j];
        }
        y[i] = (b[index[i]] - sum) / l[index[i]][i];
    }
}

void count_x(double u[SIZE][SIZE], double x[SIZE], double y[SIZE]) {
    double sum;
    for (int i = SIZE - 1; i >= 0; i--) {
        sum = 0.0;
        for (int j = i + 1; j < SIZE; j++) {
            sum += u[index[i]][j] * x[j];
        }
        x[i] = (y[i] - sum) / u[index[i]][i];
    }
}

bool check(double A[SIZE][SIZE], double b[SIZE], double x[SIZE]) {
    int counter = 0;
    double sum;
    for (int i = 0; i < SIZE; i++) {
        sum = 0.0;
        for (int j = 0; j < SIZE; j++) {
            sum += A[i][j] * x[j];
        }
        if (sum == b[i]) {
            counter++;
        }
    }
    if (counter == SIZE) {
        return true;
    } else {
        return false;
    }

}

int main() {
    double a[SIZE][SIZE] = {{1.0,   -20.0,  30.0,   -4.0},
                            {2.0,   -40.0,  -6.0,   50.0},
                            {9.0,   -180.0, 11.0,   -12.0},
                            {-16.0, 15.0,   -140.0, 13.0}};
    double b[SIZE] = {35.0, 104.0, -366.0, -354.0};
    double l[SIZE][SIZE], u[SIZE][SIZE];
    double x[SIZE], y[SIZE];
    show(a);
    decomposition(a, l, u);
    count_y(l, b, y);
    cout << "Ly = b" << endl;
    for (int i = 0; i < SIZE; i++) {
        printf("y%d= %f\n", i + 1, y[i]);
    }
    count_x(u, x, y);
    cout << "Ux = y" << endl;
    for (int i = 0; i < SIZE; i++) {
        printf("x%d= %f\n", i + 1, x[i]);
    }
    if (check(a, b, x)) {
        cout << "Good" << endl;
    }
    return 0;
}
