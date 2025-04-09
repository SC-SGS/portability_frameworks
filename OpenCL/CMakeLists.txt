cmake_minimum_required(VERSION 3.15)

project(OpenCLExample
        VERSION 1.0
        LANGUAGES CXX)

# find OpenCL
find_package(OpenCL REQUIRED)

# create executable
add_executable(opencl_daxpy main.cpp)

# set C++ standard to use
target_compile_features(opencl_daxpy PUBLIC cxx_std_17)

# link against necessary libraries
target_compile_definitions(opencl_daxpy PUBLIC CL_TARGET_OPENCL_VERSION=220)
target_include_directories(opencl_daxpy PUBLIC ${OpenCL_INCLUDE_DIRS})
target_link_libraries(opencl_daxpy PUBLIC OpenCL)

# set the offload device (CPU or GPU)
set(EXAMPLE_OPENCL_OFFLOAD_DEVICE_TYPE "gpu" CACHE STRING "Set the OpenCL offload device type.")
if (NOT (EXAMPLE_OPENCL_OFFLOAD_DEVICE_TYPE STREQUAL "gpu" OR EXAMPLE_OPENCL_OFFLOAD_DEVICE_TYPE STREQUAL "cpu"))
    message(FATAL_ERROR "Invalid offload device type: \"${EXAMPLE_OPENCL_OFFLOAD_DEVICE_TYPE}\". Must be one of: gpu, cpu.")
endif ()
message(STATUS "Using ${EXAMPLE_OPENCL_OFFLOAD_DEVICE_TYPE} as target device.")

# add compile definition
if (EXAMPLE_OPENCL_OFFLOAD_DEVICE_TYPE STREQUAL "gpu")
    target_compile_definitions(opencl_daxpy PUBLIC EXAMPLE_OPENCL_GPU_DEVICE)
endif ()