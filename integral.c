#include <stdio.h>
#include <math.h>

// Функция вычисления интеграла с заданной точностью методом Симпсона
double integral(double (*f)(double), double a, double b, double eps) {
    int seg_cnt = 1;
    double h = (b - a) / (2 * seg_cnt);

    // сумма значений функции во всех чётных точках
    double sum_even = 0;
    double x = a + 2 * h;
    for (int i = 2; i < 2 * seg_cnt; i += 2) {
        sum_even += f(x);
        x += 2 * h;
    }

    // сумма значений функции во всех нечётных точках 
    x = a + h;
    double sum_odd = 0;
    int end = seg_cnt << 1;
    double k = 2 * h;
    for (int i = 1; i < end; i += 2) {
        sum_odd += f(x);
        x += k;
    }
    

    // значения функции в точках а и b
    double f_a = f(a);
    double f_b = f(b);

    // формула Симпсона
    double int_cur = (f_a + sum_even * 2 + sum_odd * 4 + f_b) * h / 3;

    double int_prev = 0;

    while (fabs(int_cur - int_prev) >= eps * 15) {
        seg_cnt <<= 1;
        int_prev = int_cur;
        h = (b - a) / (seg_cnt << 1);

        // Все точки переходят в четные точки
        sum_even += sum_odd;

        // Новые нечётные точки
        x = a + h;
        sum_odd = 0;

        double k = 2 * h;
        int end = seg_cnt << 1;
        for (int i = 1; i < end; i += 2) {
            sum_odd += f(x);
            x += k;
        }

        int_cur = (f_a + sum_even * 2 + sum_odd * 4 + f_b) * h / 3;
    } 

    return int_cur;
}
