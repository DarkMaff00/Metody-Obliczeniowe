#include <iostream>

using namespace std;

int main()
{
    int mantissa;
    double eps;
    double temp_eps = 1.0;
    while ((temp_eps + 1.0) > 1.0) {
        eps = temp_eps;
        mantissa = -log2(eps);
        cout << "Bity mantysy: "<< mantissa << endl;
        cout << "Epsylon: "<< eps << endl;
        temp_eps = temp_eps/2.0;
    }
    return 0;
}
