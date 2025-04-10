#include "sycl/sycl.hpp"

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

    // create a SYCL queue specifying WHERE the code should run
#if defined(EXAMPLE_SYCL_GPU_DEVICE)
    sycl::queue q{ sycl::gpu_selector_v };
#else
    sycl::queue q{ sycl::cpu_selector_v };
#endif
    std::cout << q.get_device().get_info<sycl::info::device::name>() << std::endl;

    // allocate memory on the device
    double *d_X = sycl::malloc_device<double>(N, q);
    double *d_Y = sycl::malloc_device<double>(N, q);
    // copy data to the device
    const sycl::event e1 = q.copy(X.data(), d_X, N);
    const sycl::event e2 = q.copy(Y.data(), d_Y, N);

    // the SYCL compute kernel
    const sycl::event e3 = q.parallel_for(sycl::range<1>{ N }, { e1, e2 }, [=](const sycl::id<1> idx) {
        d_Y[idx] = alpha * d_X[idx] + d_Y[idx];
    });

    // copy data to the host
    sycl::event e4 = q.copy(d_Y, Y.data(), N, e3);
    // free the resources
    e4.wait();
    sycl::free(d_X, q);
    sycl::free(d_Y, q);

    for (int i = 0; i < 10; ++i) {
        std::cout << Y[i] << ' ';
    }
    std::cout << std::endl;

    return 0;
}
