#include <cl_build_lib.hpp>

void CL_InitializeVector(std::vector<int>& a) {
    std::cout << "Library check : " << __func__ << "()"<< ", Line : " << __LINE__ << "\n";

    for (int i = 0; i < a.size(); i++) {
        a.at(i) = i;
    }
}

void CL_VectorAdd(const std::vector<int>& a_vector, const std::vector<int>& b_vector, std::vector<int>& sum_parallel) {
    std::cout << "Library check : " << __func__ << "()" << ", Line : " << __LINE__ << "\n";

    for (size_t i = 0; i < sum_parallel.size(); i++) {
        sum_parallel.at(i) = a_vector.at(i) + b_vector.at(i);
    }

    return;
}