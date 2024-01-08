################################################################################
# Source
################################################################################

# For test ICX compiler
    # 'TEST_COMPILER_ICX' is ON
    # 'TEST_COMPILER_OTHER' is OFF
# For test other compiler
    # 'TEST_COMPILER_ICX' is OFF
    # 'TEST_COMPILER_OTHER' is ON
set(TEST_COMPILER_ICX ON)
set(TEST_COMPILER_OTHER OFF)

if(TEST_COMPILER_ICX)
    add_subdirectory(icx_test_01_make_executable)
    add_subdirectory(icx_test_02_make_library)
    add_subdirectory(icx_test_03_use_library)
endif()

if(TEST_COMPILER_OTHER)
    add_subdirectory(cl_test_01_make_executable)
    add_subdirectory(cl_test_02_make_library)
    add_subdirectory(cl_test_03_use_library)
endif()
