//////////////////////////////////////////////////////////////////////////////////////////////////////
//
// [ notice ]
// 
// indent :  4 space
// integer : int64_t
// floating point : float32
// 
//////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// [ dimension ]
// 
// dim.at(000) is 001D, column
// dim.at(001) is 002D, row
// dim.at(002) is 003D, volume
// dim.at(003) is 004D, volume count
// ...
// dim.at(###) is ###D, ###
// 
// example, 4 dimension
// get_ptr = [  type ( 000 x 1D x 2D x 3D   + 000 x 1D x 2D     + 000 x 1D  + 000 ~ 1D ),
//              type (                      +                   + 001 x 1D  + 000 ~ 1D ),
//              type (                      +                   + ... x 1D  + 000 ~ 1D ),
//              type (                      +                   + 2D  x 1D  + 000 ~ 1D ),
//              type (                      + 001 x 1D x 2D     + 000 x 1D  + 000 ~ 1D ),
//              type (                      +                   + 001 x 1D  + 000 ~ 1D ),
//              type (                      +                   + ... x 1D  + 000 ~ 1D ),
//              type (                      +                   + 2D  x 1D  + 000 ~ 1D ),
//              type (                      + ... x 1D x 2D     + 000 x 1D  + 000 ~ 1D ),
//              type (                      +                   + 001 x 1D  + 000 ~ 1D ),
//              type (                      +                   + ... x 1D  + 000 ~ 1D ),
//              type (                      +                   + 2D  x 1D  + 000 ~ 1D ),
//              type (                      + 3D  x 1D x 2D     + 000 x 1D  + 000 ~ 1D ),
//              type (                      +                   + 001 x 1D  + 000 ~ 1D ),
//              type (                      +                   + ... x 1D  + 000 ~ 1D ),
//              type (                      +                   + 2D  x 1D  + 000 ~ 1D ),
// 
//              type ( 001 x 1D x 2D x 3D   + 000 x 1D x 2D     + 000 x 1D  + 000 ~ 1D ),
//              type (                      +                   + 001 x 1D  + 000 ~ 1D ),
//              type (                      +                   + ... x 1D  + 000 ~ 1D ),
//              type (                      +                   + 2D  x 1D  + 000 ~ 1D ),
//              type (                      + 001 x 1D x 2D     + 000 x 1D  + 000 ~ 1D ),
//              type (                      +                   + 001 x 1D  + 000 ~ 1D ),
//              type (                      +                   + ... x 1D  + 000 ~ 1D ),
//              type (                      +                   + 2D  x 1D  + 000 ~ 1D ),
//              type (                      + ... x 1D x 2D     + 000 x 1D  + 000 ~ 1D ),
//              type (                      +                   + 001 x 1D  + 000 ~ 1D ),
//              type (                      +                   + ... x 1D  + 000 ~ 1D ),
//              type (                      +                   + 2D  x 1D  + 000 ~ 1D ),
//              type (                      + 3D  x 1D x 2D     + 000 x 1D  + 000 ~ 1D ),
//              type (                      +                   + 001 x 1D  + 000 ~ 1D ),
//              type (                      +                   + ... x 1D  + 000 ~ 1D ),
//              type (                      +                   + 2D  x 1D  + 000 ~ 1D ),
// 
//              type ( ... x 1D x 2D x 3D   + 000 x 1D x 2D     + 000 x 1D  + 000 ~ 1D ),
//              type (                      +                   + 001 x 1D  + 000 ~ 1D ),
//              type (                      +                   + ... x 1D  + 000 ~ 1D ),
//              type (                      +                   + 2D  x 1D  + 000 ~ 1D ),
//              type (                      + 001 x 1D x 2D     + 000 x 1D  + 000 ~ 1D ),
//              type (                      +                   + 001 x 1D  + 000 ~ 1D ),
//              type (                      +                   + ... x 1D  + 000 ~ 1D ),
//              type (                      +                   + 2D  x 1D  + 000 ~ 1D ),
//              type (                      + ... x 1D x 2D     + 000 x 1D  + 000 ~ 1D ),
//              type (                      +                   + 001 x 1D  + 000 ~ 1D ),
//              type (                      +                   + ... x 1D  + 000 ~ 1D ),
//              type (                      +                   + 2D  x 1D  + 000 ~ 1D ),
//              type (                      + 3D  x 1D x 2D     + 000 x 1D  + 000 ~ 1D ),
//              type (                      +                   + 001 x 1D  + 000 ~ 1D ),
//              type (                      +                   + ... x 1D  + 000 ~ 1D ),
//              type (                      +                   + 2D  x 1D  + 000 ~ 1D ),
// 
//              type ( 4D  x 1D x 2D x 3D   + 000 x 1D x 2D     + 000 x 1D  + 000 ~ 1D ),
//              type (                      +                   + 001 x 1D  + 000 ~ 1D ),
//              type (                      +                   + ... x 1D  + 000 ~ 1D ),
//              type (                      +                   + 2D  x 1D  + 000 ~ 1D ),
//              type (                      + 001 x 1D x 2D     + 000 x 1D  + 000 ~ 1D ),
//              type (                      +                   + 001 x 1D  + 000 ~ 1D ),
//              type (                      +                   + ... x 1D  + 000 ~ 1D ),
//              type (                      +                   + 2D  x 1D  + 000 ~ 1D ),
//              type (                      + ... x 1D x 2D     + 000 x 1D  + 000 ~ 1D ),
//              type (                      +                   + 001 x 1D  + 000 ~ 1D ),
//              type (                      +                   + ... x 1D  + 000 ~ 1D ),
//              type (                      +                   + 2D  x 1D  + 000 ~ 1D ),
//              type (                      + 3D  x 1D x 2D     + 000 x 1D  + 000 ~ 1D ),
//              type (                      +                   + 001 x 1D  + 000 ~ 1D ),
//              type (                      +                   + ... x 1D  + 000 ~ 1D ),
//              type (                      +                   + 2D  x 1D  + 000 ~ 1D ),
// 
//////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// [ std, sycl memory ]
// 
// std::malloc
//      Allocation
//          Desktop std::malloc() start -> [1] Only Desktop
//      Modify & Use
//          O : Desktop
//          X : parallel_for()
//
// sycl::malloc_host ( with queue )
//      Allocation
//          sycl::malloc_host do nothing.
//          Desktop direct asign start -> [1] Only Desktop
//          parallel_for() start -> [1] Desktop [2] Desktop shared GPU memory
//      Modify & Use
//          O : Desktop
//          O : parallel_for()
//
// sycl::malloc_device ( with queue )
//      Allocation
//          sycl::malloc_device do nothing.
//          parallel_for() start -> [1] Only arcA770
//      Modify & Use
//          X : Desktop
//          O : parallel_for()
//
// sycl::malloc_shared ( with queue )
//      Allocation
//          Desktop sycl::malloc_shared() start -> [1] Only Desktop
//          parallel_for() start -> [1] Desktop [2]Desktop shared GPU memory [3] Arc 770
//      Modify & Use
//          O : Desktop
//          O : parallel_for()
//      Use, After parallel_for()
//          X : Desktop
//          O : parallel_for()
//
//////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

