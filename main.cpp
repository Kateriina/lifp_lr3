#include <iostream>
#include <random>

class mt19937;

using namespace std;

double GetRandomNumber()
{
    std::random_device rd;  // Будет использоваться для получения начального числа для механизма случайных чисел
    std::mt19937 gen(rd()); // Стандартный mersenne_twister_engine, засеянный с помощью rd ()
    std::uniform_real_distribution<> dis(0.0, 1.0);
    return dis(gen);
}
int main() {
    int n = 0;
    double err = 1;
    double err_given = 0.15;
    while (err > err_given){
        double w[2][2];
        for ( int n = 0; n < 2; n++){
            for ( int m = 0; m < 2;m++){
                w[n][m] = GetRandomNumber();
            }
        }

        for ( int n = 0; n < 2; n++){
            for ( int m = 0; m < 2;m++){
                cout << "w[" << n+1 << "][" << m+1 << "] = " << w[n][m] << " ";
            }
            cout << endl;
        }

        int x1 = 1, x2 = 0;
        int d1 = 0, d2 = 1;

        //giperb
        double k1 = 2;
        double s1 = x1 * w[0][0] + x2 * w[1][0];
        double  y1 = tanh(s1 / k1);

        //sigm
        double k2 = 0.9;
        double s2 = x1 * w[0][1] + x2 * w[1][1];
        double y2 = 1 / (1 + exp(-s2*k2));

        double e1 = d1 - y1;
        double e2 = d2 - y2;

        double nn = GetRandomNumber();
        w[0][0] -= nn*e1 * x1;
        w[1][0] -= nn*e1 * x2;
        w[0][1] -= nn*e2 * x1;
        w[1][1] -= nn*e2 * x2;

        err = e1*e1 + e2*e2;
        cout << "s1 = " << s1 << endl;
        cout << "y1 = " << y1 << endl;
        cout << "s2 = " << s2 << endl;
        cout << "y2 = " << y2 << endl;
        cout << "err = " << err << endl;
        cout << endl;
    }
    return 0;
}
