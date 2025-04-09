# Portability Frameworks

This repository contains hello world DAXPY kernels written in different portable programming languages or frameworks. 
All examples are self-sufficient and can easily be compiled using the respective CMakeLists files. 

The available languages and frameworks are:
- OpenMP
- CUDA
- HPX
- OpenCL
- C++ standard parallelism (stdpar)
- SYCL
- Kokkos
- HIP

Each kernel computes $y = \alpha \cdot x + y$ for the two vectors $x, y$ of size 1024 and outputs the first 10 elements. 