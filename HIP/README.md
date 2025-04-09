# HIP – Heterogeneous-computing Interface for Portability

An DAXPY example using AMD's HIP programming language.

```bash
cmake -DCMAKE_HIP_ARCHITECTURES="gfx906" -B build .
cmake --build build
build/hip_daxpy
```

The `CMAKE_HIP_ARCHITECTURES` must be set to the correct gfx value for the GPU you wish to target. 

The `HIP_PLATFORM` environment variable can be used to switch between support for AMD and NVIDIA GPUs.
To target NVIDIA GPUs with HIP, use: 

```bash
export HIP_PLATFORM="nvidia"
cmake -DCMAKE_CUDA_ARCHITECTURES="86" -B build .
cmake --build build
build/hip_daxpy
```

Again, the `CMAKE_CUDA_ARCHITECTURES` must be set to the correct SM value for the GPU you wish to target. 