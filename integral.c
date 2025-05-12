#include "integral.h"
#include <math.h>

double ind_integral(double a, double b, double c, double x) {
    return a * x * x * x / 3 + b * x * x / 2 + c * x;
}

double s(double a, double b, double m, 
    double F_a, double F_b, double F_m) 
{
    double c = (F_b - F_a + (F_m - F_a) / (m - a) * (a - b)) / (a - b) / (m - b);
    double d = (F_m - F_a) / (m - a) - c * (m + a);
    double e = F_a - c * a * a - d * a;

    return ind_integral(c, d, e, b) - ind_integral(c, d, e, a);
}

double integral(double (*f)(double), 
    double a, double b, double m, 
    double F_a, double F_b, double F_m, 
    double eps) 
{
    double m1 = (a + m) / 2;
    double m2 = (m + b) / 2;
    double F_m1 = f(m1);
    double F_m2 = f(m2);
    
    double s1 = s(a, m, m1, F_a, F_m, F_m1);
    double s2 = s(m, b, m2, F_m, F_b, F_m2);

    if (fabs(s(a, b, m, F_a, F_b, F_m) - (s1 + s2)) < eps * 15) return s1 + s2;

    else return integral(f, a, m, m1, F_a, F_m, F_m1, eps) + integral(f, m, b, m2, F_m, F_b, F_m2, eps);
}