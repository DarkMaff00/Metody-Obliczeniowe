#include <iostream>

using namespace std;

int main()
{
    float eps = 1.0f;
    int t = -1;
    do {
        t++;
        eps = eps/2.0f;
        cout <<"t="<< t << endl;
        cout <<"epsylon="<< eps << endl;
    } while (eps + 1.0f > 1.0f);
}

