#pragma once

#include <vector>
#include <iostream>
#include <string>

extern "C" void ICX_InitializeVector(std::vector<int> & a);

extern "C" void ICX_VectorAdd(const std::vector<int> & a_vector, const std::vector<int> & b_vector, std::vector<int> & sum_parallel);

int main(void);