// dll - export, import
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

// test title macro
#define TEST_TITLE_MACRO \
printf("\n\n\n\n\n");\
printf("**************************************************\n");\
printf("[ %s ]\n", ((std::string)__func__).c_str());\
printf("**************************************************\n");

// function name macro
#define FUNC_NAME_MACRO \
printf("Func : %s()\n", ((std::string)__func__).c_str());

// function type macro
#define FUNC_TYPE_MACRO \
printf("Func : %s(%s)\n", ((std::string)__func__).c_str(), get_type.c_str());

// check byte macro
#define FUNC_BYTE_MACRO \
printf("Func : %s(%s) : [ total count / total byte ] : [ %lld / %lld byte ]\n",\
    __func__, get_type.c_str(),\
    sizeof_count, sizeof_count * sizeof_byte\
);

// function time macro
#define FUNC_TIME_MACRO \
printf("Func : %s() / Line : %d / %f sec\n", ((std::string)__func__).c_str(), __LINE__, time_tok.count());

// exception catch macro
#define CATCH_MACRO \
catch (std::exception& e) {\
    printf("Func : %s() : Exception : %s\n", ((std::string)__func__).c_str(), e.what());\
}\
catch (...) {\
    printf("Func : %s() : Exception : unknown exception\n", ((std::string)__func__).c_str());\
}

