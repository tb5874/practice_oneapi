#pragma once

#include <vector>
#include <iostream>
#include <string>

typedef std::vector<int> std::vector<int>;

int main(void);

extern "C" void ICX_InitializeVector(std::vector<int> & a);

extern "C" void ICX_VectorAdd(const std::vector<int> & a_vector, const std::vector<int> & b_vector, std::vector<int> & sum_parallel);
