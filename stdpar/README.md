# stdpar

An DAXPY example using the C++ standard parallelism.

## GCC

To use GCC as stdpar compiler, specify `-DEXAMPLE_STDPAR_IMPLEMENTATION="gcc"`.

```bash
cmake -DEXAMPLE_STDPAR_IMPLEMENTATION="gcc" -DEXAMPLE_STDPAR_OFFLOAD_DEVICE_TYPE="cpu" -B build .
cmake --build build
build/stdpar_daxpy
```

The target device must be `cpu`.
Requires a TBB installation.

## nvhpc

To use NVIDIA's nvhpc as stdpar compiler, specify `-DEXAMPLE_STDPAR_IMPLEMENTATION="nvhpc"`.

```bash
cmake -DCMAKE_CXX_COMPILER=nvc++ -DEXAMPLE_STDPAR_IMPLEMENTATION="nvhpc" -DEXAMPLE_STDPAR_OFFLOAD_DEVICE_TYPE="gpu" -B build .
cmake --build build
build/stdpar_daxpy
```

The target device, `cpu` or `gpu`, can be switched using the `EXAMPLE_STDPAR_OFFLOAD_DEVICE_TYPE` option.

## icpx

To use Intel's DPC++/icpx as stdpar compiler, specify `-DEXAMPLE_STDPAR_IMPLEMENTATION="icpx"`.

```bash
cmake -DCMAKE_CXX_COMPILER=icpx -DEXAMPLE_STDPAR_IMPLEMENTATION="icpx" -DEXAMPLE_STDPAR_OFFLOAD_DEVICE_TYPE="gpu" -B build .
cmake --build build
build/stdpar_daxpy
```

The target device, `cpu` or `gpu`, can be switched using the `EXAMPLE_STDPAR_OFFLOAD_DEVICE_TYPE` option.
Requires an Intel oneDPL installation.
The default device can be changed using the `ONEAPI_DEVICE_SELECTOR` environment variable.
Note that the respective `-fsycl-targets` flag depends on the targeted GPU and must be separately set via
`CMAKE_CXX_FLAGS`.

The target flags are:

- CPUs: `-fsycl -fsycl-targets=spir64_x86_64 -Xsycl-target-backend=spir64_x86_64 -march=avx512`
- NVIDIA GPUs: `-fsycl -fsycl-targets=nvptx64-nvidia-cuda -Xsycl-target-backend=nvptx64-nvidia-cuda --offload-arch=sm_80`
- AMD GPUs: `-fsycl -fsycl-targets=amdgcn-amd-amdhsa -Xsycl-target-backend=amdgcn-amd-amdhsa --offload-arch=gfx90a`
- Intel GPUs: `-fsycl -fsycl-targets=spir64_gen -Xsycl-target-backend=spir64_gen -device 0xe20b`

## AdaptiveCpp

To use AdaptiveCpp as stdpar compiler, specify `-DEXAMPLE_STDPAR_IMPLEMENTATION="acpp"`.

```bash
cmake -DCMAKE_CXX_COMPILER=acpp -DEXAMPLE_STDPAR_IMPLEMENTATION="acpp" -DEXAMPLE_STDPAR_OFFLOAD_DEVICE_TYPE="gpu" -B build .
cmake --build build
build/stdpar_daxpy
```

Requires a TBB installation.
The default device can be changed using the `ACPP_VISIBILITY_MASK=` environment variable.

## rocstdpar

To use rocstdpar as stdpar compiler, specify `-DEXAMPLE_STDPAR_IMPLEMENTATION="rocstdpar"`.

```bash
cmake -DCMAKE_CXX_COMPILER=clang++ -DEXAMPLE_STDPAR_IMPLEMENTATION="rocstdpar" -DEXAMPLE_STDPAR_OFFLOAD_DEVICE_TYPE="gpu" -B build .
cmake --build build
build/stdpar_daxpy
```

The target device must be `gpu`.
Upstream LLVM 18 can be used as rocstdpar compiler. 