#include <stdio.h>
#include <string.h>
#include "integral.h"
#include "test.h"
#include "root.h"


extern double _f1(double);
extern double _f2(double);
extern double _f3(double);
extern double _derf1(double);
extern double _derf2(double);
extern double _derf3(double);


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