#include <exception>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <limits>

#include <sycl/sycl.hpp>
#include <oneapi/dpl/random>
#include <oneapi/mkl.hpp>
#include <oneapi/mkl/rng/device.hpp>

//#include <sycl/ext/oneapi/backend/level_zero.hpp> ???
//#include <sycl/ext/oneapi/backend/opencl.hpp> ???
//#include <sycl/backend/level_zero.hpp> ???
//#include <sycl/backend/opencl.hpp> ???
//#include <level_zero/ze_api.h> ???

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static std::vector<std::string> static_dev;
static std::vector<std::string> static_dtype;
static std::vector<std::string> static_mtype;
static std::vector<std::string> static_rng;

extern "C" DLL_FLAG void static_setup(void);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern "C" DLL_FLAG void test_std               (void);

extern "C" DLL_FLAG void test_std_memory        (void);
extern "C" DLL_FLAG void test_std_iter_add      (void);
extern "C" DLL_FLAG void test_std_iter_matmul   (void);

extern "C" DLL_FLAG void std_mem_set            (std::string get_type, void*& get_ptr, std::vector<int64_t> get_dim, bool debug_flag);
extern "C" DLL_FLAG void std_mem_init           (std::string get_type, void*& get_ptr, std::vector<int64_t> get_dim, double get_value, bool debug_flag);
extern "C" DLL_FLAG void std_mem_free           (std::string get_type, void*& get_ptr, std::vector<int64_t> get_dim, bool debug_flag);

extern "C" DLL_FLAG void std_iter_print         (std::string get_type, void*& get_buf, std::vector<int64_t> get_dim, bool debug_flag);
extern "C" DLL_FLAG void std_iter_compare       (std::string get_type, void*& get_buf_a, void*& get_buf_b, std::vector<int64_t> get_dim);

extern "C" DLL_FLAG void std_kernel_iter_add    (std::string get_type, void*& get_buf_a, void*& get_buf_b, void*& get_buf_c, std::vector<int64_t> get_dim, bool debug_flag);
extern "C" DLL_FLAG void std_kernel_iter_matmul (std::string get_type, void*& get_buf_a, void*& get_buf_b, void*& get_buf_c, int64_t get_m, int64_t get_n, int64_t get_p, bool debug_flag);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern "C" DLL_FLAG void test_sycl                  (void);

extern "C" DLL_FLAG void test_sycl_variable         (void);
extern "C" DLL_FLAG void test_sycl_selector         (void);
extern "C" DLL_FLAG void test_sycl_device           (void);
extern "C" DLL_FLAG void test_sycl_queue            (void);
extern "C" DLL_FLAG void test_sycl_info             (void);
extern "C" DLL_FLAG void test_sycl_memory           (void);
extern "C" DLL_FLAG void test_sycl_memory_4GB       (void);
extern "C" DLL_FLAG void test_sycl_dimension        (void);
extern "C" DLL_FLAG void test_sycl_buffer_from_host (void);
extern "C" DLL_FLAG void test_sycl_buffer_from_sycl (void);
extern "C" DLL_FLAG void test_sycl_usm              (void);
extern "C" DLL_FLAG void test_sycl_random_dpl       (void);
extern "C" DLL_FLAG void test_sycl_random_mkl       (void);
extern "C" DLL_FLAG void test_sycl_usm_add          (void);
extern "C" DLL_FLAG void test_sycl_usm_matmul       (void);
extern "C" DLL_FLAG void test_sycl_parallel_for     (void);

