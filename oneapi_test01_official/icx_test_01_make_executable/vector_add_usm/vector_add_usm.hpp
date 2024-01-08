#pragma once

#include <sycl/sycl.hpp>
#include <array>
#include <iostream>
#include <string>



int main(void);

void InitializeArray(int* a, size_t size);

void VectorAdd(sycl::queue& q, const int* a, const int* b, int* sum, size_t size);

// Create an exception handler for asynchronous SYCL exceptions : -->
static auto exception_handler = [](sycl::exception_list e_list) {
    for (std::exception_ptr const& e : e_list) {
        try {
            std::rethrow_exception(e);
        }
        catch (std::exception const& e) {
            std::cout << "Failure" << std::endl;
            std::terminate();
        }
    }
};
// Create an exception handler for asynchronous SYCL exceptions : <--
