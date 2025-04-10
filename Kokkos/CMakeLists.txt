cmake_minimum_required(VERSION 3.15)

project(KokkosExample
        VERSION 1.0
        LANGUAGES CXX)

# find Kokkos
find_package(Kokkos REQUIRED)

# create executable
add_executable(kokkos_daxpy main.cpp)

# set C++ standard to use
target_compile_features(kokkos_daxpy PUBLIC cxx_std_17)

# link against necessary libraries
target_link_libraries(kokkos_daxpy PUBLIC Kokkos::kokkos)

# icpx specific Kokkos flags for the Kokkos SYCL backend
if (Kokkos_ENABLE_SYCL)
    target_compile_options(kokkos_daxpy PRIVATE -sycl-std=2020 -fsycl)
    target_link_options(kokkos_daxpy PRIVATE -fsycl)
endif ()