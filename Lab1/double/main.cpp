#include <iostream>

using namespace std;

int main()
{
    int mantissa = 0;
    double eps = 1.0;
    double temp_eps = 1.0;
    while ((temp_eps + 1.0) > 1.0) {
        eps = temp_eps;
        cout << "Bity mantysy: "<< mantissa << endl;
        mantissa += 1;
        cout << "Epsylon: "<< eps << endl;
        temp_eps = temp_eps/2.0;
    }
    return 0;
}