extern "C" DLL_FLAG void sycl_selector              (std::string get_type, void*& selector_ptr);
extern "C" DLL_FLAG void sycl_device                (std::string get_type, void*& device_ptr);
extern "C" DLL_FLAG void sycl_queue                 (std::string get_type, void*& queue_ptr, void*& get_ptr);
extern "C" DLL_FLAG void sycl_delete                (std::string get_type, void*& get_ptr);
extern "C" DLL_FLAG void sycl_mem_set               (std::string get_type, std::string get_method, void*& queue_ptr, void*& get_ptr, std::vector<int64_t> get_dim, bool debug_flag);
extern "C" DLL_FLAG void sycl_mem_init              (std::string get_type, void*& queue_ptr, void*& get_ptr, std::vector<int64_t> get_dim, double get_value, bool debug_flag);
extern "C" DLL_FLAG void sycl_mem_copy              (std::string get_type, void*& queue_ptr, void*& dst_ptr, void*& src_ptr, std::vector<int64_t> get_dim, bool debug_flag);
extern "C" DLL_FLAG void sycl_mem_free              (std::string get_type, void*& queue_ptr, void*& get_ptr, std::vector<int64_t> get_dim, bool debug_flag);

extern "C" DLL_FLAG void sycl_mkl_rng               (std::string get_type, void*& queue_ptr, void*& rng_ptr, std::uint64_t get_seed);
extern "C" DLL_FLAG void sycl_mkl_delete            (std::string get_type, void*& mkl_ptr);

extern "C" DLL_FLAG void sycl_kernel_dimension      (std::string get_type, void*& queue_ptr, void*& get_buf, std::vector<int64_t> get_dim, bool debug_flag);
extern "C" DLL_FLAG void sycl_kernel_buffer         (std::string get_type, void*& queue_ptr, void*& get_buf_a, void*& get_buf_b, void*& get_buf_c, int64_t get_m, int64_t get_n, int64_t get_p, bool debug_flag);
extern "C" DLL_FLAG void sycl_kernel_usm            (std::string get_type, void*& queue_ptr, void*& get_buf_a, void*& get_buf_b, void*& get_buf_c, int64_t get_m, int64_t get_n, int64_t get_p, bool debug_flag);
extern "C" DLL_FLAG void sycl_kernel_random_dpl     (std::string get_type, void*& queue_ptr, void*& get_buf, std::vector<int64_t> get_dim, bool debug_flag);
extern "C" DLL_FLAG void sycl_kernel_random_mkl     (std::string get_type, void*& queue_ptr, std::string rng_type, std::uint64_t get_seed, double dist_a, double dist_b, void*& get_buf, std::vector<int64_t> get_dim, bool debug_flag);
extern "C" DLL_FLAG void sycl_kernel_usm_add        (std::string get_type, void*& queue_ptr, void*& get_buf_a, void*& get_buf_b, void*& get_buf_c, std::vector<int64_t> get_dim, bool debug_flag);
extern "C" DLL_FLAG void sycl_kernel_usm_matmul     (std::string get_type, void*& queue_ptr, void*& get_buf_a, void*& get_buf_b, void*& get_buf_c, int64_t get_m, int64_t get_n, int64_t get_p, bool debug_flag);
extern "C" DLL_FLAG void sycl_kernel_parallel_for   (std::string get_type, void*& queue_ptr, void*& get_buf_x, void*& get_buf_y, std::vector<int64_t> get_dim, bool debug_flag);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern "C" DLL_FLAG void test_compare(void);

extern "C" DLL_FLAG void test_compare_add(void);
extern "C" DLL_FLAG void test_compare_matmul(void);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern "C" DLL_FLAG void func_softmax_denominator(void*& buf_x, int64_t softmax_start, int64_t softmax_count, float& softmax_denominator, void*& buf_exp);
extern "C" DLL_FLAG void func_softmax(void*& buf_exp, int64_t softmax_start, int64_t softmax_count, float softmax_denominator);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
