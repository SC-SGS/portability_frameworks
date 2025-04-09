#include <iostream>
#include <vector>

int main() {
    const int N = 1024;

    // create and fill used data
    std::vector<double> X(N);
    std::vector<double> Y(N);
    for (int i = 0; i < N; ++i) {
        X[i] = i;
        Y[i] = 2 * i;
    }
    const double alpha = 0.5;

    /*
// CPU only
#pragma omp parallel for
    for (int idx = 0; idx < N; ++idx) {
        Y[idx] = alpha * X[idx] + Y[idx];
    }
    */

    const double *d_X = X.data();
    double *d_Y = Y.data();

    // OpenMP target offloading
#pragma omp target map(tofrom : d_Y[0 : N]) map(to : d_X[0 : N])
#pragma omp teams distribute parallel for
    for (int idx = 0; idx < N; ++idx) {
        d_Y[idx] = alpha * d_X[idx] + d_Y[idx];
    }

    for (int i = 0; i < 10; ++i) {
        std::cout << Y[i] << ' ';
    }
    std::cout << std::endl;

    return 0;
}
