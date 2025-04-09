# stdpar

An DAXPY example using the C++ standard parallelism.
The two SYCL implementations DPCPP/icpx and AdaptiveCpp are supported.

## GCC

To use GCC as stdpar compiler, specify `-DEXAMPLE_STDPAR_IMPLEMENTATION="gcc"`.

```bash
cmake -DEXAMPLE_STDPAR_IMPLEMENTATION="gcc" -DEXAMPLE_SYCL_OFFLOAD_DEVICE_TYPE="cpu" -B build .
cmake --build build
build/stdpar_daxpy
```

The target device must be `cpu`.
Requires a TBB installation.

## nvhpc

To use NVIDIA's nvhpc as stdpar compiler, specify `-DEXAMPLE_STDPAR_IMPLEMENTATION="nvhpc"`.

```bash
cmake -DCMAKE_CXX_COMPILER=nvhpc -DEXAMPLE_STDPAR_IMPLEMENTATION="nvhpc" -DEXAMPLE_SYCL_OFFLOAD_DEVICE_TYPE="gpu" -B build .
cmake --build build
build/stdpar_daxpy
```

The target device, `cpu` or `gpu`, can be switched using the `EXAMPLE_STDPAR_OFFLOAD_DEVICE_TYPE` option.

## icpx

To use Intel's DPC++/icpx as stdpar compiler, specify `-DEXAMPLE_STDPAR_IMPLEMENTATION="icpx"`.

```bash
cmake -DCMAKE_CXX_COPMILER=icpx -DEXAMPLE_STDPAR_IMPLEMENTATION="icpx" -DEXAMPLE_SYCL_OFFLOAD_DEVICE_TYPE="gpu" -B build .
cmake --build build
build/stdpar_daxpy
```

The target device, `cpu` or `gpu`, can be switched using the `EXAMPLE_STDPAR_OFFLOAD_DEVICE_TYPE` option.
Requires an Intel oneDPL installation.
The default device can be changed using the `ONEAPI_DEVICE_SELECTOR` environment variable.

## AdaptiveCpp

To use AdaptiveCpp as stdpar compiler, specify `-DEXAMPLE_SYCL_IMPLEMENTATION="acpp"`.

```bash
cmake -DCMAKE_CXX_COPMILER=acpp -DEXAMPLE_SYCL_IMPLEMENTATION="acpp" -DEXAMPLE_SYCL_OFFLOAD_DEVICE_TYPE="gpu" -B build .
cmake --build build
build/sycl_daxpy
```

The target device, `cpu` or `gpu`, can be switched using the `EXAMPLE_SYCL_OFFLOAD_DEVICE_TYPE` option.
Requires a TBB installation.
The default device can be changed using the `ACPP_VISIBILITY_MASK=` environment variable.

## rocstdpar

Currently not supported. 