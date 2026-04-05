// método de newton
double newton(double (*f)(double), double (*df)(double), double x0, int max_iter = 100) {
    for (int i = 0; i < max_iter; ++i) {
        x0 -= f(x0) / df(x0);
    }
    return x0;
}
