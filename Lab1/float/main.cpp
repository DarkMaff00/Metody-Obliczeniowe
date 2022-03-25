#include <iostream>

using namespace std;

int main()
{
    int mantissa;
    float eps;
    float temp_eps = 1.0f;
    while ((temp_eps + 1.0f) > 1.0f) {
        eps = temp_eps;
        mantissa = -log2(eps);
        cout << "Bity mantysy: "<< mantissa << endl;
        cout << "Epsylon: "<< eps << endl;
        temp_eps = temp_eps/2.0f;
    }
    return 0;
}

