#include "root.h"


int iter = 0;
double root(double (*f)(double), double (*g)(double), 
    double a, double b, 
    double eps, 
    double (*der_f)(double), double (*der_g)(double)) 
{
    double mid = (a + b) / 2;
    double der1 = der_f(mid) - der_g(mid);
    double der2 = (f(mid) - g(mid) >= (f(a) - g(a) + f(b) - g(b)) / 2) ? -1 : 1;
    int flag = (der1 * der2 > 0 ? 1 : 0);

    while (b - a >= eps) {
        if (flag) {
            // Метод касательных
            double der_Fb = der_f(b) - der_g(b);
            b -= (f(b) - g(b)) / der_Fb;

            // Метод хорд
            double k = ((f(b) - g(b)) - (f(a) - g(a))) / (b - a);
            a -= (f(a) - g(a)) / k;
        } else {
            // Метод касательных
            double der_Fa = der_f(a) - der_g(a);
            a -= (f(a) - g(a)) / der_Fa;

             // Метод хорд
            double k = ((f(b) - g(b)) - (f(a) - g(a))) / (b - a);
            b -= (f(b) - g(b)) / k; 
        }
        iter++;
    }
    return (a + b) / 2;

}