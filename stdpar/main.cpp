#include <execution>
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

    // create the indices used in the for_each loop
    std::vector<int> indices(N);
    std::iota(indices.begin(), indices.end(), 0);

    // the stdpar compute kernel
    std::for_each(std::execution::par_unseq, indices.begin(), indices.end(), [=, d_X = X.data(), d_Y = Y.data()](const int idx) {
        d_Y[idx] = alpha * d_X[idx] + d_Y[idx];
    });

    for (int i = 0; i < 10; ++i) {
        std::cout << Y[i] << ' ';
    }
    std::cout << std::endl;

    return 0;
}
