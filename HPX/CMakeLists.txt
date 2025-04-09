cmake_minimum_required(VERSION 3.15)

project(HPXExample
        VERSION 1.0
        LANGUAGES CXX)

# find HPX
find_package(HPX REQUIRED)

# create executable
add_executable(hpx_daxpy main.cpp)

# set C++ standard to use
target_compile_features(hpx_daxpy PUBLIC cxx_std_17)

# link against necessary libraries
target_link_libraries(hpx_daxpy PUBLIC HPX::hpx)