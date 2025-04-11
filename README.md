# Portability Frameworks

This repository contains hello world DAXPY kernels written in different portable programming languages or frameworks.
All examples are self-sufficient and can easily be compiled using the respective CMakeLists files.

The available languages and frameworks are (the tested versions are included in braces):

- OpenMP (GCC 14.2.0)
- CUDA (12.6.3)
- HPX (1.10.0)
- OpenCL (CUDA/ROCm provided, PoCL 6.0)
- stdpar, C++ standard parallelism (GCC 14.2.0, AdaptiveCpp 24.10.0, icpx 2025.0.0, rocstdpar (upstream LLVM 18), nvhpc 25.3)
- SYCL (AdaptiveCpp 24.10.0, icpx 2025.0.0)
- Kokkos (4.6.00 (CUDA, HIP, SYCL, OpenMP, Threads, HPX, Serial))
- HIP (ROCm 6.2.0, CUDA 12.6.3)

Each kernel computes $y = \alpha \cdot x + y$ for the two vectors $x, y$ of size 1024 and outputs the first 10 elements.