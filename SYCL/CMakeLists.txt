cmake_minimum_required(VERSION 3.15)

project(SYCLExample
        VERSION 1.0
        LANGUAGES CXX)

# create executable
add_executable(sycl_daxpy main.cpp)

# set C++ standard to use
target_compile_features(sycl_daxpy PUBLIC cxx_std_17)

# check which SYCL implementation is requested
set(EXAMPLE_SYCL_IMPLEMENTATION "" CACHE STRING "Set the SYCL implementation that should be used.")
if (EXAMPLE_SYCL_IMPLEMENTATION STREQUAL "icpx" OR EXAMPLE_SYCL_IMPLEMENTATION STREQUAL "dpcpp")
    if (NOT ${CMAKE_CXX_COMPILER_ID} MATCHES "IntelLLVM")
        message(FATAL_ERROR "Please set CMAKE_CXX_COMPILER to icpx/dpcpp in order to use it as SYCL implementation.")
    endif ()
    # use Intel icpx
    message(STATUS "Using Intel's DPC++/icpx as SYCL compiler.")
    target_compile_options(sycl_daxpy PRIVATE -sycl-std=2020 -fsycl)
    target_link_options(sycl_daxpy PRIVATE -fsycl)
elseif (EXAMPLE_SYCL_IMPLEMENTATION STREQUAL "acpp")
    # set AdaptiveCpp targets of not already done
    if (NOT ACPP_TARGETS)
        set(ACPP_TARGETS "generic" CACHE STRING "The generic SSCP target." FORCE)
    endif ()
    find_package(AdaptiveCpp CONFIG REQUIRED)
    # use AdaptiveCpp
    message(STATUS "Using AdaptiveCpp as SYCL compiler.")
    add_sycl_to_target(TARGET sycl_daxpy SOURCES main.cpp)
else ()
    message(FATAL_ERROR "Unrecognized SYCL implementation: \"${EXAMPLE_SYCL_IMPLEMENTATION}\". Please set EXAMPLE_SYCL_IMPLEMENTATION.")
endif ()

# set the offload device (CPU or GPU)
set(EXAMPLE_SYCL_OFFLOAD_DEVICE_TYPE "gpu" CACHE STRING "Set the SYCL offload device type.")
if (NOT (EXAMPLE_SYCL_OFFLOAD_DEVICE_TYPE STREQUAL "gpu" OR EXAMPLE_SYCL_OFFLOAD_DEVICE_TYPE STREQUAL "cpu"))
    message(FATAL_ERROR "Invalid offload device type: \"${EXAMPLE_SYCL_OFFLOAD_DEVICE_TYPE}\". Must be one of: gpu, cpu.")
endif ()
message(STATUS "Using ${EXAMPLE_SYCL_OFFLOAD_DEVICE_TYPE} as target device.")

# add compile definition
if (EXAMPLE_SYCL_OFFLOAD_DEVICE_TYPE STREQUAL "gpu")
    target_compile_definitions(sycl_daxpy PUBLIC EXAMPLE_SYCL_GPU_DEVICE)
endif ()
