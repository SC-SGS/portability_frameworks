# OpenMP – Open Multi-Processing

An DAXPY example using the OpenMP programming framework.

```bash
cmake -B build .
cmake --build build
build/openmp_daxpy
```

If you wish to target GPUs with OpenMP's target offload feature, you have to set `CMAKE_CXX_FLAGS` accordingly. 