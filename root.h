double root(double (*f)(double), double (*g)(double), 
    double a, double b, 
    double eps, 
    double (*der_f)(double), double (*der_g)(double));

extern int iter;