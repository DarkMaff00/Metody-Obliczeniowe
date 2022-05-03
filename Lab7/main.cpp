#include <iostream>

#define SIZE 4
#define MAX 50

using namespace std;

void show(double x[SIZE]) {
    cout << "[";
    for (int i = 0; i < SIZE; i++) {
        printf("%.10f ", x[i]);
    }
    cout << "]" << endl;
}

bool convergence(double A[SIZE][SIZE]) {
    int count = 0;
    double sum;
    for (int i = 0; i < SIZE; i++) {
        sum = 0.0;
        for (int j = 0; j < SIZE; j++) {
            if (i != j) {
                sum += fabs(A[i][j]);
            }
        }
        if (fabs(A[i][i]) > sum) count++;
    }
    return count == SIZE;
}

bool error(double xn[SIZE], double xn_1[SIZE]) {
    int count = 0;
    cout << "Estymatory: [";
    printf("%.10f ", fabs(xn_1[0] - xn[0]));
    if (fabs(xn_1[0] - xn[0]) < 1e-7) count++;
    printf("%.10f ", fabs(xn_1[1] - xn[1]));
    if (fabs(xn_1[1] - xn[1]) < 1e-7) count++;
    printf("%.10f ", fabs(xn_1[2] - xn[2]));
    if (fabs(xn_1[2] - xn[2]) < 1e-7) count++;
    printf("%.10f]\n", fabs(xn_1[3] - xn[3]));
    if (fabs(xn_1[3] - xn[3]) < 1e-8) count++;

    return count == SIZE;
}

bool residue(double A[SIZE][SIZE], double b[SIZE], const double xn[SIZE]) {
    int count = 0;
    cout << "Residuum: [";
    for (int i = 0; i < SIZE; i++) {
        double sum = 0.0;
        for (int j = 0; j < SIZE; j++) {
            sum += A[i][j] * xn[j];
        }
        printf("%.10f ", fabs(sum - b[i]));
        if (fabs(sum - b[i]) < 1e-8) count++;
    }
    cout << "]" << endl;

    return count == SIZE;
}

void jacobi(double A[SIZE][SIZE], double b[SIZE]) {
    cout << "Metoda Jacobiego" << endl;
    if (convergence(A)) {
        cout << "Metoda jest zbiezna" << endl;
    }
    double xn[SIZE] = {2.0, 2.0, 2.0, 2.0};
    double xn_1[SIZE];

    for (int limit = 0; limit < MAX; limit++) {
        for (int i = 0; i < SIZE; i++) {
            double sum = 0.0;
            for (int j = 0; j < SIZE; j++) {
                if (j != i) {
                    sum += A[i][j] * xn[j];
                }

                xn_1[i] = (b[i] - sum) / A[i][i];
            }
        }
        cout << limit << "    ";
        show(xn_1);
        bool en = error(xn_1, xn);
        bool re = residue(A, b, xn);
        if (en && re) break;
        swap(xn_1, xn);
        cout << endl;
    }
}

void gauss_seidel(double A[SIZE][SIZE], double b[SIZE]) {
    cout << "Metoda Gaussa-Seidela" << endl;
    if (convergence(A)) {
        cout << "Metoda jest zbiezna" << endl;
    }
    double xn[SIZE] = {2.0, 2.0, 2.0, 2.0};
    double right[SIZE];

    for (int limit = 0; limit < MAX; limit++) {
        for (int i = 0; i < SIZE; i++) {
            double sum = 0.0;

            for (int j = i + 1; j < SIZE; j++) {
                sum += A[i][j] * xn[j];
            }
            right[i] = -sum + b[i];
        }

        double xn_1[SIZE] = {0.0, 0.0, 0.0, 0.0};

        for (int i = 0; i < SIZE; i++) {
            double sum = 0.0;

            for (int j = 0; j <= i; j++) {
                sum += xn_1[j] * A[i][j];
            }
            xn_1[i] = (right[i] - sum) / A[i][i];
        }

        cout << limit << "    ";
        show(xn);
        bool en = error(xn_1, xn);
        bool re = residue(A, b, xn);
        if (en && re) break;
        swap(xn_1,xn);
        cout << endl;
    }

}

void sor(double A[SIZE][SIZE], double b[SIZE]) {
    double omega = 0.5;
    cout << "Metoda sukcesywnej nadrelaksji" << endl;
    if (convergence(A) && omega > 0.0 && omega < 2.0) {
        cout << "Metoda jest zbiezna" << endl;
    }
    double xn[SIZE] = {2.0, 2.0, 2.0, 2.0};
    double right[SIZE] = {0.0, 0.0, 0.0, 0.0};

    for (int limit = 0; limit < MAX; limit++) {
        for (int i = 0; i < SIZE; i++) {
            double sum = ((1.0 - 1.0 / omega) * A[i][i]) * xn[i];

            for (int j = i + 1; j < SIZE; j++) {
                sum += A[i][j] * xn[j];
            }
            right[i] = -sum + b[i];
        }

        double xn_1[SIZE] = {0.0, 0.0, 0.0, 0.0};

        for (int i = 0; i < SIZE; i++) {
            double sum = 0.0;
            for (int j = 0; j <= i; j++) {
                if (i == j) {
                    sum += xn_1[j] * (1.0 / omega) * A[i][i];
                    continue;
                }
                sum += xn_1[j] * A[i][j];
            }
            xn_1[i] = (right[i] - sum) / ((1.0 / omega) * A[i][i]);
        }

        cout << limit << "    ";
        show(xn);
        bool en = error(xn_1, xn);
        bool re = residue(A, b, xn);
        if (en && re) break;
        swap(xn_1, xn);
        cout << endl;
    }

}


int main() {
    double A[SIZE][SIZE] = {{100.0, -1.0,  2.0,   -3.0},
                            {1.0,   200.0, -4.0,  5.0},
                            {-2.0,  4.0,   300.0, -6.0},
                            {3.0,   -5.0,  6.0,   400.0}};
    double b[SIZE] = {116.0, -226.0, 912.0, -1174.0};

    //jacobi(A, b);
    cout << endl;
    gauss_seidel(A, b);
    cout << endl;
    //sor(A, b);

    return 0;
}

