#include <iostream>

#define MAX 50
#define TOLF 1e-10
#define TOLX 1e-8

using namespace std;

double function(double x) {
    return tan(2.0 * x) - x - 1.0;
}

double functionPicard(double x) {
    return tan(2.0 * x) - 1.0;
}

double derivative(double x) {
    return (2.0 / (cos(2.0 * x) * cos(2.0 * x))) - 1.0;
}

double derivativePicard(double x) {
    return 2.0 / (cos(2.0 * x) * cos(2.0 * x));
}

void picardMethod(double x) {
    cout << "-------------------Metoda Picarda---------------------" << endl;

    if (fabs(derivativePicard(x)) > 1.0) {
        cout << "Wartosc bezwzgledna pochodnej Phi(x) jest wieksza od 1 -> Rozbieznosc" << endl;
    } else {
        double en, reziduum;
        double x_n1 = x;
        for (int i = 1; i <= MAX; i++) {
            x_n1 = functionPicard(x_n1);
            en = fabs(x_n1 - x);
            x = x_n1;
            reziduum = fabs(function(x));
            printf("i=%d xn=%.10f en=%.10f Reziduum=%.10f\n", i, x, en, reziduum);
            if ((reziduum <= TOLF) && (en <= TOLX)) {
                break;
            }
        }
    }
}

void bisectionMethod(double a, double b) {
    cout << "--------------------Metoda Bisekcji----------------------" << endl;
    if ((function(a) > 0.0 && function(b) > 0.0) || (function(b) < 0.0 && function(a) < 0.0) ) {
        cout << "Wartosc f(x) na koncach powina byc roznych znakow" << endl;
    } else {
        double left = a;
        double right = b;
        double xn = (left + right) / 2.0;
        double en = (right - left) / 2.0;
        double reziduum = function(xn);

        for (int i = 1; i <= MAX; i++) {
            printf("i=%d a=%.10f b=%.10f xn=%.10f en=%.10f Reziduum=%.10f\n", i, left, right, xn, en, reziduum);
            if ((fabs(reziduum) <= TOLF) && (fabs(en) <= TOLX)) {
                break;
            }

            if ((function(left) < 0.0 && function(xn) > 0.0) || (function(xn) < 0.0 && function(left) > 0.0)) {
                right = xn;
            } else {
                left = xn;
            }

            xn = (left + right) / 2.0;
            en = (right - left) / 2.0;
            reziduum = function(xn);
        }
    }
}

void newtonMethod(double x) {
    cout << "---------------------------Metoda Newtona------------------------" << endl;
    double xn = x;
    double x_n1, en, reziduum;

    for (int i = 1; i <= MAX; i++) {
        x_n1 = xn - (function(xn) / derivative(xn));
        en = fabs(x_n1 - xn);
        xn = x_n1;
        reziduum = fabs(function(xn));
        printf("i=%d xn=%.10f en=%.10f Reziduum=%.10f\n", i, xn, en, reziduum);

        if ((reziduum <= TOLF) && (en <= TOLX)) {
            break;
        }
    }
}

void secantMethod(double x, double x_n1) {
    cout << "---------------------------Metoda Siecznych------------------------" << endl;
    double x_n2 = x_n1 - (function(x_n1) / ((function(x_n1) - function(x)) / (x_n1 - x)));
    double en = fabs(x_n2 - x_n1);
    double reziduum = fabs(function(x_n2));

    for (int i = 1; i <= MAX; i++) {
        printf("i=%d xn=%.10f en=%.10f Reziduum=%.10f\n", i, x_n2, en, reziduum);
        x = x_n1;
        x_n1 = x_n2;

        x_n2 = x_n1 - (function(x_n1) / ((function(x_n1) - function(x)) / (x_n1 - x)));
        if ((reziduum <= TOLF) && (en <= TOLX)) {
            break;
        }
        en = fabs(x_n2 - x_n1);
        reziduum = fabs(function(x_n2));

    }


}

int main() {
    cout << "tan(2x) - x - 1 = 0" << endl;
    picardMethod(-2.0);
    bisectionMethod(-2.1, -1.8);
    newtonMethod(-1.7);
    secantMethod(-1.6, -1.4);
    return 0;
}


