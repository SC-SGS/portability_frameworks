#include "Kokkos_Core.hpp"

#include <iostream>
#include <vector>

template <typename T>
using host_view_type = Kokkos::View<T *, Kokkos::HostSpace, Kokkos::MemoryUnmanaged>;

int main() {
    Kokkos::initialize();
    {
        const int N = 1024;

        // create and fill used data
        std::vector<double> X(N);
        std::vector<double> Y(N);
        for (int i = 0; i < N; ++i) {
            X[i] = i;
            Y[i] = 2 * i;
        }
        const double alpha = 0.5;

        // allocate memory on the device
        Kokkos::View<double *> d_X("X", N);
        Kokkos::View<double *> d_Y("Y", N);
        // copy data to the device
        Kokkos::deep_copy(d_X, host_view_type<double>{ X.data(), N });
        Kokkos::deep_copy(d_Y, host_view_type<double>{ Y.data(), N });

        // the Kokkos compute kernel
        Kokkos::parallel_for("saxpy", N, KOKKOS_LAMBDA(const int idx) { d_Y(idx) = alpha * d_X(idx) + d_Y(idx); });
        Kokkos::fence();

        // copy data to the host
        Kokkos::deep_copy(host_view_type<double>{ Y.data(), N }, d_Y);

        for (int i = 0; i < 10; ++i) {
            std::cout << Y[i] << ' ';
        }
    }
    Kokkos::finalize();
    return 0;
}
