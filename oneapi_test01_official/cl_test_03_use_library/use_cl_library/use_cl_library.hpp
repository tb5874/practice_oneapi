#pragma once

#include <vector>
#include <iostream>
#include <string>

typedef std::vector<int> std::vector<int>;

extern "C" void CL_InitializeVector(std::vector<int> & a);

extern "C" void CL_VectorAdd(const std::vector<int> & a_vector, const std::vector<int> & b_vector, std::vector<int> & sum_parallel);

int main(void);
