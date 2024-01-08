#include <use_cl_library.hpp>

int main(void) {


    size_t vector_size = 10000;

    std::vector<int> a, b, sum_sequential, sum_parallel;

    a.resize(vector_size);
    b.resize(vector_size);

    sum_sequential.resize(vector_size);
    sum_parallel.resize(vector_size);

    CL_InitializeVector(a);
    CL_InitializeVector(b);

    CL_VectorAdd(a, b, sum_parallel);

    for (size_t i = 0; i < sum_sequential.size(); i++) {
        sum_sequential.at(i) = a.at(i) + b.at(i);
    }

    for (size_t i = 0; i < sum_sequential.size(); i++) {
        if (sum_parallel.at(i) != sum_sequential.at(i)) {
            std::cout << "Vector add failed on device.\n";
            return -1;
        }
    }

    int indices[]{ 0, 1, 2, (static_cast<int>(a.size()) - 1) };
    constexpr size_t indices_size = sizeof(indices) / sizeof(int);

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
