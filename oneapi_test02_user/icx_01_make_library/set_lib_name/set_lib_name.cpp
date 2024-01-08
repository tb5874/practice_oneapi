#include <set_lib_name.hpp>

//////////////////////////////////////////////////////////////////////////////////////////////////////

void static_setup(void) {
    try {

        // device type
        static_dev.clear();
        static_dev.push_back("default");    // if you have gpu, default is gpu. if not, cpu.
        static_dev.push_back("cpu");
        static_dev.push_back("gpu");
        static_dev.push_back("aspect");     // arcA770 : gpu + fp16 + fp32

        // type - data
        static_dtype.clear();
        static_dtype.push_back("char*");    // for test 1 byte
        static_dtype.push_back("int*");     // for test 4 byte
        static_dtype.push_back("float*");   // for test 4 byte

        // type - memory
        static_mtype.clear();
        static_mtype.push_back("host");
        static_mtype.push_back("device");
        static_mtype.push_back("shared");

    }
    CATCH_MACRO

    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////





















//////////////////////////////////////////////////////////////////////////////////////////////////////

// standard test

void test_std(void) {
    try {               

        test_std_memory();
        test_std_iter_add();
        test_std_iter_matmul();

    }
    CATCH_MACRO

    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// standard memory - new, init, delete

void test_std_memory(void) {
    try {

        TEST_TITLE_MACRO

        int64_t M = 64;
        int64_t N = 64;
        int64_t P = 64;

        // Matrix A : M x N
        std::vector<int64_t> dim_a;
        dim_a.clear();
        dim_a.push_back(N); // 1D, column
        dim_a.push_back(M); // 2D, row
        dim_a.push_back(1); // 3D, volum
        dim_a.push_back(1); // 4D, volum count
        dim_a.push_back(1); // 5D, 6D, ...

        // Matrix B : N x P
        std::vector<int64_t> dim_b;
        dim_b.clear();
        dim_b.push_back(P);
        dim_b.push_back(N);

        // Matrix C : M x P
        std::vector<int64_t> dim_c;
        dim_c.clear();
        dim_c.push_back(P); 
        dim_c.push_back(M); 

        void* ptr_a = nullptr;
        void* ptr_b = nullptr;
        void* ptr_c = nullptr;

        // [ Test ]
        for (int iter_dtype = 0; iter_dtype < static_dtype.size(); iter_dtype++) {

            printf("\n\n");

            std_mem_set(static_dtype.at(iter_dtype), ptr_a, dim_a, false);
            std_mem_set(static_dtype.at(iter_dtype), ptr_b, dim_b, false);
            std_mem_set(static_dtype.at(iter_dtype), ptr_c, dim_c, false);

            std_mem_init(static_dtype.at(iter_dtype), ptr_a, dim_a, (double)1.0, false);
            std_mem_init(static_dtype.at(iter_dtype), ptr_b, dim_b, (double)2.0, false);
            std_mem_init(static_dtype.at(iter_dtype), ptr_c, dim_c, (double)3.0, false);

            std_iter_print(static_dtype.at(iter_dtype), ptr_a, dim_a, false);
            std_iter_print(static_dtype.at(iter_dtype), ptr_b, dim_b, false);
            std_iter_print(static_dtype.at(iter_dtype), ptr_c, dim_c, false);

            std_mem_free(static_dtype.at(iter_dtype), ptr_a, dim_a, false);
            std_mem_free(static_dtype.at(iter_dtype), ptr_b, dim_b, false);
            std_mem_free(static_dtype.at(iter_dtype), ptr_c, dim_c, false);

        }

    }
    CATCH_MACRO

    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void test_std_iter_add(void) {
    try {

        TEST_TITLE_MACRO

        int64_t M = 64;
        int64_t N = 64;

        std::vector<int64_t> dim_a;
        dim_a.clear();
        dim_a.push_back(N);
        dim_a.push_back(M);

        std::vector<int64_t> dim_b;
        dim_b.clear();
        dim_b.push_back(N);
        dim_b.push_back(M);

        std::vector<int64_t> dim_c;
        dim_c.clear();
        dim_c.push_back(N);
        dim_c.push_back(M);

        void* ptr_a = nullptr;
        void* ptr_b = nullptr;
        void* ptr_c = nullptr;

        // [ Test ]
        for (int iter_dtype = 0; iter_dtype < static_dtype.size(); iter_dtype++) {

            printf("\n\n");

            std_mem_set(static_dtype.at(iter_dtype), ptr_a, dim_a, false);
            std_mem_set(static_dtype.at(iter_dtype), ptr_b, dim_b, false);
            std_mem_set(static_dtype.at(iter_dtype), ptr_c, dim_c, false);

            std_mem_init(static_dtype.at(iter_dtype), ptr_a, dim_a, (double)1.0, false);
            std_mem_init(static_dtype.at(iter_dtype), ptr_b, dim_b, (double)1.0, false);
            std_mem_init(static_dtype.at(iter_dtype), ptr_c, dim_c, (double)0.0, false);

            std_kernel_iter_add(static_dtype.at(iter_dtype), ptr_a, ptr_b, ptr_c, dim_c, true);

            std_iter_print(static_dtype.at(iter_dtype), ptr_c, dim_c, false);

            std_mem_free(static_dtype.at(iter_dtype), ptr_a, dim_a, false);
            std_mem_free(static_dtype.at(iter_dtype), ptr_b, dim_b, false);
            std_mem_free(static_dtype.at(iter_dtype), ptr_c, dim_c, false);

        }

    }
    CATCH_MACRO

    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void test_std_iter_matmul(void) {
    try {

        TEST_TITLE_MACRO

        int64_t M = 64;
        int64_t N = 64;
        int64_t P = 64;

        std::vector<int64_t> dim_a;
        dim_a.clear();
        dim_a.push_back(N);
        dim_a.push_back(M);

        std::vector<int64_t> dim_b;
        dim_b.clear();
        dim_b.push_back(P);
        dim_b.push_back(N);

        std::vector<int64_t> dim_c;
        dim_c.clear();
        dim_c.push_back(P);
        dim_c.push_back(M);

        void* ptr_a = nullptr;
        void* ptr_b = nullptr;
        void* ptr_c = nullptr;

        // [ Test ]
        for (int iter_dtype = 0; iter_dtype < static_dtype.size(); iter_dtype++) {

            printf("\n\n");

            std_mem_set(static_dtype.at(iter_dtype), ptr_a, dim_a, false);
            std_mem_set(static_dtype.at(iter_dtype), ptr_b, dim_b, false);
            std_mem_set(static_dtype.at(iter_dtype), ptr_c, dim_c, false);

            std_mem_init(static_dtype.at(iter_dtype), ptr_a, dim_a, (double)1.0, false);
            std_mem_init(static_dtype.at(iter_dtype), ptr_b, dim_b, (double)1.0, false);
            std_mem_init(static_dtype.at(iter_dtype), ptr_c, dim_c, (double)0.0, false);

            std_kernel_iter_matmul(static_dtype.at(iter_dtype), ptr_a, ptr_b, ptr_c, M, N, P, true);

            std_iter_print(static_dtype.at(iter_dtype), ptr_c, dim_c, false);

            std_mem_free(static_dtype.at(iter_dtype), ptr_a, dim_a, false);
            std_mem_free(static_dtype.at(iter_dtype), ptr_b, dim_b, false);
            std_mem_free(static_dtype.at(iter_dtype), ptr_c, dim_c, false);

        }

    }
    CATCH_MACRO

    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// standard memory set

void std_mem_set(std::string get_type, void*& get_ptr, std::vector<int64_t> get_dim, bool debug_flag) {
    try {

        FUNC_TYPE_MACRO

        int64_t sizeof_byte = 0;

        int64_t sizeof_count = 1;
        for (int64_t iter = 0; iter < get_dim.size(); iter++) {
            sizeof_count = sizeof_count * get_dim.at(iter);
        }

        // [ Type 01, new style ]
        if (get_type == "char*") {
            sizeof_byte = sizeof(char);
            get_ptr = new char[sizeof_count];
        }
        else if (get_type == "int*") {
            sizeof_byte = sizeof(int);
            get_ptr = new int[sizeof_count];
        }
        else if (get_type == "float*") {
            sizeof_byte = sizeof(float);
            get_ptr = new float[sizeof_count];
        }
        else if (get_type == "vector<int>*") {
            sizeof_byte = sizeof(int);
            get_ptr = new std::vector<int>;
            ((std::vector<int>*)get_ptr)->resize(sizeof_count);
        }
        else {
            // [ #D pointer ]
            // [ 2D sample ]
            // get_ptr = new type* [ 2D ]
            // for (int iter_2D = 0; iter_2D < 2D; iter_2D++)
            //     ((type**)get_ptr)[iter_2D] = new type[ 1D ]
            // get_ptr = [ type* ( 000 ) ][ type ( 000 ~ 1D ) ]
            //           [ type* ( 001 ) ][ type ( 000 ~ 1D ) ]
            //           [ type* ( ... ) ][ type ( 000 ~ 1D ) ]
            //           [ type* ( 2D  ) ][ type ( 000 ~ 1D ) ]
            throw std::exception("need to update");
        }

        // [ Type 02, malloc style ]
        // if (get_type == "###")
        //     get_ptr = (###*)std::malloc( sizeof(###) * total_count )

        if (debug_flag) {
            FUNC_BYTE_MACRO
        }

    }
    CATCH_MACRO

    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void std_mem_init(std::string get_type, void*& get_ptr, std::vector<int64_t> get_dim, double get_value, bool debug_flag) {
    try {

        FUNC_TYPE_MACRO

        int64_t sizeof_byte = 0;

        int64_t sizeof_count = 1;
        for (int64_t iter = 0; iter < get_dim.size(); iter++) {
            sizeof_count = sizeof_count * get_dim.at(iter);
        }

        if (get_type == "char*") {
            sizeof_byte = sizeof(char);
            char value = (char)get_value;
            for (int64_t iter = 0; iter < sizeof_count; iter++) {
                ((char*)get_ptr)[iter] = value;
            }
        }
        else if (get_type == "int*") {
            sizeof_byte = sizeof(int);
            int value = (int)get_value;
            for (int64_t iter = 0; iter < sizeof_count; iter++) {
                ((int*)get_ptr)[iter] = value;
            }
        }
        else if (get_type == "float*") {
            sizeof_byte = sizeof(float);
            float value = (float)get_value;
            for (int64_t iter = 0; iter < sizeof_count; iter++) {
                ((float*)get_ptr)[iter] = value;
            }
        }
        else if (get_type == "vector<int>*") {
            sizeof_byte = sizeof(int);
            int value = (int)get_value;
            for (int64_t iter = 0; iter < sizeof_count; iter++) {
                ((std::vector<int>*)get_ptr)->at(iter) = value;
            }
        }
        else {
            throw std::exception("need to update");
        }

        if (debug_flag) {
            FUNC_BYTE_MACRO
        }

    }
    CATCH_MACRO

    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void std_mem_free(std::string get_type, void*& get_ptr, std::vector<int64_t> get_dim, bool debug_flag) {
    try {

        FUNC_TYPE_MACRO

        int64_t sizeof_byte = 0;

        int64_t sizeof_count = 1;
        for (int64_t iter = 0; iter < get_dim.size(); iter++) {
            sizeof_count = sizeof_count * get_dim.at(iter);
        }

        // [ Type 01, delete style ]
        if (get_type == "char*") {
            sizeof_byte = sizeof(char);
            delete (char*)get_ptr;
            get_ptr = nullptr;
        }
        else if (get_type == "int*") {
            sizeof_byte = sizeof(int);
            delete (int*)get_ptr;
            get_ptr = nullptr;
        }
        else if (get_type == "float*") {
            sizeof_byte = sizeof(float);
            delete (float*)get_ptr;
            get_ptr = nullptr;
        }
        else if (get_type == "vector<int>*") {
            sizeof_byte = sizeof(int);
            delete (std::vector<int>*)get_ptr;
            get_ptr = nullptr;
        }
        else {
            // [ #D pointer ]
            // [ 2D sample ]
            // for (int iter_2D = 0; iter_2D < 2D; iter_2D++)
            //     delete ((type**)get_ptr)[iter_2D]
            //     ((type**)get_ptr)[iter_2D] = nullptr
            // delete ((type**)get_ptr);
            throw std::exception("need to update");
        }

        // [ Type 02, free style ] 
        // if (get_type == "###")
        //     std::free( (###*)get_ptr )
        //     get_ptr = nullptr

        if (debug_flag) {
            FUNC_BYTE_MACRO
        }

    }
    CATCH_MACRO

    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void std_iter_print(std::string get_type, void*& get_buf, std::vector<int64_t> get_dim, bool debug_flag) {
    try {

        FUNC_TYPE_MACRO

        int64_t sizeof_count = 1;
        for (int64_t iter = 0; iter < get_dim.size(); iter++) {
            sizeof_count = sizeof_count * get_dim.at(iter);
        }

        if (get_type == "char*") {
            for (int64_t iter = 0; iter < sizeof_count; iter++) {
                if(debug_flag) printf("Func : %s(%s) : [ idx %lld : %d ]\n", __func__, get_type.c_str(), iter, ((char*)get_buf)[iter]);
            }
        }
        else if (get_type == "int*") {
            for (int64_t iter = 0; iter < sizeof_count; iter++) {
                if (debug_flag) printf("Func : %s(%s) : [ idx %lld : %d ]\n", __func__, get_type.c_str(), iter, ((int*)get_buf)[iter]);
            }
        }
        else if (get_type == "float*") {
            for (int64_t iter = 0; iter < sizeof_count; iter++) {
                if (debug_flag) printf("Func : %s(%s) : [ idx %lld : %f ]\n", __func__, get_type.c_str(), iter, ((float*)get_buf)[iter]);
            }
        }
        else {
            throw std::exception("need to update");
        }

    }
    CATCH_MACRO

    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void std_iter_compare(std::string get_type, void*& get_buf_a, void*& get_buf_b, std::vector<int64_t> get_dim) {
    try {

        FUNC_TYPE_MACRO

        int64_t sizeof_count = 1;
        for (int64_t iter = 0; iter < get_dim.size(); iter++) {
            sizeof_count = sizeof_count * get_dim.at(iter);
        }

        if (get_type == "char*") {

            char* buf_a = (char*)get_buf_a;
            char* buf_b = (char*)get_buf_b;

            for (int64_t itr = 0; itr < sizeof_count; itr++) {
                bool result_flag = (buf_a[itr] == buf_b[itr]);
                if (result_flag == false) {
                    printf("index : %lld is different.\n", itr);
                    throw std::exception("fail");
                }
            }

        }
        else if (get_type == "int*") {

            int* buf_a = (int*)get_buf_a;
            int* buf_b = (int*)get_buf_b;

            for (int64_t itr = 0; itr < sizeof_count; itr++) {
                bool result_flag = (buf_a[itr] == buf_b[itr]);
                if (result_flag == false) {
                    printf("index : %lld is different.\n", itr);
                    throw std::exception("fail");
                }
            }

        }
        else if (get_type == "float*") {

            float* buf_a = (float*)get_buf_a;
            float* buf_b = (float*)get_buf_b;

            for (int64_t itr = 0; itr < sizeof_count; itr++) {
                float get_tolerance = std::fabs(buf_a[itr] - buf_b[itr]);
                bool result_flag = ( get_tolerance < std::numeric_limits<float>::epsilon() );
                if (result_flag == false) {
                    printf("index : %lld is different.\n", itr);
                    throw std::exception("fail");
                }
            }

        }        
        else {
            throw std::exception("need to update");
        }

        printf("Func : %s() : all index is same.\n", ((std::string)__func__).c_str());

    }
    CATCH_MACRO

    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void std_kernel_iter_add(std::string get_type, void*& get_buf_a, void*& get_buf_b, void*& get_buf_c, std::vector<int64_t> get_dim, bool debug_flag) {
    try {

        FUNC_TYPE_MACRO

        std::chrono::system_clock::time_point time_tick;
        std::chrono::duration<double>time_tok;

        int64_t get_col = get_dim.at(0);
        int64_t get_row = get_dim.at(1);

        int64_t a_col = get_col;
        int64_t b_col = get_col;
        int64_t c_col = get_col;

        if (get_type == "char*") {

            char* buf_a = (char*)get_buf_a;
            char* buf_b = (char*)get_buf_b;
            char* buf_c = (char*)get_buf_c;

            time_tick = std::chrono::system_clock::now();
            for (int64_t row = 0; row < get_row; row++) {
                for (int64_t col = 0; col < get_col; col++) {
                    buf_c[c_col * row + col] = buf_a[a_col * row + col] + buf_b[b_col * row + col];
                }
            }
            time_tok = std::chrono::system_clock::now() - time_tick;
            if (debug_flag) {
                FUNC_TIME_MACRO
            }

        }
        else if (get_type == "int*") {

            int* buf_a = (int*)get_buf_a;
            int* buf_b = (int*)get_buf_b;
            int* buf_c = (int*)get_buf_c;

            time_tick = std::chrono::system_clock::now();
            for (int64_t row = 0; row < get_row; row++) {
                for (int64_t col = 0; col < get_col; col++) {
                    buf_c[c_col * row + col] = buf_a[a_col * row + col] + buf_b[b_col * row + col];
                }
            }
            time_tok = std::chrono::system_clock::now() - time_tick;
            if (debug_flag) {
                FUNC_TIME_MACRO
            }

        }
        else if (get_type == "float*") {

            float* buf_a = (float*)get_buf_a;
            float* buf_b = (float*)get_buf_b;
            float* buf_c = (float*)get_buf_c;

            time_tick = std::chrono::system_clock::now();
            for (int64_t row = 0; row < get_row; row++) {
                for (int64_t col = 0; col < get_col; col++) {
                    buf_c[c_col * row + col] = buf_a[a_col * row + col] + buf_b[b_col * row + col];
                }
            }
            time_tok = std::chrono::system_clock::now() - time_tick;
            if (debug_flag) {
                FUNC_TIME_MACRO
            }

        }
        else {
            throw std::exception("need to update");
        }

    }
    CATCH_MACRO

    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void std_kernel_iter_matmul(std::string get_type, void*& get_buf_a, void*& get_buf_b, void*& get_buf_c, int64_t get_m, int64_t get_n, int64_t get_p, bool debug_flag) {
    try {

        FUNC_TYPE_MACRO

        std::chrono::system_clock::time_point time_tick;
        std::chrono::duration<double>time_tok;

        int64_t get_col = get_p;
        int64_t get_row = get_m;
        int64_t get_itr = get_n;

        int64_t a_col = get_n;
        int64_t b_col = get_p;
        int64_t c_col = get_p;

        if (get_type == "char*") {

            char* buf_a = (char*)get_buf_a;
            char* buf_b = (char*)get_buf_b;
            char* buf_c = (char*)get_buf_c;

            time_tick = std::chrono::system_clock::now();
            for (int64_t m = 0; m < get_row; m++) {
                for (int64_t p = 0; p < get_col; p++) {
                    for (int64_t n = 0; n < get_itr; n++) {
                        buf_c[c_col * m + p] += buf_a[a_col * m + n] * buf_b[b_col * n + p];
                    }
                }
            }
            time_tok = std::chrono::system_clock::now() - time_tick;
            if (debug_flag) {
                FUNC_TIME_MACRO
            }

        }
        else if (get_type == "int*") {

            int* buf_a = (int*)get_buf_a;
            int* buf_b = (int*)get_buf_b;
            int* buf_c = (int*)get_buf_c;

            time_tick = std::chrono::system_clock::now();
            for (int64_t m = 0; m < get_row; m++) {
                for (int64_t p = 0; p < get_col; p++) {
                    for (int64_t n = 0; n < get_itr; n++) {
                        buf_c[c_col * m + p] += buf_a[a_col * m + n] * buf_b[b_col * n + p];
                    }
                }
            }
            time_tok = std::chrono::system_clock::now() - time_tick;
            if (debug_flag) {
                FUNC_TIME_MACRO
            }

        }
        else if (get_type == "float*") {

            float* buf_a = (float*)get_buf_a;
            float* buf_b = (float*)get_buf_b;
            float* buf_c = (float*)get_buf_c;

            time_tick = std::chrono::system_clock::now();
            for (int64_t m = 0; m < get_row; m++) {
                for (int64_t p = 0; p < get_col; p++) {
                    for (int64_t n = 0; n < get_itr; n++) {
                        buf_c[c_col * m + p] += buf_a[a_col * m + n] * buf_b[b_col * n + p];
                    }
                }
            }
            time_tok = std::chrono::system_clock::now() - time_tick;
            if (debug_flag) {
                FUNC_TIME_MACRO
            }

        }
        else {
            throw std::exception("need to update");
        }
    }
    CATCH_MACRO

    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////















//////////////////////////////////////////////////////////////////////////////////////////////////////

// sycl test

void test_sycl(void) {
    try {

        test_sycl_variable();
        test_sycl_selector();
        test_sycl_device();
        test_sycl_queue();
        test_sycl_info();
        test_sycl_memory();
        test_sycl_memory_4GB();
        test_sycl_dimension();
        test_sycl_buffer_from_host();
        test_sycl_buffer_from_sycl();
        test_sycl_usm();
        test_sycl_random();
        test_sycl_usm_add();
        test_sycl_usm_matmul();

    }
    CATCH_MACRO

    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// 
// [ Test 01 ]  : double -> float32
//              : [ O ]
// 
// [ Test 02 ]  : double -> float32 -> std::uint16_t
//              : [ X ]
// 
// [ Test 03 ]  : double -> float32 -> sycl::half
//              : [ O ]
// 
// [ Test 04 ]  : double -> sycl::half
//              : [ O ]
// 
// [ Test 05 ]  : double -> sycl::half -> std::uint16_t
//              : [ X ]
// 
// [ Test 06 ]  : double -> sycl::half -> float32
//              : [ O ]
// 
// [ Test 07 ]  : double -> sycl::half -> sycl::detail::half2Float() -> float32
//              : [ X ]
// 
// [ Test 08 ]  : double -> sycl::half -> sycl::detail::float2Half() -> std::uint16_t
//              : [ O ]
// 
// [ Test 09 ]  : double -> float32 ->  sycl::detail::float2Half() -> std::uint16_t
//              : [ O ]
// 
// [ Test 10 ]  : std::uint16_t '12263' is almost float32 '0.1234'
//              : std::uint16_t -> sycl::detail::half2Float() -> float32
//              : [ O ]
// 
// [ Test 11 ]  : std::uint16_t '12263' is almost float32 '0.1234'
//              : std::uint16_t -> sycl::detail::half2Float() -> sycl::half
//              : [ O ]
// 
//////////////////////////////////////////////////////////////////////////////////////////////////////
void test_sycl_variable(void) {
    try {

        TEST_TITLE_MACRO

        std::uint16_t test_uint16 = 0;
        float test_float32 = 0.0;
        sycl::half test_sycl_half = 0.0;

        // [ Test 01 ]
        test_float32 = 0.1234567891011121314151617181920;

        // [ Test 02 ]
        test_float32 = 0.1234567891011121314151617181920;
        test_uint16 = test_float32;

        // [ Test 03 ]
        test_float32 = 0.1234567891011121314151617181920;
        test_sycl_half = test_float32;

        // [ Test 04 ]
        test_sycl_half = 0.1234567891011121314151617181920;

        // [ Test 05 ]
        test_sycl_half = 0.1234567891011121314151617181920;
        test_uint16 = test_sycl_half;

        // [ Test 06 ]
        test_sycl_half = 0.1234567891011121314151617181920;
        test_float32 = test_sycl_half;

        // [ Test 07 ]
        test_sycl_half = 0.1234567891011121314151617181920;
        test_float32 = sycl::detail::half2Float(test_sycl_half);

        // [ Test 08 ]
        test_sycl_half = 0.1234567891011121314151617181920;
        test_uint16 = sycl::detail::float2Half(test_sycl_half);

        // [ Test 09 ]
        test_float32 = 0.1234567891011121314151617181920;
        test_uint16 = sycl::detail::float2Half(test_float32);

        // [ Test 10 ]
        test_uint16 = 12263;
        test_float32 = sycl::detail::half2Float(test_uint16);

        // [ Test 11 ]
        test_uint16 = 12263;
        test_sycl_half = sycl::detail::half2Float(test_uint16);

    }
    CATCH_MACRO

    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// [ Test ]
// get function pointer
// sycl::default_selector_v
// sycl::cpu_selector_v
// sycl::gpu_selector_v
// 
//////////////////////////////////////////////////////////////////////////////////////////////////////
void test_sycl_selector(void) {
    try {

        TEST_TITLE_MACRO

        void* selector_ptr = nullptr;

        // [ Test ]
        for (int iter_device = 0; iter_device < static_dev.size(); iter_device++) {
            sycl_selector(static_dev.at(iter_device), selector_ptr);
        }

    }
    CATCH_MACRO

    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// [ Test ]
// from sycl selector -> sycl::device
// 
//////////////////////////////////////////////////////////////////////////////////////////////////////
void test_sycl_device(void) {
    try {

        TEST_TITLE_MACRO

        void* device_ptr = nullptr;

        // [ Test ]
        for (int iter_device = 0; iter_device < static_dev.size(); iter_device++) {
            sycl_device(static_dev.at(iter_device), device_ptr);
            sycl_delete("device", device_ptr);
        }

    }
    CATCH_MACRO

    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// [ Test 01 ]
// selector -> queue
// 
// [ Test 02 ]
// device -> queue
// 
//////////////////////////////////////////////////////////////////////////////////////////////////////
void test_sycl_queue(void) {
    try {

        TEST_TITLE_MACRO

        void* selector_ptr = nullptr;
        void* device_ptr = nullptr;
        void* queue_ptr = nullptr;

        // [ Test 01 ]
        for (int iter_device = 0; iter_device < static_dev.size(); iter_device++) {
            sycl_selector(static_dev.at(iter_device), selector_ptr);
            sycl_queue("selector", queue_ptr, selector_ptr);
            sycl_delete("queue", queue_ptr);

        }

        // [ Test 02 ]
        for (int iter_device = 0; iter_device < static_dev.size(); iter_device++) {
            sycl_device(static_dev.at(iter_device), device_ptr);
            sycl_queue("device", queue_ptr, device_ptr);
            sycl_delete("queue", queue_ptr);
            sycl_delete("device", device_ptr);
        }

    }
    CATCH_MACRO

    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// [ Test ]
// sycl::info::device::name
// sycl::info::device::global_mem_size
// sycl::info::device::local_mem_size
// sycl::info::device::address_bits
// sycl::info::device::max_mem_alloc_size
// sycl::ext::intel::info::device::free_memory
// 
//////////////////////////////////////////////////////////////////////////////////////////////////////
void test_sycl_info(void) {
    try {

        TEST_TITLE_MACRO

        void* device_ptr = nullptr;
        void* queue_ptr = nullptr;

        // [ Test ]
        for (int iter_device = 0; iter_device < static_dev.size(); iter_device++) {

            sycl_device(static_dev.at(iter_device), device_ptr);
            sycl_queue("device", queue_ptr, device_ptr);

            // device name
            printf("Func : device name : %s\n",
                ((sycl::queue*)queue_ptr)->get_device().get_info<sycl::info::device::name>().c_str());

            // global_mem_size
            // Returns the size of global device memory in bytes.
            printf("Func : global_mem_size : %lld\n",
                (int64_t)((sycl::queue*)queue_ptr)->get_device().get_info<sycl::info::device::global_mem_size>());

            // local_mem_size
            // Shared local memory Size, GPU device has this bytes for each work-group.
            printf("Func : local_mem_size : %lld\n",
                (int64_t)((sycl::queue*)queue_ptr)->get_device().get_info<sycl::info::device::local_mem_size>());

            // address_bits
            printf("Func : address_bits : %lld\n",
                (int64_t)((sycl::queue*)queue_ptr)->get_device().get_info<sycl::info::device::address_bits>());

            // max_mem_alloc_size
            // Returns the maximum size of memory object allocation in bytes.
            // The minimum value is max (1/4th of info::device::global_mem_size,128*1024*1024) if this SYCL device is not of device type info::device_type::custom.
            printf("Func : max_mem_alloc_size : %lld\n",
                (int64_t)((sycl::queue*)queue_ptr)->get_device().get_info<sycl::info::device::max_mem_alloc_size>());

            // free_memory 
            // https://github.com/triSYCL/sycl/blob/sycl/unified/master/sycl/doc/extensions/supported/sycl_ext_intel_device_info.md
            if (((sycl::queue*)queue_ptr)->get_device().has(sycl::aspect::ext_intel_free_memory) == true) {
                printf("Func : free_memory : %lld\n",
                    (int64_t)((sycl::queue*)queue_ptr)->get_device().get_info<sycl::ext::intel::info::device::free_memory>());
            }

            sycl_delete("queue", queue_ptr);
            sycl_delete("device", device_ptr);

        }

    }
    CATCH_MACRO

    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// [ Test ]
// 'host memory'
// desktop can access 'host pointer'
// arcA770 can access 'host pointer'
//
// 'device memory'
// only arcA770 can access 'device pointer'
//
// 'shared memory'
// If 'shared pointer' did not touch sycl library, desktop can access 'shared pointer'
// If 'shared pointer' touch sycl library, desktop can't access 'shared pointer'
// 
//////////////////////////////////////////////////////////////////////////////////////////////////////
void test_sycl_memory(void) {
    try {

        TEST_TITLE_MACRO

        int64_t M = 64;
        int64_t N = 64;
        int64_t P = 64;
        
        std::vector<int64_t> dim_a;
        dim_a.clear();
        dim_a.push_back(N);
        dim_a.push_back(M);

        std::vector<int64_t> dim_b;
        dim_b.clear();
        dim_b.push_back(P);
        dim_b.push_back(N);

        std::vector<int64_t> dim_c;
        dim_c.clear();
        dim_c.push_back(P);
        dim_c.push_back(M);

        void* device_ptr = nullptr;
        void* queue_ptr = nullptr;

        void* ptr_sycl_a = nullptr;
        void* ptr_sycl_b = nullptr;
        void* ptr_sycl_c = nullptr;

        // [ Test ]
        for (int iter_device = 0; iter_device < static_dev.size(); iter_device++) {

            sycl_device(static_dev.at(iter_device), device_ptr);
            sycl_queue("device", queue_ptr, device_ptr);

            for (int iter_dtype = 0; iter_dtype < static_dtype.size(); iter_dtype++) {

                printf("\nFunc : data type : %s\n", static_dtype.at(iter_dtype).c_str());

                for (int iter_mtype = 0; iter_mtype < static_mtype.size(); iter_mtype++) {

                    printf("\nFunc : memory type : %s\n", static_mtype.at(iter_mtype).c_str());

                    sycl_mem_set(static_dtype.at(iter_dtype), static_mtype.at(iter_mtype), queue_ptr, ptr_sycl_a, dim_a, false);
                    sycl_mem_set(static_dtype.at(iter_dtype), static_mtype.at(iter_mtype), queue_ptr, ptr_sycl_b, dim_b, false);
                    sycl_mem_set(static_dtype.at(iter_dtype), static_mtype.at(iter_mtype), queue_ptr, ptr_sycl_c, dim_c, false);

                    sycl_mem_init(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_a, dim_a, (double)0.0, false);
                    sycl_mem_init(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_b, dim_b, (double)0.0, false);
                    sycl_mem_init(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_c, dim_c, (double)0.0, false);

                    sycl_mem_free(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_a, dim_a, false);
                    sycl_mem_free(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_b, dim_b, false);
                    sycl_mem_free(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_c, dim_c, false);

                }
            }

            sycl_delete("queue", queue_ptr);
            sycl_delete("device", device_ptr);

        }

    }
    CATCH_MACRO

    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// [ Test 01 ]
// 4GB
// 4294967296 = 1024 x 1024 x 1024 x 4 byte.
// 
// [ Test 02 ]
// max_mem_alloc_size
// 4294959104 = arcA770, almost global_mem_size(16688295936 byte) quarter.
// 
//////////////////////////////////////////////////////////////////////////////////////////////////////
void test_sycl_memory_4GB(void) {
    try {

        TEST_TITLE_MACRO

        std::vector<int64_t> dim_4gb;
        dim_4gb.clear();
        dim_4gb.push_back(4294967296); // 1024 * 1024 * 1024 * 4 byte;

        std::vector<int64_t> dim_max;
        dim_max.clear();
        dim_max.push_back(4294959104); // max_mem_alloc_size

        void* device_ptr = nullptr;
        void* queue_ptr = nullptr;

        void* ptr_sycl_4gb = nullptr;
        void* ptr_sycl_max = nullptr;

        for (int iter_device = 0; iter_device < static_dev.size(); iter_device++) {

            sycl_device(static_dev.at(iter_device), device_ptr);
            sycl_queue("device", queue_ptr, device_ptr);

            for (int iter_mtype = 0; iter_mtype < static_mtype.size(); iter_mtype++) {

                printf("\nFunc : memory type : %s\n", static_mtype.at(iter_mtype).c_str());

                sycl_mem_set("char*", static_mtype.at(iter_mtype), queue_ptr, ptr_sycl_4gb, dim_4gb, true);
                sycl_mem_free("char*", queue_ptr, ptr_sycl_4gb, dim_4gb, true);

                sycl_mem_set("char*", static_mtype.at(iter_mtype), queue_ptr, ptr_sycl_max, dim_max, true);
                sycl_mem_free("char*", queue_ptr, ptr_sycl_max, dim_max, true);

            }

            sycl_delete("queue", queue_ptr);
            sycl_delete("device", device_ptr);

        }

    }
    CATCH_MACRO

    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void test_sycl_dimension(void) {
    try {

        TEST_TITLE_MACRO

        std::vector<int64_t> dim_a;
        dim_a.clear();
        dim_a.push_back(8); // 1d, col
        dim_a.push_back(4); // 2d, row
        dim_a.push_back(2); // 3d, volumn
        // ...              // 4d, volumn count
        // ...              // 5d, ###

        void* device_ptr = nullptr;
        void* queue_ptr = nullptr;

        void* ptr_a = nullptr;
        void* ptr_sycl_a = nullptr;

        // [ Test ]
        sycl_device("default", device_ptr);
        sycl_queue("device", queue_ptr, device_ptr);

        std_mem_set("char*", ptr_a, dim_a, false);
        std_mem_init("char*", ptr_a, dim_a, (double)0.0, false);

        sycl_mem_set("char*", "host", queue_ptr, ptr_sycl_a, dim_a, false);
        sycl_mem_init("char*", queue_ptr, ptr_sycl_a, dim_a, (double)0.0, false);

        sycl_kernel_dimension("char*", queue_ptr, ptr_sycl_a, dim_a, false);

        sycl_mem_copy("char*", queue_ptr, ptr_a, ptr_sycl_a, dim_a, false);

        std_iter_print("char*", ptr_a, dim_a, false);

        sycl_mem_free("char*", queue_ptr, ptr_sycl_a, dim_a, false);
        std_mem_free("char*", ptr_a, dim_a, false);

        sycl_delete("queue", queue_ptr);
        sycl_delete("device", device_ptr);

    }
    CATCH_MACRO

    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// [ Test ]
// 'desktop pointer' can't directly use 'sycl::queue::parallel_for()'
// 'desktop pointer' -> use 'sycl buffer' -> 'sycl::queue::parallel_for()'
// 
//////////////////////////////////////////////////////////////////////////////////////////////////////
void test_sycl_buffer_from_host(void) {
    try {

        TEST_TITLE_MACRO

        int64_t M = 64;
        int64_t N = 64;
        int64_t P = 64;
        
        std::vector<int64_t> dim_a;
        dim_a.clear();
        dim_a.push_back(N);
        dim_a.push_back(M);

        std::vector<int64_t> dim_b;
        dim_b.clear();
        dim_b.push_back(P);
        dim_b.push_back(N);

        std::vector<int64_t> dim_c;
        dim_c.clear();
        dim_c.push_back(P);
        dim_c.push_back(M);

        void* device_ptr = nullptr;
        void* queue_ptr = nullptr;

        void* ptr_a = nullptr;
        void* ptr_b = nullptr;
        void* ptr_c = nullptr;

        // [ Test ]
        for (int iter_device = 0; iter_device < static_dev.size(); iter_device++) {

            sycl_device(static_dev.at(iter_device), device_ptr);
            sycl_queue("device", queue_ptr, device_ptr);

            for (int iter_dtype = 0; iter_dtype < static_dtype.size(); iter_dtype++) {

                printf("\nFunc : data type : %s\n", static_dtype.at(iter_dtype).c_str());

                std_mem_set(static_dtype.at(iter_dtype), ptr_a, dim_a, false);
                std_mem_set(static_dtype.at(iter_dtype), ptr_b, dim_b, false);
                std_mem_set(static_dtype.at(iter_dtype), ptr_c, dim_c, false);

                std_mem_init(static_dtype.at(iter_dtype), ptr_a, dim_a, (double)1.0, false);
                std_mem_init(static_dtype.at(iter_dtype), ptr_b, dim_b, (double)1.0, false);
                std_mem_init(static_dtype.at(iter_dtype), ptr_c, dim_c, (double)0.0, false);

                sycl_kernel_buffer(static_dtype.at(iter_dtype), queue_ptr, ptr_a, ptr_b, ptr_c, M, N, P, true);

                std_iter_print(static_dtype.at(iter_dtype), ptr_c, dim_c, false);

                std_mem_free(static_dtype.at(iter_dtype), ptr_a, dim_a, false);
                std_mem_free(static_dtype.at(iter_dtype), ptr_b, dim_b, false);
                std_mem_free(static_dtype.at(iter_dtype), ptr_c, dim_c, false);

            }

            sycl_delete("queue", queue_ptr);
            sycl_delete("device", device_ptr);

        }        

    }
    CATCH_MACRO

    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// [ Test ]
// 'desktop pointer' can't directly use 'sycl::queue::parallel_for()'
// 'desktop pointer' -> copy to 'sycl pointer' -> use 'sycl buffer' -> 'sycl::queue::parallel_for()' -> copy to 'desktop pointer'
// 
//////////////////////////////////////////////////////////////////////////////////////////////////////
void test_sycl_buffer_from_sycl(void) {
    try {

        TEST_TITLE_MACRO

        int64_t M = 64;
        int64_t N = 64;
        int64_t P = 64;
        
        std::vector<int64_t> dim_a;
        dim_a.clear();
        dim_a.push_back(N);
        dim_a.push_back(M);

        std::vector<int64_t> dim_b;
        dim_b.clear();
        dim_b.push_back(P);
        dim_b.push_back(N);

        std::vector<int64_t> dim_c;
        dim_c.clear();
        dim_c.push_back(P);
        dim_c.push_back(M);

        void* device_ptr = nullptr;
        void* queue_ptr = nullptr;

        void* ptr_a = nullptr;
        void* ptr_b = nullptr;
        void* ptr_c = nullptr;

        void* ptr_sycl_a = nullptr;
        void* ptr_sycl_b = nullptr;
        void* ptr_sycl_c = nullptr;

        // [ Test ]
        for (int iter_device = 0; iter_device < static_dev.size(); iter_device++) {

            sycl_device(static_dev.at(iter_device), device_ptr);
            sycl_queue("device", queue_ptr, device_ptr);

            for (int iter_dtype = 0; iter_dtype < static_dtype.size(); iter_dtype++) {

                printf("\nFunc : data type : %s\n", static_dtype.at(iter_dtype).c_str());

                for (int iter_mtype = 0; iter_mtype < static_mtype.size(); iter_mtype++) {

                    printf("\nFunc : memory type : %s\n", static_mtype.at(iter_mtype).c_str());

                    std_mem_set(static_dtype.at(iter_dtype), ptr_a, dim_a, false);
                    std_mem_set(static_dtype.at(iter_dtype), ptr_b, dim_b, false);
                    std_mem_set(static_dtype.at(iter_dtype), ptr_c, dim_c, false);

                    std_mem_init(static_dtype.at(iter_dtype), ptr_a, dim_a, (double)1.0, false);
                    std_mem_init(static_dtype.at(iter_dtype), ptr_b, dim_b, (double)1.0, false);
                    std_mem_init(static_dtype.at(iter_dtype), ptr_c, dim_c, (double)0.0, false);

                    sycl_mem_set(static_dtype.at(iter_dtype), static_mtype.at(iter_mtype), queue_ptr, ptr_sycl_a, dim_a, false);
                    sycl_mem_set(static_dtype.at(iter_dtype), static_mtype.at(iter_mtype), queue_ptr, ptr_sycl_b, dim_b, false);
                    sycl_mem_set(static_dtype.at(iter_dtype), static_mtype.at(iter_mtype), queue_ptr, ptr_sycl_c, dim_c, false);

                    sycl_mem_copy(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_a, ptr_a, dim_a, false);
                    sycl_mem_copy(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_b, ptr_b, dim_b, false);
                    sycl_mem_copy(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_c, ptr_c, dim_c, false);

                    sycl_kernel_buffer(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_a, ptr_sycl_b, ptr_sycl_c, M, N, P, true);

                    sycl_mem_copy(static_dtype.at(iter_dtype), queue_ptr, ptr_c, ptr_sycl_c, dim_c, false);

                    std_iter_print(static_dtype.at(iter_dtype), ptr_c, dim_c, false);

                    sycl_mem_free(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_a, dim_a, false);
                    sycl_mem_free(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_b, dim_b, false);
                    sycl_mem_free(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_c, dim_c, false);

                    std_mem_free(static_dtype.at(iter_dtype), ptr_a, dim_a, false);
                    std_mem_free(static_dtype.at(iter_dtype), ptr_b, dim_b, false);
                    std_mem_free(static_dtype.at(iter_dtype), ptr_c, dim_c, false);

                }
            }

            sycl_delete("queue", queue_ptr);
            sycl_delete("device", device_ptr);

        }

    }
    CATCH_MACRO

    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// [ Test ]
// 'desktop pointer' -> copy to 'sycl pointer' -> usm -> copy to 'desktop pointer'
// 
//////////////////////////////////////////////////////////////////////////////////////////////////////
void test_sycl_usm(void) {
    try {

        TEST_TITLE_MACRO

        int64_t M = 64;
        int64_t N = 64;
        int64_t P = 64;

        std::vector<int64_t> dim_a;
        dim_a.clear();
        dim_a.push_back(N);
        dim_a.push_back(M);

        std::vector<int64_t> dim_b;
        dim_b.clear();
        dim_b.push_back(P);
        dim_b.push_back(N);

        std::vector<int64_t> dim_c;
        dim_c.clear();
        dim_c.push_back(P);
        dim_c.push_back(M);

        void* device_ptr = nullptr;
        void* queue_ptr = nullptr;

        void* ptr_a = nullptr;
        void* ptr_b = nullptr;
        void* ptr_c = nullptr;

        void* ptr_sycl_a = nullptr;
        void* ptr_sycl_b = nullptr;
        void* ptr_sycl_c = nullptr;

        // [ Test ]
        for (int iter_device = 0; iter_device < static_dev.size(); iter_device++) {

            sycl_device(static_dev.at(iter_device), device_ptr);
            sycl_queue("device", queue_ptr, device_ptr);

            for (int iter_dtype = 0; iter_dtype < static_dtype.size(); iter_dtype++) {

                printf("\nFunc : data type : %s\n", static_dtype.at(iter_dtype).c_str());

                for (int iter_mtype = 0; iter_mtype < static_mtype.size(); iter_mtype++) {

                    printf("\nFunc : memory type : %s\n", static_mtype.at(iter_mtype).c_str());

                    std_mem_set(static_dtype.at(iter_dtype), ptr_a, dim_a, false);
                    std_mem_set(static_dtype.at(iter_dtype), ptr_b, dim_b, false);
                    std_mem_set(static_dtype.at(iter_dtype), ptr_c, dim_c, false);

                    std_mem_init(static_dtype.at(iter_dtype), ptr_a, dim_a, (double)1.0, false);
                    std_mem_init(static_dtype.at(iter_dtype), ptr_b, dim_b, (double)1.0, false);
                    std_mem_init(static_dtype.at(iter_dtype), ptr_c, dim_c, (double)0.0, false);

                    sycl_mem_set(static_dtype.at(iter_dtype), static_mtype.at(iter_mtype), queue_ptr, ptr_sycl_a, dim_a, false);
                    sycl_mem_set(static_dtype.at(iter_dtype), static_mtype.at(iter_mtype), queue_ptr, ptr_sycl_b, dim_b, false);
                    sycl_mem_set(static_dtype.at(iter_dtype), static_mtype.at(iter_mtype), queue_ptr, ptr_sycl_c, dim_c, false);

                    sycl_mem_copy(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_a, ptr_a, dim_a, false);
                    sycl_mem_copy(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_b, ptr_b, dim_b, false);
                    sycl_mem_copy(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_c, ptr_c, dim_c, false);

                    sycl_kernel_usm(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_a, ptr_sycl_b, ptr_sycl_c, M, N, P, true);

                    sycl_mem_copy(static_dtype.at(iter_dtype), queue_ptr, ptr_c, ptr_sycl_c, dim_c, false);

                    std_iter_print(static_dtype.at(iter_dtype), ptr_c, dim_c, false);

                    sycl_mem_free(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_a, dim_a, false);
                    sycl_mem_free(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_b, dim_b, false);
                    sycl_mem_free(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_c, dim_c, false);

                    std_mem_free(static_dtype.at(iter_dtype), ptr_a, dim_a, false);
                    std_mem_free(static_dtype.at(iter_dtype), ptr_b, dim_b, false);
                    std_mem_free(static_dtype.at(iter_dtype), ptr_c, dim_c, false);

                }
            }

            sycl_delete("queue", queue_ptr);
            sycl_delete("device", device_ptr);

        }

    }
    CATCH_MACRO

    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void test_sycl_random(void) {
    try {

        TEST_TITLE_MACRO

        int64_t M = 64;

        std::vector<int64_t> dim_a;
        dim_a.clear();
        dim_a.push_back(M);

        void* device_ptr = nullptr;
        void* queue_ptr = nullptr;

        void* ptr_a = nullptr;
        void* ptr_sycl_a = nullptr;

        // [ Test ]
        for (int iter_device = 0; iter_device < static_dev.size(); iter_device++) {

            sycl_device(static_dev.at(iter_device), device_ptr);
            sycl_queue("device", queue_ptr, device_ptr);

            for (int iter_dtype = 0; iter_dtype < static_dtype.size(); iter_dtype++) {

                printf("\nFunc : data type : %s\n", static_dtype.at(iter_dtype).c_str());

                for (int iter_mtype = 0; iter_mtype < static_mtype.size(); iter_mtype++) {

                    printf("\nFunc : memory type : %s\n", static_mtype.at(iter_mtype).c_str());

                    std_mem_set(static_dtype.at(iter_dtype), ptr_a, dim_a, false);
                    std_mem_init(static_dtype.at(iter_dtype), ptr_a, dim_a, (double)0.0, false);

                    sycl_mem_set(static_dtype.at(iter_dtype), static_mtype.at(iter_mtype), queue_ptr, ptr_sycl_a, dim_a, false);
                    sycl_mem_init(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_a, dim_a, (double)0.0, false);

                    sycl_mem_copy(static_dtype.at(iter_dtype), queue_ptr, ptr_a, ptr_sycl_a, dim_a, false);

                    sycl_kernel_random(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_a, dim_a, false);

                    sycl_mem_copy(static_dtype.at(iter_dtype), queue_ptr, ptr_a, ptr_sycl_a, dim_a, false);

                    std_iter_print(static_dtype.at(iter_dtype), ptr_a, dim_a, false);

                    sycl_mem_free(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_a, dim_a, false);
                    std_mem_free(static_dtype.at(iter_dtype), ptr_a, dim_a, false);
                }
            }

            sycl_delete("queue", queue_ptr);
            sycl_delete("device", device_ptr);

        }

    }
    CATCH_MACRO

    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void test_sycl_usm_add(void) {
    try {

        TEST_TITLE_MACRO

        // row M x col N
        int64_t M = 64;
        int64_t N = 64;

        std::vector<int64_t> dim_a;
        dim_a.clear();
        dim_a.push_back(N); // col
        dim_a.push_back(M); // row

        std::vector<int64_t> dim_b;
        dim_b.clear();
        dim_b.push_back(N);
        dim_b.push_back(M);

        std::vector<int64_t> dim_c;
        dim_c.clear();
        dim_c.push_back(N);
        dim_c.push_back(M);

        void* device_ptr = nullptr;
        void* queue_ptr = nullptr;

        void* ptr_a = nullptr;
        void* ptr_b = nullptr;
        void* ptr_c = nullptr;

        void* ptr_sycl_a = nullptr;
        void* ptr_sycl_b = nullptr;
        void* ptr_sycl_c = nullptr;

        // [ Test ]
        for (int iter_device = 0; iter_device < static_dev.size(); iter_device++) {

            sycl_device(static_dev.at(iter_device), device_ptr);
            sycl_queue("device", queue_ptr, device_ptr);

            for (int iter_dtype = 0; iter_dtype < static_dtype.size(); iter_dtype++) {

                printf("\nFunc : data type : %s\n", static_dtype.at(iter_dtype).c_str());

                for (int iter_mtype = 0; iter_mtype < static_mtype.size(); iter_mtype++) {

                    printf("\nFunc : memory type : %s\n", static_mtype.at(iter_mtype).c_str());

                    std_mem_set(static_dtype.at(iter_dtype), ptr_a, dim_a, false);
                    std_mem_set(static_dtype.at(iter_dtype), ptr_b, dim_b, false);
                    std_mem_set(static_dtype.at(iter_dtype), ptr_c, dim_c, false);

                    std_mem_init(static_dtype.at(iter_dtype), ptr_a, dim_a, (double)1.0, false);
                    std_mem_init(static_dtype.at(iter_dtype), ptr_b, dim_b, (double)1.0, false);
                    std_mem_init(static_dtype.at(iter_dtype), ptr_c, dim_c, (double)0.0, false);

                    sycl_mem_set(static_dtype.at(iter_dtype), static_mtype.at(iter_mtype), queue_ptr, ptr_sycl_a, dim_a, false);
                    sycl_mem_set(static_dtype.at(iter_dtype), static_mtype.at(iter_mtype), queue_ptr, ptr_sycl_b, dim_b, false);
                    sycl_mem_set(static_dtype.at(iter_dtype), static_mtype.at(iter_mtype), queue_ptr, ptr_sycl_c, dim_c, false);

                    sycl_mem_init(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_a, dim_a, (double)0.0, false);
                    sycl_mem_init(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_b, dim_b, (double)0.0, false);
                    sycl_mem_init(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_c, dim_c, (double)0.0, false);

                    sycl_mem_copy(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_a, ptr_a, dim_a, false);
                    sycl_mem_copy(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_b, ptr_b, dim_b, false);
                    sycl_mem_copy(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_c, ptr_c, dim_c, false);

                    sycl_kernel_usm_add(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_a, ptr_sycl_b, ptr_sycl_c, dim_c, true);

                    sycl_mem_copy(static_dtype.at(iter_dtype), queue_ptr, ptr_c, ptr_sycl_c, dim_c, false);

                    std_iter_print(static_dtype.at(iter_dtype), ptr_c, dim_c, false);

                    sycl_mem_free(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_a, dim_a, false);
                    sycl_mem_free(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_b, dim_b, false);
                    sycl_mem_free(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_c, dim_c, false);

                    std_mem_free(static_dtype.at(iter_dtype), ptr_a, dim_a, false);
                    std_mem_free(static_dtype.at(iter_dtype), ptr_b, dim_b, false);
                    std_mem_free(static_dtype.at(iter_dtype), ptr_c, dim_c, false);

                }
            }

            sycl_delete("queue", queue_ptr);
            sycl_delete("device", device_ptr);

        }

    }
    CATCH_MACRO

    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void test_sycl_usm_matmul(void) {
    try {

        TEST_TITLE_MACRO

        int64_t M = 64;
        int64_t N = 64;
        int64_t P = 64;

        std::vector<int64_t> dim_a;
        dim_a.clear();
        dim_a.push_back(N);
        dim_a.push_back(M);

        std::vector<int64_t> dim_b;
        dim_b.clear();
        dim_b.push_back(P);
        dim_b.push_back(N);

        std::vector<int64_t> dim_c;
        dim_c.clear();
        dim_c.push_back(P);
        dim_c.push_back(M);

        void* device_ptr = nullptr;
        void* queue_ptr = nullptr;

        void* ptr_a = nullptr;
        void* ptr_b = nullptr;
        void* ptr_c = nullptr;

        void* ptr_sycl_a = nullptr;
        void* ptr_sycl_b = nullptr;
        void* ptr_sycl_c = nullptr;

        // [ Test ]
        for (int iter_device = 0; iter_device < static_dev.size(); iter_device++) {

            sycl_device(static_dev.at(iter_device), device_ptr);
            sycl_queue("device", queue_ptr, device_ptr);

            for (int iter_dtype = 0; iter_dtype < static_dtype.size(); iter_dtype++) {

                printf("\nFunc : data type : %s\n", static_dtype.at(iter_dtype).c_str());

                for (int iter_mtype = 0; iter_mtype < static_mtype.size(); iter_mtype++) {

                    printf("\nFunc : memory type : %s\n", static_mtype.at(iter_mtype).c_str());

                    std_mem_set(static_dtype.at(iter_dtype), ptr_a, dim_a, false);
                    std_mem_set(static_dtype.at(iter_dtype), ptr_b, dim_b, false);
                    std_mem_set(static_dtype.at(iter_dtype), ptr_c, dim_c, false);

                    std_mem_init(static_dtype.at(iter_dtype), ptr_a, dim_a, (double)1.0, false);
                    std_mem_init(static_dtype.at(iter_dtype), ptr_b, dim_b, (double)1.0, false);
                    std_mem_init(static_dtype.at(iter_dtype), ptr_c, dim_c, (double)0.0, false);

                    sycl_mem_set(static_dtype.at(iter_dtype), static_mtype.at(iter_mtype), queue_ptr, ptr_sycl_a, dim_a, false);
                    sycl_mem_set(static_dtype.at(iter_dtype), static_mtype.at(iter_mtype), queue_ptr, ptr_sycl_b, dim_b, false);
                    sycl_mem_set(static_dtype.at(iter_dtype), static_mtype.at(iter_mtype), queue_ptr, ptr_sycl_c, dim_c, false);

                    sycl_mem_init(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_a, dim_a, (double)0.0, false);
                    sycl_mem_init(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_b, dim_b, (double)0.0, false);
                    sycl_mem_init(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_c, dim_c, (double)0.0, false);

                    sycl_mem_copy(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_a, ptr_a, dim_a, false);
                    sycl_mem_copy(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_b, ptr_b, dim_b, false);
                    sycl_mem_copy(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_c, ptr_c, dim_c, false);

                    sycl_kernel_usm_matmul(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_a, ptr_sycl_b, ptr_sycl_c, M, N, P, true);

                    sycl_mem_copy(static_dtype.at(iter_dtype), queue_ptr, ptr_c, ptr_sycl_c, dim_c, false);

                    std_iter_print(static_dtype.at(iter_dtype), ptr_c, dim_c, false);

                    sycl_mem_free(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_a, dim_a, false);
                    sycl_mem_free(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_b, dim_b, false);
                    sycl_mem_free(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_c, dim_c, false);

                    std_mem_free(static_dtype.at(iter_dtype), ptr_a, dim_a, false);
                    std_mem_free(static_dtype.at(iter_dtype), ptr_b, dim_b, false);
                    std_mem_free(static_dtype.at(iter_dtype), ptr_c, dim_c, false);

                }
            }

            sycl_delete("queue", queue_ptr);
            sycl_delete("device", device_ptr);

        }

    }
    CATCH_MACRO

    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void sycl_selector(std::string get_type, void*& selector_ptr) {
    try {

        printf("\n\n\n");

        FUNC_TYPE_MACRO

        if ((get_type == "") || (get_type == "default")) {
            selector_ptr = (void*)&sycl::default_selector_v;
        }
        else if (get_type == "cpu") {
            selector_ptr = (void*)&sycl::cpu_selector_v;
        }
        else if (get_type == "gpu") {
            selector_ptr = (void*)&sycl::gpu_selector_v;
        }
        else if (get_type == "aspect") {
            throw std::exception("can't reference sycl::aspect_selector function address");
        }
        else {
            throw std::exception("you need to update");
        }

        if (false) {

            // function definition
            int(*get_selector)(const sycl::device&) = (int(*)(const sycl::device&))selector_ptr;

            // make device
            printf("%s\n", get_type.c_str());
            sycl::device d1(get_selector);
            sycl::queue q1(d1);
            (d1.has(sycl::aspect::fp64) == true) ? printf("fp64 support !!!\n") : printf("fp64 not support !!!\n");
            (d1.has(sycl::aspect::fp16) == true) ? printf("fp16 support !!!\n") : printf("fp16 not support !!!\n");
            (q1.get_device().has(sycl::aspect::fp64) == true) ? printf("fp64 support !!!\n") : printf("fp64 not support !!!\n");
            (q1.get_device().has(sycl::aspect::fp16) == true) ? printf("fp16 support !!!\n") : printf("fp16 not support !!!\n");

            // other style 01
            sycl::device d2(sycl::aspect_selector(std::vector{ sycl::aspect::gpu, sycl::aspect::fp16, sycl::aspect::fp64 }));
            sycl::queue q2(d2);

            // other style 02
            sycl::device d3(sycl::aspect_selector(std::vector{ sycl::aspect::cpu, sycl::aspect::fp16 }));
            sycl::queue q3(d3);

            // other style 03
            sycl::queue q4(sycl::aspect_selector(std::vector{ sycl::aspect::cpu, sycl::aspect::fp64 }));
        }

    }
    CATCH_MACRO

    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void sycl_device(std::string get_type, void*& device_ptr) {
    try {

        printf("\n\n\n");

        FUNC_TYPE_MACRO

        device_ptr = new sycl::device;

        if ((get_type == "") || (get_type == "default")) {
            (*(sycl::device*)device_ptr) = sycl::device(sycl::default_selector_v);
        }
        else if (get_type == "cpu") {
            (*(sycl::device*)device_ptr) = sycl::device(sycl::cpu_selector_v);
        }
        else if (get_type == "gpu") {
            (*(sycl::device*)device_ptr) = sycl::device(sycl::gpu_selector_v);
        }
        else if (get_type == "aspect") {

            // arcA770 : can't use fp64
            (*(sycl::device*)device_ptr) = sycl::device(sycl::aspect_selector(std::vector{ sycl::aspect::gpu, sycl::aspect::fp16 }));
            //(*(sycl::device*)device_ptr) = sycl::device(sycl::aspect_selector(std::vector{ sycl::aspect::gpu, sycl::aspect::fp64 }));
            //(*(sycl::device*)device_ptr) = sycl::device(sycl::aspect_selector(std::vector{ sycl::aspect::gpu, sycl::aspect::fp64, sycl::aspect::fp16 }));

            // cpu : need to set system enviroment CL_CONFIG_CPU_EXPERIMENTAL_FP16 = 1
            //(*(sycl::device*)device_ptr) = sycl::device(sycl::aspect_selector(std::vector{ sycl::aspect::cpu, sycl::aspect::fp16 }));
            //(*(sycl::device*)device_ptr) = sycl::device(sycl::aspect_selector(std::vector{ sycl::aspect::cpu, sycl::aspect::fp64 }));
            //(*(sycl::device*)device_ptr) = sycl::device(sycl::aspect_selector(std::vector{ sycl::aspect::cpu, sycl::aspect::fp64, sycl::aspect::fp16 }) );
        }
        else {
            throw std::exception("you need to check");
        }

    }
    CATCH_MACRO

    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void sycl_queue(std::string get_type, void*& queue_ptr, void*& get_ptr) {
    try {

        FUNC_TYPE_MACRO

        queue_ptr = new sycl::queue;

        if (get_type == "selector") {
            int(*get_selector)(const sycl::device&) = (int(*)(const sycl::device&))get_ptr;
            (*(sycl::queue*)queue_ptr) = sycl::queue(get_selector);
        }
        else if (get_type == "device") {
            (*(sycl::queue*)queue_ptr) = sycl::queue(*((sycl::device*)get_ptr));
        }
        else {
            throw std::exception("you need to update");
        }

        // for sycl library pre-load : -->
        sycl::queue* q = (sycl::queue*)queue_ptr;
        q->parallel_for(\
            sycl::range(1), [=](auto index) {
                int get_value = 0;
                get_value = get_value + 0;
            }
        );
        q->wait();
        // for sycl library pre-load : <--

    }
    CATCH_MACRO

    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void sycl_delete(std::string get_type, void*& get_ptr) {
    try {

        FUNC_TYPE_MACRO

        if (get_type == "device") {
            delete ((sycl::device*)get_ptr);
            get_ptr = nullptr;
        }
        else if (get_type == "queue") {
            delete ((sycl::queue*)get_ptr);
            get_ptr = nullptr;
        }
        else {
            throw std::exception("you need to update");
        }

    }
    CATCH_MACRO

    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void sycl_mem_set(std::string get_type, std::string get_method, void*& queue_ptr, void*& get_ptr, std::vector<int64_t> get_dim, bool debug_flag) {
    try {

        FUNC_TYPE_MACRO

        int64_t sizeof_byte = 0;

        int64_t sizeof_count = 1;
        for (int64_t iter = 0; iter < get_dim.size(); iter++) {
            sizeof_count = sizeof_count * get_dim.at(iter);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        // for malloc
        if (get_type == "char*") {

            sizeof_byte = sizeof(char);

            if (get_method == "host") {
                get_ptr = (void*)sycl::malloc_host<char>(sizeof_count, (*(sycl::queue*)queue_ptr));
            }
            else if (get_method == "device") {
                get_ptr = (void*)sycl::malloc_device<char>(sizeof_count, (*(sycl::queue*)queue_ptr));
            }
            else if (get_method == "shared") {
                get_ptr = (void*)sycl::malloc_shared<char>(sizeof_count, (*(sycl::queue*)queue_ptr));
            }
            else {
                throw std::exception("need to update");
            }
        }
        else if (get_type == "int*") {

            sizeof_byte = sizeof(int);

            if (get_method == "host") {
                get_ptr = (void*)sycl::malloc_host<int>(sizeof_count, (*(sycl::queue*)queue_ptr));
            }
            else if (get_method == "device") {
                get_ptr = (void*)sycl::malloc_device<int>(sizeof_count, (*(sycl::queue*)queue_ptr));
            }
            else if (get_method == "shared") {
                get_ptr = (void*)sycl::malloc_shared<int>(sizeof_count, (*(sycl::queue*)queue_ptr));
            }
            else {
                throw std::exception("need to update");
            }
        }
        else if (get_type == "float*") {

            sizeof_byte = sizeof(float);

            if (get_method == "host") {
                get_ptr = (void*)sycl::malloc_host<float>(sizeof_count, (*(sycl::queue*)queue_ptr));
            }
            else if (get_method == "device") {
                get_ptr = (void*)sycl::malloc_device<float>(sizeof_count, (*(sycl::queue*)queue_ptr));
            }
            else if (get_method == "shared") {
                get_ptr = (void*)sycl::malloc_shared<float>(sizeof_count, (*(sycl::queue*)queue_ptr));
            }
            else {
                throw std::exception("need to update");
            }
        }
        else {
            throw std::exception("need to update");
        }

        ((sycl::queue*)queue_ptr)->wait();
        ////////////////////////////////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        // for to notify 'desktop, desktop shared gpu memory, gpu memory' 
        ((sycl::queue*)queue_ptr)->memset(get_ptr, 0, sizeof_byte * sizeof_count);
        ((sycl::queue*)queue_ptr)->wait();
        ////////////////////////////////////////////////////////////////////////////////////////////////////

        if (debug_flag) {
            FUNC_BYTE_MACRO
        }

    }
    CATCH_MACRO

    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void sycl_mem_init(std::string get_type, void*& queue_ptr, void*& get_ptr, std::vector<int64_t> get_dim, double get_value, bool debug_flag) {
    try {

        FUNC_TYPE_MACRO

        int64_t sizeof_byte = 0;

        int64_t sizeof_count = 1;
        for (int iter = 0; iter < get_dim.size(); iter++) {
            sizeof_count = sizeof_count * get_dim.at(iter);
        }

        if (get_type == "char*") {
            sizeof_byte = sizeof(char);
            int value = (int)get_value;
            ((sycl::queue*)queue_ptr)->memset(get_ptr, value, sizeof_byte * sizeof_count);
        }
        else if (get_type == "int*") {
            sizeof_byte = sizeof(int);
            int value = (int)get_value;
            ((sycl::queue*)queue_ptr)->memset(get_ptr, value, sizeof_byte * sizeof_count);
        }
        else if (get_type == "float*") {
            sizeof_byte = sizeof(float);
            int value = (int)get_value;
            ((sycl::queue*)queue_ptr)->memset(get_ptr, value, sizeof_byte * sizeof_count);
        }
        else {
            throw std::exception("need to update");
        }

        ((sycl::queue*)queue_ptr)->wait();

        if (debug_flag) {
            FUNC_BYTE_MACRO
        }

    }
    CATCH_MACRO

    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void sycl_mem_copy(std::string get_type, void*& queue_ptr, void*& dst_ptr, void*& src_ptr, std::vector<int64_t> get_dim, bool debug_flag) {
    try {

        FUNC_TYPE_MACRO

        int64_t sizeof_byte = 0;

        int64_t sizeof_count = 1;
        for (int iter = 0; iter < get_dim.size(); iter++) {
            sizeof_count = sizeof_count * get_dim.at(iter);
        }

        if (get_type == "char*") {
            sizeof_byte = sizeof(char);
            ((sycl::queue*)queue_ptr)->memcpy(dst_ptr, src_ptr, sizeof_byte * sizeof_count);
        }
        else if (get_type == "int*") {
            sizeof_byte = sizeof(int);
            ((sycl::queue*)queue_ptr)->memcpy(dst_ptr, src_ptr, sizeof_byte * sizeof_count);
        }
        else if (get_type == "float*") {
            sizeof_byte = sizeof(float);
            ((sycl::queue*)queue_ptr)->memcpy(dst_ptr, src_ptr, sizeof_byte * sizeof_count);
        }
        else {
            throw std::exception("need to update");
        }

        ((sycl::queue*)queue_ptr)->wait();

        if (debug_flag) {
            FUNC_BYTE_MACRO
        }

    }
    CATCH_MACRO

    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void sycl_mem_free(std::string get_type, void*& queue_ptr, void*& get_ptr, std::vector<int64_t> get_dim, bool debug_flag) {
    try {

        FUNC_TYPE_MACRO

        int64_t sizeof_byte = 0;

        int64_t sizeof_count = 1;
        for (int iter = 0; iter < get_dim.size(); iter++) {
            sizeof_count = sizeof_count * get_dim.at(iter);
        }

        if (get_type == "char*") {
            sizeof_byte = sizeof(char);
            sycl::free((char*)get_ptr, (*(sycl::queue*)queue_ptr));
            get_ptr = nullptr;
        }
        else if (get_type == "int*") {
            sizeof_byte = sizeof(int);
            sycl::free((int*)get_ptr, (*(sycl::queue*)queue_ptr));
            get_ptr = nullptr;
        }
        else if (get_type == "float*") {
            sizeof_byte = sizeof(float);
            sycl::free((float*)get_ptr, (*(sycl::queue*)queue_ptr));
            get_ptr = nullptr;
        }
        else {
            throw std::exception("need to update");
        }

        ((sycl::queue*)queue_ptr)->wait();

        if (debug_flag) {
            FUNC_BYTE_MACRO
        }

    }
    CATCH_MACRO

    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void sycl_kernel_dimension(std::string get_type, void*& queue_ptr, void*& get_buf, std::vector<int64_t> get_dim, bool debug_flag) {
    try {

        FUNC_TYPE_MACRO

        std::chrono::system_clock::time_point time_tick;
        std::chrono::duration<double>time_tok;

        sycl::queue* q = (sycl::queue*)queue_ptr;

        // range.hpp -> "range can only be 1, 2, or 3 Dimensional."
        int64_t range_1d = get_dim.at(0); // 8, col
        int64_t range_2d = get_dim.at(1); // 4, row
        int64_t range_3d = get_dim.at(2); // 2, volumn

        time_tick = std::chrono::system_clock::now();
        q->submit(\
            [&](auto& h) {
                h.parallel_for(
                    sycl::range(range_3d, range_2d, range_1d), [=](auto index) {

                        int idx_3d = index[0]; // 0 ~ 1, 2, range_3d, volumn
                        int idx_2d = index[1]; // 0 ~ 3, 4, range_2d, row
                        int idx_1d = index[2]; // 0 ~ 7, 8, range_1d, col

                        int64_t get_index = \
                            idx_3d * (range_2d * range_1d) + \
                            idx_2d * (range_1d)+\
                            idx_1d;

                        ((char*)get_buf)[get_index] = (char)get_index;

                    }
                );
            }
        );
        q->wait();
        time_tok = std::chrono::system_clock::now() - time_tick;
        if (debug_flag) {
            FUNC_TIME_MACRO
        }

    }
    CATCH_MACRO

    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void sycl_kernel_buffer(std::string get_type, void*& queue_ptr, void*& get_buf_a, void*& get_buf_b, void*& get_buf_c, int64_t get_m, int64_t get_n, int64_t get_p, bool debug_flag) {
    try {

        FUNC_TYPE_MACRO

        std::chrono::system_clock::time_point time_tick;
        std::chrono::duration<double>time_tok;

        sycl::queue* q = (sycl::queue*)queue_ptr;

        // [ pointer -> sycl::buffer ] 
        // Buffer type          : 1 Dimensions
        // Buffer count         : get_m x get_n
        //                      : get_n x get_p
        //                      : get_m x get_p
        // Create thread count  : sycl::range(get_m, get_p)
        //                      : get_m x get_p
        //                      : index[0] = 0 ~ ( get_m - 1 )
        //                      : index[1] = 0 ~ ( get_p - 1 )

        if (get_type == "char*") {
            sycl::buffer sycl_buf_a((char*)get_buf_a, sycl::range(get_m * get_n));
            sycl::buffer sycl_buf_b((char*)get_buf_b, sycl::range(get_n * get_p));
            sycl::buffer sycl_buf_c((char*)get_buf_c, sycl::range(get_m * get_p));
            time_tick = std::chrono::system_clock::now();
            q->submit(\
                [&](auto& h) {
                    sycl::accessor a(sycl_buf_a, h, sycl::read_only);
                    sycl::accessor b(sycl_buf_b, h, sycl::read_only);
                    sycl::accessor c(sycl_buf_c, h, sycl::write_only);
                    h.parallel_for(
                        sycl::range(get_m, get_p), [=](auto index) {
                            char sum = 0; // -128 ~ 127

                            int64_t target_row = index[0];
                            int64_t target_col = index[1];
                            int64_t a_col = get_n;
                            int64_t b_col = get_p;
                            int64_t c_col = get_p;
                            int64_t itr_range = get_n;
                            for (int64_t n = 0; n < itr_range; n++) {
                                // [ Matrix A (M x N) : fix row, itr N -> move right ]
                                // [ Matrix B (N x P) : fix col, itr N -> move down ]
                                sum += a[a_col * target_row + n] * b[b_col * n + target_col];
                            }
                            // [ Matrix C : fix row, fix col ]
                            c[c_col * target_row + target_col] = sum;
                        }
                    );
                }
            );
            q->wait();
            time_tok = std::chrono::system_clock::now() - time_tick;
            if (debug_flag) {
                FUNC_TIME_MACRO
            }
        }
        else if (get_type == "int*") {
            sycl::buffer sycl_buf_a((int*)get_buf_a, sycl::range(get_m * get_n));
            sycl::buffer sycl_buf_b((int*)get_buf_b, sycl::range(get_n * get_p));
            sycl::buffer sycl_buf_c((int*)get_buf_c, sycl::range(get_m * get_p));
            time_tick = std::chrono::system_clock::now();
            q->submit(\
                [&](auto& h) {
                    sycl::accessor a(sycl_buf_a, h, sycl::read_only);
                    sycl::accessor b(sycl_buf_b, h, sycl::read_only);
                    sycl::accessor c(sycl_buf_c, h, sycl::write_only);
                    h.parallel_for(
                        sycl::range(get_m, get_p), [=](auto index) {
                            int sum = 0;

                            int64_t target_row = index[0];
                            int64_t target_col = index[1];
                            int64_t a_col = get_n;
                            int64_t b_col = get_p;
                            int64_t c_col = get_p;
                            int64_t itr_range = get_n;
                            for (int64_t n = 0; n < itr_range; n++) {
                                sum += a[a_col * target_row + n] * b[b_col * n + target_col];
                            }
                            c[c_col * target_row + target_col] = sum;
                        }
                    );
                }
            );
            q->wait();
            time_tok = std::chrono::system_clock::now() - time_tick;
            if (debug_flag) {
                FUNC_TIME_MACRO
            }
        }
        else if (get_type == "float*") {
            sycl::buffer sycl_buf_a((float*)get_buf_a, sycl::range(get_m * get_n));
            sycl::buffer sycl_buf_b((float*)get_buf_b, sycl::range(get_n * get_p));
            sycl::buffer sycl_buf_c((float*)get_buf_c, sycl::range(get_m * get_p));
            time_tick = std::chrono::system_clock::now();
            q->submit(\
                [&](auto& h) {
                    sycl::accessor a(sycl_buf_a, h, sycl::read_only);
                    sycl::accessor b(sycl_buf_b, h, sycl::read_only);
                    sycl::accessor c(sycl_buf_c, h, sycl::write_only);
                    h.parallel_for(
                        sycl::range(get_m, get_p), [=](auto index) {
                            float sum = 0.0f;

                            int64_t target_row = index[0];
                            int64_t target_col = index[1];
                            int64_t a_col = get_n;
                            int64_t b_col = get_p;
                            int64_t c_col = get_p;
                            int64_t itr_range = get_n;
                            for (int64_t n = 0; n < itr_range; n++) {
                                sum += a[a_col * target_row + n] * b[b_col * n + target_col];
                            }
                            c[c_col * target_row + target_col] = sum;
                        }
                    );
                }
            );
            q->wait();
            time_tok = std::chrono::system_clock::now() - time_tick;
            if (debug_flag) {
                FUNC_TIME_MACRO
            }
        }
        else if (get_type == "half*") {
            sycl::buffer sycl_buf_a((sycl::half*)get_buf_a, sycl::range(get_m * get_n));
            sycl::buffer sycl_buf_b((sycl::half*)get_buf_b, sycl::range(get_n * get_p));
            sycl::buffer sycl_buf_c((sycl::half*)get_buf_c, sycl::range(get_m * get_p));
            time_tick = std::chrono::system_clock::now();
            q->submit(\
                [&](auto& h) {
                    sycl::accessor a(sycl_buf_a, h, sycl::read_only);
                    sycl::accessor b(sycl_buf_b, h, sycl::read_only);
                    sycl::accessor c(sycl_buf_c, h, sycl::write_only);
                    h.parallel_for(
                        sycl::range(get_m, get_p), [=](auto index) {
                            sycl::half sum = 0.0f;

                            int64_t target_row = index[0];
                            int64_t target_col = index[1];
                            int64_t a_col = get_n;
                            int64_t b_col = get_p;
                            int64_t c_col = get_p;
                            int64_t itr_range = get_n;
                            for (int64_t n = 0; n < itr_range; n++) {
                                sum += a[a_col * target_row + n] * b[b_col * n + target_col];
                            }
                            c[c_col * target_row + target_col] = sum;
                        }
                    );
                }
            );
            q->wait();
            time_tok = std::chrono::system_clock::now() - time_tick;
            if (debug_flag) {
                FUNC_TIME_MACRO
            }
        }
        else {
            throw std::exception("need to update");
        }
    }
    CATCH_MACRO

    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void sycl_kernel_usm(std::string get_type, void*& queue_ptr, void*& get_buf_a, void*& get_buf_b, void*& get_buf_c, int64_t get_m, int64_t get_n, int64_t get_p, bool debug_flag) {
    try {

        FUNC_TYPE_MACRO

        std::chrono::system_clock::time_point time_tick;
        std::chrono::duration<double>time_tok;

        sycl::queue* q = (sycl::queue*)queue_ptr;

        // [ sycl pointer ]
        // Buffer type          : 1 Dimensions
        // Buffer count         : get_m x get_n
        //                      : get_n x get_p
        //                      : get_m x get_p
        // Create thread count  : sycl::range(get_m, get_p)
        //                      : get_m x get_p
        //                      : index[0] = 0 ~ ( get_m - 1 )
        //                      : index[1] = 0 ~ ( get_p - 1 )

        if (get_type == "char*") {
            char* buf_a = (char*)get_buf_a;
            char* buf_b = (char*)get_buf_b;
            char* buf_c = (char*)get_buf_c;
            time_tick = std::chrono::system_clock::now();
            q->submit(\
                [&](auto& h) {
                    h.parallel_for(
                        sycl::range(get_m, get_p), [=](auto index) {
                            char sum = 0;

                            int64_t target_row = index[0];
                            int64_t target_col = index[1];
                            int64_t a_col = get_n;
                            int64_t b_col = get_p;
                            int64_t c_col = get_p;
                            int64_t itr_range = get_n;
                            for (int64_t n = 0; n < itr_range; n++) {
                                sum += buf_a[a_col * target_row + n] * buf_b[b_col * n + target_col];
                            }
                            buf_c[c_col * target_row + target_col] = sum;
                        }
                    );
                }
            );
            q->wait();
            time_tok = std::chrono::system_clock::now() - time_tick;
            if (debug_flag) {
                FUNC_TIME_MACRO
            }
        }
        else if (get_type == "int*") {
            int* buf_a = (int*)get_buf_a;
            int* buf_b = (int*)get_buf_b;
            int* buf_c = (int*)get_buf_c;
            time_tick = std::chrono::system_clock::now();
            q->submit(\
                [&](auto& h) {
                    h.parallel_for(
                        sycl::range(get_m, get_p), [=](auto index) {
                            int sum = 0;

                            int64_t target_row = index[0];
                            int64_t target_col = index[1];
                            int64_t a_col = get_n;
                            int64_t b_col = get_p;
                            int64_t c_col = get_p;
                            int64_t itr_range = get_n;
                            for (int64_t n = 0; n < itr_range; n++) {
                                sum += buf_a[a_col * target_row + n] * buf_b[b_col * n + target_col];
                            }
                            buf_c[c_col * target_row + target_col] = sum;
                        }
                    );
                }
            );
            q->wait();
            time_tok = std::chrono::system_clock::now() - time_tick;
            if (debug_flag) {
                FUNC_TIME_MACRO
            }
        }
        else if (get_type == "float*") {
            float* buf_a = (float*)get_buf_a;
            float* buf_b = (float*)get_buf_b;
            float* buf_c = (float*)get_buf_c;
            time_tick = std::chrono::system_clock::now();
            q->submit(\
                [&](auto& h) {
                    h.parallel_for(
                        sycl::range(get_m, get_p), [=](auto index) {
                            float sum = 0.0f;

                            int64_t target_row = index[0];
                            int64_t target_col = index[1];
                            int64_t a_col = get_n;
                            int64_t b_col = get_p;
                            int64_t c_col = get_p;
                            int64_t itr_range = get_n;
                            for (int64_t n = 0; n < itr_range; n++) {
                                sum += buf_a[a_col * target_row + n] * buf_b[b_col * n + target_col];
                            }
                            buf_c[c_col * target_row + target_col] = sum;
                        }
                    );
                }
            );
            q->wait();
            time_tok = std::chrono::system_clock::now() - time_tick;
            if (debug_flag) {
                FUNC_TIME_MACRO
            }
        }
        else if (get_type == "float**") {
            throw std::exception("need to update");
        }
        else {
            throw std::exception("need to update");
        }

    }
    catch (std::exception& e) {
        printf("Exception : %s() : %s\n", __func__, e.what());
    }
    catch (...) {
        printf("Exception : unknown exception.\n");
    }

    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void sycl_kernel_random(std::string get_type, void*& queue_ptr, void*& get_buf, std::vector<int64_t> get_dim, bool debug_flag) {
    try {

        FUNC_TYPE_MACRO

        std::chrono::system_clock::time_point time_tick;
        std::chrono::duration<double>time_tok;

        sycl::queue* q = (sycl::queue*)queue_ptr;

        int64_t sizeof_count = 1;
        for (int64_t iter = 0; iter < get_dim.size(); iter++) {
            sizeof_count = sizeof_count * get_dim.at(iter);
        }
        int get_seed = 777;
        float dist_a = 0.0f;
        float dist_b = 1.0f;
        int range_mod = 10; // 0 ~ 9

        if (get_type == "char*") {

            time_tick = std::chrono::system_clock::now();
            q->submit(\
                [&](auto& h) {
                    h.parallel_for(
                        sycl::range(sizeof_count), [=](auto index) {
                            oneapi::dpl::minstd_rand get_engine(get_seed, (int64_t)index);
                            oneapi::dpl::uniform_real_distribution<float> get_distribution(dist_a, dist_b);
                            float get_value = get_distribution(get_engine);

                            ((char*)get_buf)[(int64_t)index] = (int)(get_value * 10000.0f) % range_mod;
                        }
                    );
                }
            );
            q->wait();
            time_tok = std::chrono::system_clock::now() - time_tick;
            if (debug_flag) {
                FUNC_TIME_MACRO
            }

        }
        else if (get_type == "int*") {

            time_tick = std::chrono::system_clock::now();
            q->submit(\
                [&](auto& h) {
                    h.parallel_for(
                        sycl::range(sizeof_count), [=](auto index) {
                            oneapi::dpl::minstd_rand get_engine(get_seed, (int64_t)index);
                            // 2024.01.12 - when device is gpu, can't use fp64. In here, something is fp64 : -->
                            //oneapi::dpl::uniform_int_distribution<int> get_distribution(dist_a, dist_b);
                            // 2024.01.12 - when device is gpu, can't use fp64. In here, something is fp64 : <--
                            oneapi::dpl::uniform_real_distribution<float> get_distribution(dist_a, dist_b);
                            float get_value = get_distribution(get_engine);

                            ((int*)get_buf)[(int64_t)index] = (int)(get_value * 10000.0f) % range_mod;
                        }
                    );
                }
            );
            q->wait();
            time_tok = std::chrono::system_clock::now() - time_tick;
            if (debug_flag) {
                FUNC_TIME_MACRO
            }

        }
        else if (get_type == "float*") {

            time_tick = std::chrono::system_clock::now();
            q->submit(\
                [&](auto& h) {
                    h.parallel_for(
                        sycl::range(sizeof_count), [=](auto index) {
                            oneapi::dpl::minstd_rand get_engine(get_seed, (int64_t)index);
                            oneapi::dpl::uniform_real_distribution<float> get_distribution(dist_a, dist_b);
                            float get_value = get_distribution(get_engine);

                            ((float*)get_buf)[(int64_t)index] = get_value;
                        }
                    );
                }
            );
            q->wait();
            time_tok = std::chrono::system_clock::now() - time_tick;
            if (debug_flag) {
                FUNC_TIME_MACRO
            }

        }
        else {
            throw std::exception("need to update");
        }

    }
    CATCH_MACRO

    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void sycl_kernel_usm_add(std::string get_type, void*& queue_ptr, void*& get_buf_a, void*& get_buf_b, void*& get_buf_c, std::vector<int64_t> get_dim, bool debug_flag) {
    try {

        FUNC_TYPE_MACRO

        std::chrono::system_clock::time_point time_tick;
        std::chrono::duration<double>time_tok;

        int64_t get_col = get_dim.at(0);
        int64_t get_row = get_dim.at(1);

        int64_t a_col = get_col;
        int64_t b_col = get_col;
        int64_t c_col = get_col;

        sycl::queue* q = (sycl::queue*)queue_ptr;

        if (get_type == "char*") {

            char* buf_a = (char*)get_buf_a;
            char* buf_b = (char*)get_buf_b;
            char* buf_c = (char*)get_buf_c;

            time_tick = std::chrono::system_clock::now();
            q->submit(\
                [&](sycl::handler& h) {
                    h.parallel_for(\
                        sycl::range(get_row, get_col), [=](auto index) {
                            int64_t target_row = index[0]; // 0 ~ get_row
                            int64_t target_col = index[1]; // 0 ~ get_col
                            buf_c[c_col * target_row + target_col] = buf_a[a_col * target_row + target_col] + buf_b[b_col * target_row + target_col];
                        }
                    );
                }
            );
            q->wait();
            time_tok = std::chrono::system_clock::now() - time_tick;
            if (debug_flag) {
                FUNC_TIME_MACRO
            }

        }
        else if (get_type == "int*") {

            int* buf_a = (int*)get_buf_a;
            int* buf_b = (int*)get_buf_b;
            int* buf_c = (int*)get_buf_c;

            time_tick = std::chrono::system_clock::now();
            q->submit(\
                [&](sycl::handler& h) {
                    h.parallel_for(\
                        sycl::range(get_row, get_col), [=](auto index) {
                            int64_t target_row = index[0];
                            int64_t target_col = index[1];
                            buf_c[c_col * target_row + target_col] = buf_a[a_col * target_row + target_col] + buf_b[b_col * target_row + target_col];
                        }
                    );
                }
            );
            q->wait();
            time_tok = std::chrono::system_clock::now() - time_tick;
            if (debug_flag) {
                FUNC_TIME_MACRO
            }

        }
        else if (get_type == "float*") {

            float* buf_a = (float*)get_buf_a;
            float* buf_b = (float*)get_buf_b;
            float* buf_c = (float*)get_buf_c;

            time_tick = std::chrono::system_clock::now();
            q->submit([&](sycl::handler& h) {
                h.parallel_for(\
                    sycl::range(get_row, get_col), [=](auto index) {
                        int64_t target_row = index[0];
                        int64_t target_col = index[1];
                        buf_c[c_col * target_row + target_col] = buf_a[a_col * target_row + target_col] + buf_b[b_col * target_row + target_col];
                    }
                );
                }
            );
            q->wait();
            time_tok = std::chrono::system_clock::now() - time_tick;
            if (debug_flag) {
                FUNC_TIME_MACRO
            }

        }
        else {
            throw std::exception("need to update");
        }

    }
    CATCH_MACRO

    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void sycl_kernel_usm_matmul(std::string get_type, void*& queue_ptr, void*& get_buf_a, void*& get_buf_b, void*& get_buf_c, int64_t get_m, int64_t get_n, int64_t get_p, bool debug_flag) {
    try {

        FUNC_TYPE_MACRO

        std::chrono::system_clock::time_point time_tick;
        std::chrono::duration<double>time_tok;

        int64_t get_col = get_p;
        int64_t get_row = get_m;
        int64_t get_itr = get_n;

        int64_t a_col = get_n;
        int64_t b_col = get_p;
        int64_t c_col = get_p;

        sycl::queue* q = (sycl::queue*)queue_ptr;

        if (get_type == "char*") {

            char* buf_a = (char*)get_buf_a;
            char* buf_b = (char*)get_buf_b;
            char* buf_c = (char*)get_buf_c;

            time_tick = std::chrono::system_clock::now();
            q->submit([&](sycl::handler& h) {
                h.parallel_for(\
                    sycl::range(get_row, get_col), [=](auto index) {
                        char sum = 0;
                        int64_t target_row = index[0]; // 0 ~ get_row
                        int64_t target_col = index[1]; // 0 ~ get_col
                        for (int64_t n = 0; n < get_itr; n++) {
                            // [ Matrix A (M x N) : fix row, itr N -> move right ]
                            // [ Matrix B (N x P) : fix col, itr N -> move down ]
                            sum += buf_a[a_col * target_row + n] * buf_b[b_col * n + target_col];
                        }
                        // [ Matrix C : fix row, fix col ]
                        buf_c[c_col * target_row + target_col] = sum;
                    }
                );
                }
            );
            q->wait();
            time_tok = std::chrono::system_clock::now() - time_tick;
            if (debug_flag) {
                FUNC_TIME_MACRO
            }

        }
        else if (get_type == "int*") {

            int* buf_a = (int*)get_buf_a;
            int* buf_b = (int*)get_buf_b;
            int* buf_c = (int*)get_buf_c;

            time_tick = std::chrono::system_clock::now();
            q->submit([&](sycl::handler& h) {
                    h.parallel_for(\
                        sycl::range(get_row, get_col), [=](auto index) {
                            int sum = 0;
                            int64_t target_row = index[0];
                            int64_t target_col = index[1];
                            for (int64_t n = 0; n < get_itr; n++) {
                                sum += buf_a[a_col * target_row + n] * buf_b[b_col * n + target_col];
                            }
                            buf_c[c_col * target_row + target_col] = sum;
                        }
                    );
                }
            );
            q->wait();
            time_tok = std::chrono::system_clock::now() - time_tick;
            if (debug_flag) {
                FUNC_TIME_MACRO
            }

        }
        else if (get_type == "float*") {

            float* buf_a = (float*)get_buf_a;
            float* buf_b = (float*)get_buf_b;
            float* buf_c = (float*)get_buf_c;

            time_tick = std::chrono::system_clock::now();
            q->submit([&](sycl::handler& h) {
                h.parallel_for(\
                    sycl::range(get_row, get_col), [=](auto index) {
                        float sum = 0.0f;
                        int64_t target_row = index[0];
                        int64_t target_col = index[1];
                        for (int64_t n = 0; n < get_itr; n++) {
                            sum += buf_a[a_col * target_row + n] * buf_b[b_col * n + target_col];
                        }
                        buf_c[c_col * target_row + target_col] = sum;
                    }
                );
                }
            );
            q->wait();
            time_tok = std::chrono::system_clock::now() - time_tick;
            if (debug_flag) {
                FUNC_TIME_MACRO
            }

        }
        else {
            throw std::exception("need to update");
        }

    }
    CATCH_MACRO

    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////















//////////////////////////////////////////////////////////////////////////////////////////////////////

// compare

void test_compare(void) {
    try {

        test_compare_add();
        test_compare_matmul();

    }
    CATCH_MACRO

    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// 64   x 64   : std iter is fast
// 1024 x 1024 : sycl + device memory is fast

void test_compare_add(void) {
    try {

        TEST_TITLE_MACRO

        int64_t M = 1024;
        int64_t N = 1024;

        std::vector<int64_t> dim_a;
        dim_a.clear();
        dim_a.push_back(N);
        dim_a.push_back(M);

        std::vector<int64_t> dim_b;
        dim_b.clear();
        dim_b.push_back(N);
        dim_b.push_back(M);

        std::vector<int64_t> dim_c;
        dim_c.clear();
        dim_c.push_back(N);
        dim_c.push_back(M);

        void* device_ptr = nullptr;
        void* queue_ptr = nullptr;

        void* ptr_a = nullptr;
        void* ptr_b = nullptr;
        void* ptr_c = nullptr;
        void* ptr_itr = nullptr;

        void* ptr_sycl_a = nullptr;
        void* ptr_sycl_b = nullptr;
        void* ptr_sycl_c = nullptr;

        // [ Test ]
        for (int iter_device = 0; iter_device < static_dev.size(); iter_device++) {

            sycl_device(static_dev.at(iter_device), device_ptr);
            sycl_queue("device", queue_ptr, device_ptr);

            for (int iter_dtype = 0; iter_dtype < static_dtype.size(); iter_dtype++) {

                printf("\nFunc : data type : %s\n", static_dtype.at(iter_dtype).c_str());

                for (int iter_mtype = 0; iter_mtype < static_mtype.size(); iter_mtype++) {

                    printf("\nFunc : memory type : %s\n", static_mtype.at(iter_mtype).c_str());

                    std_mem_set(static_dtype.at(iter_dtype), ptr_a, dim_a, false);
                    std_mem_set(static_dtype.at(iter_dtype), ptr_b, dim_b, false);
                    std_mem_set(static_dtype.at(iter_dtype), ptr_c, dim_c, false);
                    std_mem_set(static_dtype.at(iter_dtype), ptr_itr, dim_c, false);

                    std_mem_init(static_dtype.at(iter_dtype), ptr_a, dim_a, (double)1.0, false);
                    std_mem_init(static_dtype.at(iter_dtype), ptr_b, dim_b, (double)1.0, false);
                    std_mem_init(static_dtype.at(iter_dtype), ptr_c, dim_c, (double)0.0, false);
                    std_mem_init(static_dtype.at(iter_dtype), ptr_itr, dim_c, (double)0.0, false);

                    sycl_mem_set(static_dtype.at(iter_dtype), static_mtype.at(iter_mtype), queue_ptr, ptr_sycl_a, dim_a, false);
                    sycl_mem_set(static_dtype.at(iter_dtype), static_mtype.at(iter_mtype), queue_ptr, ptr_sycl_b, dim_b, false);
                    sycl_mem_set(static_dtype.at(iter_dtype), static_mtype.at(iter_mtype), queue_ptr, ptr_sycl_c, dim_c, false);

                    sycl_mem_init(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_a, dim_a, (double)0.0, false);
                    sycl_mem_init(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_b, dim_b, (double)0.0, false);
                    sycl_mem_init(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_c, dim_c, (double)0.0, false);

                    sycl_mem_copy(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_a, ptr_a, dim_a, false);
                    sycl_mem_copy(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_b, ptr_b, dim_b, false);
                    sycl_mem_copy(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_c, ptr_c, dim_c, false);

                    sycl_kernel_usm_add(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_a, ptr_sycl_b, ptr_sycl_c, dim_c, true);
                    std_kernel_iter_add(static_dtype.at(iter_dtype), ptr_a, ptr_b, ptr_itr, dim_c, true);

                    sycl_mem_copy(static_dtype.at(iter_dtype), queue_ptr, ptr_c, ptr_sycl_c, dim_c, false);

                    std_iter_compare(static_dtype.at(iter_dtype), ptr_c, ptr_itr, dim_c);

                    std_iter_print(static_dtype.at(iter_dtype), ptr_c, dim_c, false);

                    sycl_mem_free(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_a, dim_a, false);
                    sycl_mem_free(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_b, dim_b, false);
                    sycl_mem_free(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_c, dim_c, false);

                    std_mem_free(static_dtype.at(iter_dtype), ptr_a, dim_a, false);
                    std_mem_free(static_dtype.at(iter_dtype), ptr_b, dim_b, false);
                    std_mem_free(static_dtype.at(iter_dtype), ptr_c, dim_c, false);
                    std_mem_free(static_dtype.at(iter_dtype), ptr_itr, dim_c, false);

                }
            }

            sycl_delete("queue", queue_ptr);
            sycl_delete("device", device_ptr);

        }

    }
    CATCH_MACRO

    return;
}

void test_compare_matmul(void) {
    try {

        TEST_TITLE_MACRO

        int64_t M = 1024;
        int64_t N = 1024;
        int64_t P = 1024;

        std::vector<int64_t> dim_a;
        dim_a.clear();
        dim_a.push_back(N);
        dim_a.push_back(M);

        std::vector<int64_t> dim_b;
        dim_b.clear();
        dim_b.push_back(P);
        dim_b.push_back(N);

        std::vector<int64_t> dim_c;
        dim_c.clear();
        dim_c.push_back(P);
        dim_c.push_back(M);

        void* device_ptr = nullptr;
        void* queue_ptr = nullptr;

        void* ptr_a = nullptr;
        void* ptr_b = nullptr;
        void* ptr_c = nullptr;
        void* ptr_itr = nullptr;

        void* ptr_sycl_a = nullptr;
        void* ptr_sycl_b = nullptr;
        void* ptr_sycl_c = nullptr;

        // [ Test ]
        for (int iter_device = 0; iter_device < static_dev.size(); iter_device++) {

            sycl_device(static_dev.at(iter_device), device_ptr);
            sycl_queue("device", queue_ptr, device_ptr);

            for (int iter_dtype = 0; iter_dtype < static_dtype.size(); iter_dtype++) {

                printf("\nFunc : data type : %s\n", static_dtype.at(iter_dtype).c_str());

                for (int iter_mtype = 0; iter_mtype < static_mtype.size(); iter_mtype++) {

                    printf("\nFunc : memory type : %s\n", static_mtype.at(iter_mtype).c_str());

                    std_mem_set(static_dtype.at(iter_dtype), ptr_a, dim_a, false);
                    std_mem_set(static_dtype.at(iter_dtype), ptr_b, dim_b, false);
                    std_mem_set(static_dtype.at(iter_dtype), ptr_c, dim_c, false);
                    std_mem_set(static_dtype.at(iter_dtype), ptr_itr, dim_c, false);

                    std_mem_init(static_dtype.at(iter_dtype), ptr_a, dim_a, (double)1.0, false);
                    std_mem_init(static_dtype.at(iter_dtype), ptr_b, dim_b, (double)1.0, false);
                    std_mem_init(static_dtype.at(iter_dtype), ptr_c, dim_c, (double)0.0, false);
                    std_mem_init(static_dtype.at(iter_dtype), ptr_itr, dim_c, (double)0.0, false);

                    sycl_mem_set(static_dtype.at(iter_dtype), static_mtype.at(iter_mtype), queue_ptr, ptr_sycl_a, dim_a, false);
                    sycl_mem_set(static_dtype.at(iter_dtype), static_mtype.at(iter_mtype), queue_ptr, ptr_sycl_b, dim_b, false);
                    sycl_mem_set(static_dtype.at(iter_dtype), static_mtype.at(iter_mtype), queue_ptr, ptr_sycl_c, dim_c, false);

                    sycl_mem_init(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_a, dim_a, (double)0.0, false);
                    sycl_mem_init(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_b, dim_b, (double)0.0, false);
                    sycl_mem_init(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_c, dim_c, (double)0.0, false);

                    sycl_mem_copy(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_a, ptr_a, dim_a, false);
                    sycl_mem_copy(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_b, ptr_b, dim_b, false);
                    sycl_mem_copy(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_c, ptr_c, dim_c, false);

                    sycl_kernel_usm_matmul(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_a, ptr_sycl_b, ptr_sycl_c, M, N, P, true);
                    std_kernel_iter_matmul(static_dtype.at(iter_dtype), ptr_a, ptr_b, ptr_itr, M, N, P, true);

                    sycl_mem_copy(static_dtype.at(iter_dtype), queue_ptr, ptr_c, ptr_sycl_c, dim_c, false);

                    std_iter_compare(static_dtype.at(iter_dtype), ptr_c, ptr_itr, dim_c);

                    std_iter_print(static_dtype.at(iter_dtype), ptr_c, dim_c, false);

                    sycl_mem_free(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_a, dim_a, false);
                    sycl_mem_free(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_b, dim_b, false);
                    sycl_mem_free(static_dtype.at(iter_dtype), queue_ptr, ptr_sycl_c, dim_c, false);

                    std_mem_free(static_dtype.at(iter_dtype), ptr_a, dim_a, false);
                    std_mem_free(static_dtype.at(iter_dtype), ptr_b, dim_b, false);
                    std_mem_free(static_dtype.at(iter_dtype), ptr_c, dim_c, false);
                    std_mem_free(static_dtype.at(iter_dtype), ptr_itr, dim_c, false);

                }
            }

            sycl_delete("queue", queue_ptr);
            sycl_delete("device", device_ptr);

        }

    }
    CATCH_MACRO

    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////




































































