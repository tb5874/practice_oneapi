#pragma once

#if ( defined(_WIN32) || defined(_WIN64) )

#ifdef EXPORT_FLAG
#define DLL_FLAG __declspec(dllexport)
#else
#define DLL_FLAG __declspec(dllimport)
#endif

#elif ( defined(__unix__) || defined(__linux__) )

#ifdef EXPORT_FLAG
#define DLL_FLAG __attribute__((__visibility__("default")))
#else
#define DLL_FLAG __attribute__((__visibility__("default")))
#endif

#endif

#include <vector>
#include <iostream>
#include <string>

typedef std::vector<int> std::vector<int>;

extern "C" DLL_FLAG void CL_InitializeVector(std::vector<int> & a);
extern "C" DLL_FLAG void CL_VectorAdd(const std::vector<int>& a_vector, const std::vector<int>& b_vector, std::vector<int>& sum_parallel);
