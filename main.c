#include <stdio.h>
#include <string.h>
#include "integral.h"
#include "test.h"
#include "root.h"

// функции
extern double _f1(double);
extern double _f2(double);
extern double _f3(double);

// производные функций
extern double _derf1(double);
extern double _derf2(double);
extern double _derf3(double);


int main(char argc, char *argv[]) {
    char print_roots = 0, print_iter = 0;
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-help") == 0) { // вывод всех доступных флагов
            printf("-test: test functions\n-roots: print roots\n-iter: print iterations\n");
            return 0;
        } else if (strcmp(argv[i], "-test") == 0) { // тестирование функций
            test();
            return 0;
        } else if (strcmp(argv[i], "-roots") == 0) { // вывод точек пересечения
            print_roots = 1;
        } else if (strcmp(argv[i], "-iter") == 0) { // вывод количества итераций
            print_iter = 1;
        }
    }
    double eps1 = 0.00008, eps2 = 0.00008;

    double x1 = root(_f1, _f3, 2.1, 3, eps1, _derf1, _derf3); // поиск левой точки пересечения
    if (print_iter)
        printf("Iterations for f1 x f3: %d\n", iter);
    iter = 0;

    double x2 = root(_f2, _f3, 4, 5, eps1, _derf2, _derf3); // поиск средней точки пересечения
    if (print_iter)
        printf("Iterations for f2 x f3: %d\n", iter);
    iter = 0;

    double x3 = root(_f1, _f2, 6, 7, eps1, _derf1, _derf2); // поиск правой точки пересечения
    if (print_iter)
        printf("Iterations for f1 x f2: %d\n", iter);
    iter = 0;

    if (print_roots) 
        printf("Roots: \nf1 x f2: %lf\nf2 x f3: %lf\nf1 x f3: %lf\n", x3, x2, x1); // вывод точек пересечения
    

    double s1 = integral(_f3, x1, x2, eps2); // площадь под y=1/(2-x)+6
    double s2 = integral(_f2, x2, x3, eps2); // площадь под y=-2x+14
    double s3 = integral(_f1, x1, x3, eps2); // площадь под y=ln(x)
    double s_ans = s1 + s2 - s3; // итоговая площадь фигуры
    printf("Square: %lf\n", s_ans);
    
}