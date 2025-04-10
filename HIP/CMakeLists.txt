cmake_minimum_required(VERSION 3.15)

project(HIPExample
        VERSION 1.0
        LANGUAGES CXX)

set(EXAMPLE_HIP_RUNTIME "")
if (DEFINED ENV{HIP_PLATFORM})
    if ($ENV{HIP_PLATFORM} MATCHES "amd")
        set(EXAMPLE_HIP_RUNTIME "HIP" CACHE STRING "Target AMD GPUs via HIP." FORCE)
    elseif ($ENV{HIP_PLATFORM} MATCHES "nvidia")
        set(EXAMPLE_HIP_RUNTIME "CUDA" CACHE STRING "Target NVIDIA GPUs via HIP." FORCE)
    else ()
        message(FATAL_ERROR "Invalid HIP_PLATFORM: \"$ENV{HIP_PLATFORM}\"")
    endif ()
else ()
    # assume we are targeting AMD hardware
    set(EXAMPLE_HIP_RUNTIME "HIP" CACHE STRING "Target AMD GPUs via HIP." FORCE)
endif ()
message(STATUS "Using ${EXAMPLE_HIP_RUNTIME} as HIP runtime.")

# find HIP
include(CheckLanguage)
check_language(${EXAMPLE_HIP_RUNTIME})
enable_language(${EXAMPLE_HIP_RUNTIME})
find_package(HIP)

# set necessary flags
set(CMAKE_HIP_STANDARD 17)
set(CMAKE_HIP_STANDARD_REQUIRED ON)

# create executable
add_executable(hip_daxpy main.hip)

# set C++ standard to use
target_compile_features(hip_daxpy PUBLIC cxx_std_17)

# link against necessary libraries
target_link_libraries(hip_daxpy PUBLIC hip::device hip::host)
set_source_files_properties(main.hip PROPERTIES LANGUAGE ${EXAMPLE_HIP_RUNTIME})
set_target_properties(hip_daxpy PROPERTIES LINKER_LANGUAGE ${EXAMPLE_HIP_RUNTIME})