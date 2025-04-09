#include <iostream>
#include <vector>

// the CUDA compute kernel
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
    cudaMalloc(&d_X, N * sizeof(double));
    cudaMalloc(&d_Y, N * sizeof(double));
    // copy data to the device
    cudaMemcpy(d_X, X.data(), N * sizeof(double), cudaMemcpyHostToDevice);
    cudaMemcpy(d_Y, Y.data(), N * sizeof(double), cudaMemcpyHostToDevice);

    // perform computations
    saxpy<<<(N + 255) / 256, 256>>>(alpha, d_X, d_Y, N);

    // copy data to the host
    cudaMemcpy(Y.data(), d_Y, N * sizeof(double), cudaMemcpyDeviceToHost);
    // free the resources
    cudaFree(d_X);
    cudaFree(d_Y);

    for (int i = 0; i < 10; ++i) {
        std::cout << Y[i] << ' ';
    }
    std::cout << std::endl;

    return 0;
}
