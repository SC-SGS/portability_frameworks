# CUDA - Compute Unified Device Architecture

An DAXPY example using NVIDIA's CUDA programming language.

```bash
cmake -DCMAKE_CUDA_ARCHITECTURES="80" -B build .
cmake --build build
build/cuda_daxpy
```

The `CMAKE_CUDA_ARCHITECTURES` must be set to the correct SM value for the GPU you wish to target. 