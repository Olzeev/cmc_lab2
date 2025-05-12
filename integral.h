double ind_integral(double a, double b, double c, double x);

double s(double a, double b, double m, 
    double F_a, double F_b, double F_m);

double integral(double (*f)(double), 
    double a, double b, double m, 
    double F_a, double F_b, double F_m, 
    double eps);

