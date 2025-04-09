# OpenCL – Open Computing Language

An DAXPY example using the OpenCL programming framework.

```bash
cmake -DEXAMPLE_OPENCL_OFFLOAD_DEVICE_TYPE="gpu" -B build .
cmake --build build
build/opencl_daxpy
```

The target device, `cpu` or `gpu`, can be switched using the `EXAMPLE_OPENCL_OFFLOAD_DEVICE_TYPE` option. 