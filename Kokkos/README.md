# Kokkos

An DAXPY example using the Kokkos programming framework.
Note always uses the Kokkos default execution space.

```bash
cmake -B build .
cmake --build build
build/kokkos_daxpy
```

The host execution space can be selected using `-DEXAMPLE_USE_HOST_EXECUTION_SPACE=ON`.
For HIP support, additionally set `-DCMAKE_CXX_COMPILER=hipcc`.