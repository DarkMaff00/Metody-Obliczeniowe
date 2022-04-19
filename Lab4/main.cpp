#include <iostream>

#define MAX 50
#define TOLF 1e-10
#define TOLX 1e-8

using namespace std;

void popraw(const double *m, double *wynik) {
    double x = m[0];
    double y = m[1];
    double z = m[2];

    wynik[0] = (2.0 * x * x * y - y * y + x * x - 1.0) / (2.0 * x + 4.0 * x * y);
    wynik[1] = (y * y + y - 1.0) / (2.0 * y + 1.0);
    wynik[2] = (z * z - 1.0) / (2.0 * z);
}

void funkcje(const double *m, double *wynik) {
    double x = m[0];
    double y = m[1];
    double z = m[2];

    wynik[0] = x * x + y * y + z * z - 2.0;
    wynik[1] = x * x + y * y - 1.0;
    wynik[2] = x * x - y;
}

void show(const double *m) {
    cout << "[";
    for (int i = 0; i < 3; i++) {
        printf("%.10f, ", m[i]);
    }
    cout << "]" << endl;
}

bool stop(const double *en, const double *reziduum) {
    int count = 0;
    for (int i = 0; i < 3; i++) {
        if (en[i] <= TOLX) {
            count++;
        }
    }

    for (int i = 0; i < 3; i++) {
        if (fabs(reziduum[i]) <= TOLF) {
            count++;
        }
    }

    if (count == 6) {
        return true;
    }
    return false;
}

int main() {
    double xn[] = {10.0, 10.0, 10.0};
    double x_n1[3], en[3], reziduum[3], delta[3];

    for (int i = 1; i <= MAX; i++) {
        popraw(xn, delta);

        x_n1[0] = xn[0] - delta[0];
        x_n1[1] = xn[1] - delta[1];
        x_n1[2] = xn[2] - delta[2];

        en[0] = fabs(x_n1[0] - xn[0]);
        en[1] = fabs(x_n1[1] - xn[1]);
        en[2] = fabs(x_n1[2] - xn[2]);

        funkcje(x_n1, reziduum);

        xn[0] = x_n1[0];
        xn[1] = x_n1[1];
        xn[2] = x_n1[2];

        cout << "i=" << i << endl;
        cout << "Przyblizenia:";
        show(xn);
        cout << "en:";
        show(en);
        cout << "Reziduum:";
        show(reziduum);
        cout << endl;

        if (stop(en, reziduum)) {
            break;
        }

    }
    return 0;
}
