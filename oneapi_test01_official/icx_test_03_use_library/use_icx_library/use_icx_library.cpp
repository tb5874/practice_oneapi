//==============================================================
// Vector Add is the equivalent of a Hello, World! sample for data parallel
// programs. Building and running the sample verifies that your development
// environment is setup correctly and demonstrates the use of the core features
// of SYCL. This sample runs on both CPU and GPU (or FPGA). When run, it
// computes on both the CPU and offload device, then compares results. If the
// code executes on both CPU and offload device, the device name and a success
// message are displayed. And, your development environment is setup correctly!
//
// For comprehensive instructions regarding SYCL Programming, go to
// https://software.intel.com/en-us/oneapi-programming-guide and search based on
// relevant terms noted in the comments.
//
// SYCL material used in the code sample:
// •	A one dimensional array of data.
// •	A device queue, buffer, accessor, and kernel.
//==============================================================
// Copyright © Intel Corporation
//
// SPDX-License-Identifier: MIT
// =============================================================
#include <use_icx_library.hpp>

//****************************************************************************
// Demonstrate vector add both in sequential on CPU and in parallel on device.
//****************************************************************************
int main(void) {

    // Vector type and data size for this example.
    size_t vector_size = 10000;

    // Create vector objects with "vector_size" to store the input and output data.
    std::vector<int> a, b, sum_sequential, sum_parallel;
    a.resize(vector_size);
    b.resize(vector_size);
    sum_sequential.resize(vector_size);
    sum_parallel.resize(vector_size);

    // Initialize input vectors with values from 0 to vector_size - 1
    ICX_InitializeVector(a);
    ICX_InitializeVector(b);

    try {
        // Vector addition in SYCL
        ICX_VectorAdd(a, b, sum_parallel);
    }
    catch (...) {
        std::cout << "An exception is caught for vector add.\n";
        std::terminate();
    }

    // Compute the sum of two vectors in sequential for validation.
    for (size_t i = 0; i < sum_sequential.size(); i++) {
        sum_sequential.at(i) = a.at(i) + b.at(i);
    }

    // Verify that the two vectors are equal.  
    for (size_t i = 0; i < sum_sequential.size(); i++) {
        if (sum_parallel.at(i) != sum_sequential.at(i)) {
            std::cout << "Vector add failed on device.\n";
            return -1;
        }
    }

    int indices[]{ 0, 1, 2, (static_cast<int>(a.size()) - 1) };
    constexpr size_t indices_size = sizeof(indices) / sizeof(int);

    // Print out the result of vector add.
    for (int i = 0; i < indices_size; i++) {
        int j = indices[i];
        if (i == indices_size - 1) std::cout << "...\n";
        std::cout << "[" << j << "]: " << a[j] << " + " << b[j] << " = " << sum_parallel[j] << "\n";
    }

    a.clear();
    b.clear();
    sum_sequential.clear();
    sum_parallel.clear();

    std::cout << "Vector add successfully completed on device.\n";

    return 0;
}
