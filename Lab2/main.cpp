#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

inline double fx(double x) {
    return ((1.0 - exp(-x)) / x);
}

inline double error(double approx, double result) {
    return fabs((approx - result) / result);
}

double taylor(double x) {
    double step = 1.0;
    double sum = 1.0;

    for (int i = 2; i < 30; i++) {                          // Taylor series for (1-exp(-x)/x) equals 1 - x/2 + x^2/6 - x^3/24 ...
        step *= -x / i;
        sum += step;
    }
    return sum;
}

int main() {
    vector<double> log, x, exp;
    double c1, c2, c3;
    ifstream data("../dane.txt");
    ofstream results("../good_result.txt");
    while (data >> c1 >> c2 >> c3) {
        log.push_back(c1);
        x.push_back(c2);
        exp.push_back(c3);
    }
    double approx_result, relative_error, log_error;
    for (int i = 0; i < log.size(); i++) {
        if (log[i] < 0.0) {
            approx_result = taylor(x[i]);
        } else {
            approx_result = fx(x[i]);
        }
        relative_error = error(approx_result, exp[i]);
        log_error = log10(relative_error);
        results << log[i] << " " << log_error << endl;
    }


    return 0;
}
