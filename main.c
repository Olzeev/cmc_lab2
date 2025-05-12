#include <stdio.h>
#include <math.h>
#include <string.h>

extern double _f1(double);
extern double _f2(double);
extern double _f3(double);
extern double _derf1(double);
extern double _derf2(double);
extern double _derf3(double);

// Тестовые функции
typedef double (*func)(double);

double g1(double x) {
    return sqrt(x) + 1;
}

double der_g1(double x) {
    return 1 / (2 * sqrt(x));
}

double g2(double x) {
    return -2 * x + 14;
}

double der_g2(double x) {
    return -2;
}
double g3(double x) {
    return 1 / x;
}

double der_g3(double x) {
    return -1 / (x * x);
}
double g4(double x) {
    return x * x;
}

double der_g4(double x) {
    return 2 * x;
}
double g5(double x) {
    return -3 * x + 2;
}

double der_g5(double x) {
    return -3;
}

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

void test(void) {
    
    func functions[] = {g1, g2, g3, g4, g5};
    func derivatives[] = {der_g1, der_g2, der_g3, der_g4, der_g5};
    char *text[] = {"y = sqrt(x) + 1", "y = -2x + 14", "y = 1 / x", "y = x^2", "y = -3x + 2"};
    for (int i = 0; i < 5; ++i) {
        printf("%d) %s\n", i + 1, text[i]);
    }
    int i, j;
    double a, b, eps1, eps2;
    puts("Function numbers (1-5): ");
    scanf("%d%d", &i, &j);
    i--;
    j--;
    puts("Interval: ");
    scanf("%lf %lf", &a, &b);
    puts("Eps1: ");
    scanf("%lf", &eps1);
    puts("Eps2: ");
    scanf("%lf", &eps2);

    printf("Root: %lf\n", root(functions[i], functions[j], a, b, eps1, derivatives[i], derivatives[j]));
    printf("Iterations: %d\n", iter);
    printf("Integral 1: %lf\n", integral(functions[i], a, b, (a + b) / 2, functions[i](a), functions[i](b), functions[i]((a + b) / 2), eps2));
    printf("Integral 2: %lf\n", integral(functions[j], a, b, (a + b) / 2, functions[j](a), functions[j](b), functions[j]((a + b) / 2), eps2));
}

int main(char argc, char *argv[]) {
    char print_roots = 0, print_iter = 0;
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-help") == 0) {
            printf("-test: test functions\n-roots: print roots\n-iter: print iterations\n");
            return 0;
        } else if (strcmp(argv[i], "-test") == 0) {
            test();
            return 0;
        } else if (strcmp(argv[i], "-roots") == 0) {
            print_roots = 1;
        } else if (strcmp(argv[i], "-iter") == 0) {
            print_iter = 1;
        }
    }
    double eps1 = 0.00001, eps2 = 0.000001, a = 2.1;

    double x1 = root(_f1, _f3, a, 5, eps1, _derf1, _derf3);
    if (print_iter)
        printf("Iterations for f1 x f3: %d\n", iter);
    iter = 0;

    double x2 = root(_f2, _f3, a, 7, eps1, _derf2, _derf3);
    if (print_iter)
        printf("Iterations for f2 x f3: %d\n", iter);
    iter = 0;

    double x3 = root(_f1, _f2, a, 7, eps1, _derf1, _derf2);
    if (print_iter)
        printf("Iterations for f1 x f2: %d\n", iter);
    iter = 0;

    if (print_roots) 
        printf("Roots: \nf1 x f2: %lf\nf2 x f3: %lf\nf1 x f3: %lf\n", x3, x2, x1);
    

    double s1 = integral(_f3, x1, x2, (x1 + x2) / 2, _f3(x1), _f3(x2), _f3((x1 + x2) / 2), eps2);
    double s2 = integral(_f2, x2, x3, (x2 + x3) / 2, _f2(x2), _f2(x3), _f2((x2 + x3) / 2), eps2);
    double s3 = integral(_f1, x1, x3, (x1 + x3) / 2, _f1(x1), _f1(x3), _f1((x1 + x3) / 2), eps2);
    double s_ans = s1 + s2 - s3;
    printf("Square: %lf\n", s_ans);
    
}