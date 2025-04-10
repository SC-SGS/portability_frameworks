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

# set the execution space
set(EXAMPLE_USE_HOST_EXECUTION_SPACE OFF CACHE STRING "Set to ON of the host execution space should be used.")

# add compile definition
if (EXAMPLE_USE_HOST_EXECUTION_SPACE)
    target_compile_definitions(kokkos_daxpy PUBLIC EXAMPLE_USE_HOST_EXECUTION_SPACE)
endif ()