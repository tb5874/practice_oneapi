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
#include <icx_build_lib.hpp>

//************************************************
// Initialize the vector from 0 to vector_size - 1
//************************************************
void ICX_InitializeVector(std::vector<int>& a) {
    std::cout << "Library check : " << __func__ << "()" << ", Line : " << __LINE__ << "\n";

    for (int i = 0; i < a.size(); i++) {
        a.at(i) = i;
    }
    return;
}

//***************************************************************************
// Vector add in SYCL on device: returns sum in 4th parameter "sum_parallel".
//***************************************************************************
void ICX_VectorAdd(const std::vector<int>& a_vector, const std::vector<int>& b_vector, std::vector<int>& sum_parallel) {

    // Create device selector for the device of your interest.
    // The default device selector will select the most performant device.
    std::cout << "Library check : " << __func__ << "()" << ", Line : " << __LINE__ << "\n";
    auto selector = sycl::cpu_selector_v;

    std::cout << "Library check : " << __func__ << "()" << ", Line : " << __LINE__ << "\n";
    sycl::queue q(selector);

    // Print out the device information used for the kernel code.
    std::cout << "Library check : " << __func__ << "()" << ", Line : " << __LINE__ << "\n";
    std::cout << "Running on device: " << q.get_device().get_info<sycl::info::device::name>() << "\n";
    std::cout << "Vector size: " << a_vector.size() << "\n";

    // Create the range object for the vectors managed by the buffer.
    sycl::range<1> num_items{ a_vector.size() };

    // Create buffers that hold the data shared between the host and the devices.
    // The buffer destructor is responsible to copy the data back to host when it
    // goes out of scope.
    std::cout << "Library check : " << __func__ << "()" << ", Line : " << __LINE__ << "\n";
    sycl::buffer a_buf(a_vector);
    sycl::buffer b_buf(b_vector);
    sycl::buffer sum_buf(sum_parallel.data(), num_items);

    // num_repetitions: How many times to repeat the kernel invocation.
    std::cout << "Library check : " << __func__ << "()" << ", Line : " << __LINE__ << "\n";
    size_t num_repetitions = 1;
    for (size_t i = 0; i < num_repetitions; i++) {
        // Submit a command group to the queue by a lambda function that contains the
        // data access permission and device computation (kernel).
        q.submit(\
            [&](sycl::handler& h) {
                // Create an accessor for each buffer with access permission: read, write or
                // read/write. The accessor is a mean to access the memory in the buffer.
                sycl::accessor a(a_buf, h, sycl::read_only);
                sycl::accessor b(b_buf, h, sycl::read_only);
                // The sum_accessor is used to store (with write permission) the sum data.
                sycl::accessor sum(sum_buf, h, sycl::write_only, sycl::no_init);
                // Use parallel_for to run vector addition in parallel on device. This
                // executes the kernel.
                //    1st parameter is the number of work items.
                //    2nd parameter is the kernel, a lambda that specifies what to do per
                //    work item. The parameter of the lambda is the work item id.
                // SYCL supports unnamed lambda kernel by default.
                h.parallel_for(\
                    num_items,
                    [=](auto i) {
                        sum[i] = a[i] + b[i];
                    });
            });
    };
    // Wait until compute tasks on GPU done
    std::cout << "Library check : " << __func__ << "()" << ", Line : " << __LINE__ << "\n";
    q.wait();
    std::cout << "Library check : " << __func__ << "()" << ", Line : " << __LINE__ << "\n";
    return;
}
