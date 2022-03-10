#include <iostream>

using namespace std;

int main()
{
    double eps = 1.0;
    int t = -1;
    do {
        t++;
        eps = eps/2.0;
        cout <<"t="<< t << endl;
        cout <<"epsylon="<< eps << endl;
    } while (eps + 1.0 > 1.0);
}
