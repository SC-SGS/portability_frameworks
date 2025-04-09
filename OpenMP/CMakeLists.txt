cmake_minimum_required(VERSION 3.15)

project(OpenMPExample
        VERSION 1.0
        LANGUAGES CXX)

# find OpenMP
find_package(OpenMP REQUIRED)

# create executable
add_executable(openmp_daxpy main.cpp)

# set C++ standard to use
target_compile_features(openmp_daxpy PUBLIC cxx_std_17)

# link against necessary libraries
target_link_libraries(openmp_daxpy PRIVATE OpenMP::OpenMP_CXX)