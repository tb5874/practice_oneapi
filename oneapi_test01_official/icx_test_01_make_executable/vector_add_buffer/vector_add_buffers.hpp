#pragma once

#include <sycl/sycl.hpp>
#include <vector>
#include <iostream>
#include <string>

int main(void);

void InitializeVector(std::vector<int>& a);

void VectorAdd(sycl::queue& q, const std::vector<int>& a_vector, const std::vector<int>& b_vector, std::vector<int>& sum_parallel);

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
