cmake_minimum_required(VERSION 3.15)

project(stdparExample
        VERSION 1.0
        LANGUAGES CXX)

# create executable
add_executable(stdpar_daxpy main.cpp)

# set C++ standard to use
target_compile_features(stdpar_daxpy PUBLIC cxx_std_17)

# set the offload target (CPU or GPU)
set(EXAMPLE_STDPAR_OFFLOAD_DEVICE_TYPE "gpu" CACHE STRING "Set the stdpar offload device type.")
if (NOT (EXAMPLE_STDPAR_OFFLOAD_DEVICE_TYPE STREQUAL "gpu" OR EXAMPLE_STDPAR_OFFLOAD_DEVICE_TYPE STREQUAL "cpu"))
    message(FATAL_ERROR "Invalid offload device type: \"${EXAMPLE_STDPAR_OFFLOAD_TARGET}\". Must be one of: gpu, cpu.")
endif ()

# check which stdpar implementation is requested
set(EXAMPLE_STDPAR_IMPLEMENTATION "" CACHE STRING "Set the stdpar implementation that should be used.")
if (EXAMPLE_STDPAR_IMPLEMENTATION STREQUAL "gcc")
    if (NOT EXAMPLE_STDPAR_OFFLOAD_DEVICE_TYPE STREQUAL "cpu")
        message(FATAL_ERROR "gcc only supports cpu as offload target.")
    endif ()
    # GNU GCC + TBB as stdpar implementation
    message(STATUS "Using ${EXAMPLE_STDPAR_IMPLEMENTATION} as stdpar implementation.")

    # must be linked against tbb
    find_package(TBB REQUIRED)
    target_link_libraries(stdpar_daxpy PUBLIC TBB::tbb)
elseif (EXAMPLE_STDPAR_IMPLEMENTATION STREQUAL "nvhpc")
    if (NOT ${CMAKE_CXX_COMPILER_ID} STREQUAL "NVHPC")
        message(FATAL_ERROR "Please set CMAKE_CXX_COMPILER to nvc++ in order to use it as stdpar implementation.")
    endif ()
    # nvhpc as stdpar implementation
    message(STATUS "Using ${EXAMPLE_STDPAR_IMPLEMENTATION} as stdpar implementation.")

    # must be linked against CUDA
    include(CheckLanguage)
    check_language(CUDA)
    enable_language(CUDA)
    find_package(CUDAToolkit REQUIRED)

    if (EXAMPLE_STDPAR_OFFLOAD_DEVICE_TYPE STREQUAL "cpu")
        target_compile_options(stdpar_daxpy PUBLIC -stdpar=multicore)
    else ()
        target_compile_options(stdpar_daxpy PUBLIC -stdpar=gpu)
    endif ()
elseif (EXAMPLE_STDPAR_IMPLEMENTATION STREQUAL "icpx")
    if (NOT ${CMAKE_CXX_COMPILER_ID} MATCHES "IntelLLVM")
        message(FATAL_ERROR "Please set CMAKE_CXX_COMPILER to icpx in order to use it as stdpar implementation.")
    endif ()
    # Intel icpx as stdpar implementation
    message(STATUS "Using ${EXAMPLE_STDPAR_IMPLEMENTATION} as stdpar implementation.")

    # must be linked against SYCL
    target_compile_options(stdpar_daxpy PUBLIC -fsycl)
    target_link_options(stdpar_daxpy PUBLIC -fsycl)

    if (EXAMPLE_STDPAR_OFFLOAD_DEVICE_TYPE STREQUAL "cpu")
        target_compile_options(stdpar_daxpy PUBLIC -fsycl-pstl-offload=cpu)
        target_link_options(stdpar_daxpy PUBLIC -fsycl-pstl-offload=cpu)
    else ()
        target_compile_options(stdpar_daxpy PUBLIC -fsycl-pstl-offload=gpu)
        target_link_options(stdpar_daxpy PUBLIC -fsycl-pstl-offload=gpu)
    endif ()

    # must be linked against oneDPL
    find_package(oneDPL REQUIRED)
    target_link_libraries(stdpar_daxpy PUBLIC oneDPL)
elseif (EXAMPLE_STDPAR_IMPLEMENTATION STREQUAL "acpp")
    # AdaptiveCpp as stdpar implementation
    message(STATUS "Using ${EXAMPLE_STDPAR_IMPLEMENTATION} as stdpar implementation.")

    # set AdaptiveCpp targets of not already done
    if (NOT ACPP_TARGETS)
        set(ACPP_TARGETS "generic" CACHE STRING "The generic SSCP target." FORCE)
    endif ()

    find_package(AdaptiveCpp CONFIG REQUIRED)

    # must be linked against SYCL
    target_compile_options(stdpar_daxpy PUBLIC --acpp-stdpar --acpp-stdpar-unconditional-offload)

    # must be linked against tbb
    find_package(TBB REQUIRED)
    target_link_libraries(stdpar_daxpy PUBLIC TBB::tbb)
elseif (EXAMPLE_STDPAR_IMPLEMENTATION STREQUAL "rocstdpar")
    # AMD rocstdpar as stdpar implementation
    message(STATUS "Using ${EXAMPLE_STDPAR_IMPLEMENTATION} as stdpar implementation.")

    # must be linked against HIP
    include(CheckLanguage)
    check_language(HIP)
    enable_language(HIP)
    find_package(HIP REQUIRED)

    # set compilation flags
    target_compile_options(stdpar_daxpy PUBLIC --hipstdpar)
    target_link_libraries(stdpar_daxpy PUBLIC hip::device hip::host)
else ()
    message(FATAL_ERROR "Unrecognized stdpar implementation: \"${EXAMPLE_STDPAR_IMPLEMENTATION}\"")
endif ()
