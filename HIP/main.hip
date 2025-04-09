#include "hip/hip_runtime.h"
#include "hip/hip_runtime_api.h"

#include <iostream>
#include <vector>

// the HIP compute kernel
__global__ void saxpy(const double alpha, const double *X, double *Y, const int N) {
    const int idx = blockDim.x * blockIdx.x + threadIdx.x;
    if (idx < N) {
        Y[idx] = alpha * X[idx] + Y[idx];
    }
}

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

    double *d_X, *d_Y;
    // allocate memory on the device
    hipMalloc(&d_X, N * sizeof(double));
    hipMalloc(&d_Y, N * sizeof(double));
    // copy data to the device
    hipMemcpy(d_X, X.data(), N * sizeof(double), hipMemcpyHostToDevice);
    hipMemcpy(d_Y, Y.data(), N * sizeof(double), hipMemcpyHostToDevice);

    // perform computations
    saxpy<<<(N + 255) / 256, 256>>>(alpha, d_X, d_Y, N);

    // copy data to the host
    hipMemcpy(Y.data(), d_Y, N * sizeof(double), hipMemcpyDeviceToHost);
    // free the resources
    hipFree(d_X);
    hipFree(d_Y);

    for (int i = 0; i < 10; ++i) {
        std::cout << Y[i] << ' ';
    }
    std::cout << std::endl;

    return 0;
}
