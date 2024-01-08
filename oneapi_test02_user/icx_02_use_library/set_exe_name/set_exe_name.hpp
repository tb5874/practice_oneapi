#pragma once

#include <exception>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>

extern "C" void static_setup(void);
extern "C" void test_std(void);
extern "C" void test_sycl(void);
extern "C" void test_compare(void);

int main(void);
