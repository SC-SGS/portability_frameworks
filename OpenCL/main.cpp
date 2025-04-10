#include "CL/cl.h"

#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

const char *kernel_source = R"KS(
__kernel void saxpy(const double alpha, __global double *X, __global double *Y) {
    const int idx = get_global_id(0);
    Y[idx] = alpha * X[idx] + Y[idx];
}
)KS";

int main() {
    const int N = 1024;

    // create and fill used data
    std::vector<double> X(N);
    std::vector<double> Y(N);
    for (int i = 0; i < N; ++i) {
        X[i] = i;
        Y[i] = 2 * i;
    }
    const double alpha = 0.5;

    cl_uint num_platforms{};
    clGetPlatformIDs(0, nullptr, &num_platforms);
    std::vector<cl_platform_id> platforms(num_platforms);
    clGetPlatformIDs(num_platforms, platforms.data(), nullptr);

    cl_device_id device;
    bool device_found{ false };
    // iterate over all platforms to get the correct one
    for (int i = 0; i < num_platforms; ++i) {
#if defined(EXAMPLE_OPENCL_GPU_DEVICE)
        cl_int err = clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_GPU, 1, &device, nullptr);
#else
        cl_int err = clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_CPU, 1, &device, nullptr);
#endif
        if (err == CL_SUCCESS) {
            device_found = true;
            break;
        }
    }

    // check if a device could be found
    if (!device_found) {
        std::cerr << "Couldn't find the requested device type." << std::endl;
        return 1;
    }

    // get device name
    std::size_t name_length{};
    clGetDeviceInfo(device, CL_DEVICE_NAME, 0, nullptr, &name_length);
    std::string device_name(name_length - 1, '\0');
    clGetDeviceInfo(device, CL_DEVICE_NAME, name_length, device_name.data(), nullptr);
    std::cout << device_name << std::endl;

    cl_context context = clCreateContext(nullptr, 1, &device, nullptr, nullptr, nullptr);
    cl_command_queue queue = clCreateCommandQueueWithProperties(context, device, 0, nullptr);

    cl_mem d_X = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, N * sizeof(double), X.data(), nullptr);
    cl_mem d_Y = clCreateBuffer(context, CL_MEM_COPY_HOST_PTR, N * sizeof(double), Y.data(), nullptr);

    cl_program program = clCreateProgramWithSource(context, 1, &kernel_source, nullptr, nullptr);
    clBuildProgram(program, 1, &device, nullptr, nullptr, nullptr);
    cl_kernel kernel = clCreateKernel(program, "saxpy", nullptr);

    clSetKernelArg(kernel, 0, sizeof(double), &alpha);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &d_X);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &d_Y);

    size_t global_size = N;
    clEnqueueNDRangeKernel(queue, kernel, 1, nullptr, &global_size, nullptr, 0, nullptr, nullptr);
    clEnqueueReadBuffer(queue, d_Y, CL_TRUE, 0, N * sizeof(double), Y.data(), 0, nullptr, nullptr);

    clReleaseMemObject(d_X);
    clReleaseMemObject(d_Y);
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseCommandQueue(queue);
    clReleaseContext(context);

    for (int i = 0; i < 10; ++i) {
        std::cout << Y[i] << ' ';
    }
    std::cout << std::endl;

    return 0;
}
