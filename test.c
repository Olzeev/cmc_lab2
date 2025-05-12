#include <stdio.h>
#include <math.h>
#include "test.h"
#include "root.h"
#include "integral.h"

// Тестовые функции и их производные
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
    scanf("%d%d", &i, &j); // ввод номеров функций
    i--;
    j--;
    puts("Interval: ");
    scanf("%lf %lf", &a, &b); // ввод интервала 
    puts("Eps1: ");
    scanf("%lf", &eps1); // ввод eps1
    puts("Eps2: ");
    scanf("%lf", &eps2); // ввод eps2

    printf("Root: %lf\n", root(functions[i], functions[j], a, b, eps1, derivatives[i], derivatives[j])); // вывод их точки пересечения
    printf("Iterations: %d\n", iter); // вывод количества итераций
    // вывод итеграла от первой функции на данном отрезке
    printf("Integral 1: %lf\n", integral(functions[i], a, b, (a + b) / 2, functions[i](a), functions[i](b), functions[i]((a + b) / 2), eps2));
    // вывод интеграла от второй функции на данном отрезке
    printf("Integral 2: %lf\n", integral(functions[j], a, b, (a + b) / 2, functions[j](a), functions[j](b), functions[j]((a + b) / 2), eps2));
}