#include "integral.h"
#include <math.h>

double ind_integral(double a, double b, double c, double x) { // неопределенный интеграл от параболы с коэффициентами a, b, c в точке x
    return a * x * x * x / 3 + b * x * x / 2 + c * x;
}

double s(double a, double b, double m, 
    double F_a, double F_b, double F_m)  // площадь под параболой, проведенной через точки (a, F_a), (b, F_b), (m, F_m)
{
    double c = (F_b - F_a + (F_m - F_a) / (m - a) * (a - b)) / (a - b) / (m - b); // первый коэффициент
    double d = (F_m - F_a) / (m - a) - c * (m + a); // второй коэффициент
    double e = F_a - c * a * a - d * a; // третий коэффициент

    return ind_integral(c, d, e, b) - ind_integral(c, d, e, a); // площадь по формуле Ньютона-Лейбница
}

double integral(double (*f)(double), 
    double a, double b, double m, 
    double F_a, double F_b, double F_m, 
    double eps) // интеграл функции f от a до b, m - середина отрезка, F_a, F_b, F_m - значения функции в этих точках
{
    double m1 = (a + m) / 2; // середина левого отрезка
    double m2 = (m + b) / 2; // середина правого отрезка
    double F_m1 = f(m1);
    double F_m2 = f(m2);
    
    double s1 = s(a, m, m1, F_a, F_m, F_m1); // площадь левой части как площадь под параболой
    double s2 = s(m, b, m2, F_m, F_b, F_m2); // площадь правой части

    if (fabs(s(a, b, m, F_a, F_b, F_m) - (s1 + s2)) < eps * 15) return s1 + s2; // достигли нужной точности
    
    else return integral(f, a, m, m1, F_a, F_m, F_m1, eps) + integral(f, m, b, m2, F_m, F_b, F_m2, eps); 
    // рекурсивно считаем интеграл правой и левой частей
}