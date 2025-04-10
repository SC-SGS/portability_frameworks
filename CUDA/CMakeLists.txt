cmake_minimum_required(VERSION 3.15)

project(CUDAExample
        VERSION 1.0
        LANGUAGES CXX)

# find CUDA
include(CheckLanguage)
check_language(CUDA)
enable_language(CUDA)
find_package(CUDAToolkit REQUIRED)

# set necessary flags
set(CMAKE_CUDA_STANDARD 17)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)

# create executable
add_executable(cuda_daxpy main.cu)

# set C++ standard to use
target_compile_features(cuda_daxpy PUBLIC cxx_std_17)

# link against necessary libraries
target_link_libraries(cuda_daxpy PUBLIC CUDA::cudart)