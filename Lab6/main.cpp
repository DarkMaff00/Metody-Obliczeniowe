#include <iostream>

#define SIZE 6
using namespace std;

auto *c = new double[SIZE];

void fill_u(double *u) {
    u[0] = 1.0 / 2.0;
    u[1] = 1.0 / 4.0;
    u[2] = 1.0 / 6.0;
    u[3] = 1.0 / 8.0;
    u[4] = 1.0 / 10.0;
}

void fill_l(double *l) {
    l[0] = 1.0 / 3.0;
    l[1] = 1.0 / 5.0;
    l[2] = 1.0 / 7.0;
    l[3] = 1.0 / 9.0;
    l[4] = 1.0 / 11.0;
}

void fill_d(double *d) {
    d[0] = 10.0;
    d[1] = 20.0;
    d[2] = 30.0;
    d[3] = 30.0;
    d[4] = 20.0;
    d[5] = 10.0;
}

void fill_b(double *b) {
    b[0] = 31.0;
    b[1] = 165.0 / 4.0;
    b[2] = 917.0 / 30.0;
    b[3] = 851.0 / 28.0;
    b[4] = 3637.0 / 90.0;
    b[5] = 332.0 / 11.0;
}

void count_eta(const double *u, double *d, const double *l) {
    for (int i = 1; i < SIZE; i++) {
        c[i] = l[i - 1] / d[i - 1];
        d[i] -= (c[i] * u[i - 1]);
    }
}

void count_r(double *b) {
    for (int i = 1; i < SIZE; i++) {
        b[i] -= c[i] * b[i - 1];
    }
}

void results(const double *d, const double *u, const double *r, double *x) {
    for (int i = SIZE - 1; i >= 0; i--) {
        if (i == (SIZE - 1)) {
            x[i] = r[i] / d[i];
        } else {
            x[i] = (r[i] - (u[i] * x[i + 1])) / d[i];
        }
    }
}

void show(double *vector) {
    for (int i = 0; i < SIZE; i++) {
        printf("x%d = %f\n", i, vector[i]);
    }
    cout << endl;
}

bool check(const double *u, const double *d, const double *l, const double *x, const double *b) {
    int counter = 0;
    double sum;
    sum = d[0] * x[0] + u[0] * x[1];
    if (b[0] - sum == 0.0) {
        counter++;
    }
    for (int i = 0; i < SIZE - 1; i++) {
        sum = l[i] * x[i] + d[i + 1] * x[i + 1] + u[i + 1] * x[i + 2];
        if (b[i + 1] - sum == 0.0) {
            counter++;
        }
    }
    if (counter == SIZE) {
        return true;
    } else {
        return false;
    }
}

void thomas(double *u, double *d, double *l, double *b, double *x) {
    count_eta(u, d, l);
    count_r(b);
    results(d, u, b, x);
    show(x);
}

int main() {
    auto *u = new double[SIZE - 1];
    auto *d = new double[SIZE];
    auto *l = new double[SIZE - 1];
    auto *b = new double[SIZE];
    auto *x = new double[SIZE];
    auto *d2 = new double[SIZE];
    auto *b2 = new double[SIZE];
    fill_u(u);
    fill_l(l);
    fill_d(d);
    fill_b(b);
    fill_d(d2);
    fill_b(b2);

    thomas(u, d, l, b, x);
    if (check(u, d2, l, x, b2)) {
        cout << "Good" << endl;
    } else {
        cout << "Bad" << endl;
    }
    return 0;
}

