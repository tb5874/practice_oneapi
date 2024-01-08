################################################################################
# Before project
################################################################################
if(WIN32)
    # Force CMake to use icx-cl rather than the default C++ compiler/linker. needed on Windows only
    include (CMakeForceCompiler)
    CMAKE_FORCE_CXX_COMPILER(icx-cl IntelDPCPP)
    include (Platform/Windows-Clang)
elseif(UNIX)
    # Direct CMake to use icpx rather than the default C++ compiler/linker.
    set(CMAKE_CXX_COMPILER icpx)
endif()

################################################################################
# Start project
################################################################################
#project(##### VERSION 0.1 DESCRIPTION "#####" LANGUAGES NONE)
set(PROJECT_NAME icx_test_01_make_executable)
set(ROOT_NAMESPACE icx_test_01_make_executable)
message(STATUS "PROJECT_NAME : [${PROJECT_NAME}]")
message(STATUS "ROOT_NAMESPACE : [${ROOT_NAMESPACE}]")

################################################################################
# Language C
################################################################################
if(False)
    enable_language(C)
    set(CMAKE_C_STANDARD_FORCE True)
    if (CMAKE_C_STANDARD_FORCE)
        set(CMAKE_C_STANDARD 18)
    endif()
    set(CMAKE_C_STANDARD_REQUIRED ON)
    message(STATUS "${PROJECT_NAME} : CMAKE_C_COMPILER set to [${CMAKE_C_COMPILER}]")
    message(STATUS "${PROJECT_NAME} : CMAKE_C_STANDARD_FORCE set to [${CMAKE_C_STANDARD_FORCE}]")
    message(STATUS "${PROJECT_NAME} : CMAKE_C_STANDARD set to [${CMAKE_C_STANDARD}]")
    message(STATUS "${PROJECT_NAME} : CMAKE_C_STANDARD_REQUIRED set to [${CMAKE_C_STANDARD_REQUIRED}]")
    message(STATUS "${PROJECT_NAME} : CMAKE_C_FLAGS_DEBUG set to [${CMAKE_C_FLAGS_DEBUG}]")
    message(STATUS "${PROJECT_NAME} : CMAKE_C_FLAGS_RELEASE set to [${CMAKE_C_FLAGS_RELEASE}]")
endif()

################################################################################
# Language CXX
################################################################################
if(True)
    enable_language(CXX)
    set(CMAKE_CXX_STANDARD_FORCE True)
    if (CMAKE_CXX_STANDARD_FORCE)
        set(CMAKE_CXX_STANDARD 17)
    endif()
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    message(STATUS "${PROJECT_NAME} : CMAKE_CXX_COMPILER set to [${CMAKE_CXX_COMPILER}]")
    message(STATUS "${PROJECT_NAME} : CMAKE_CXX_STANDARD_FORCE set to [${CMAKE_CXX_STANDARD_FORCE}]")
    message(STATUS "${PROJECT_NAME} : CMAKE_CXX_STANDARD set to [${CMAKE_CXX_STANDARD}]")
    message(STATUS "${PROJECT_NAME} : CMAKE_CXX_STANDARD_REQUIRED set to [${CMAKE_CXX_STANDARD_REQUIRED}]")
    message(STATUS "${PROJECT_NAME} : CMAKE_CXX_FLAGS_DEBUG set to [${CMAKE_CXX_FLAGS_DEBUG}]")
    message(STATUS "${PROJECT_NAME} : CMAKE_CXX_FLAGS_RELEASE set to [${CMAKE_CXX_FLAGS_RELEASE}]")
endif()

################################################################################
# Compile Option
################################################################################
# https://www.intel.com/content/www/us/en/docs/cpp-compiler/developer-guide-reference/2021-10/alphabetical-option-list.html
# https://www.intel.com/content/dam/develop/external/us/en/documents/oneapi_dpcpp_cpp_compiler.pdf
if(WIN32)
    list(APPEND COMPILE_OPTIONS
        "$<$<COMPILE_LANGUAGE:CXX>:"
            "$<$<CONFIG:Debug>:"
                # add flag
                "/std:c++17"    # Tells the compiler to conform to a specific language standard.
                "/debug:all"    # Generates complete debugging information.
                "/Zi"           # the compiler to generate symbolic debugging information in a program database (PDB) file for use with the debugger.
                "/Od"           # Disables all optimizations.
                "/MDd"          # Tells the linker to search for unresolved references in a multithreaded, dynamic-link runtime library. ( Debug )
            ">"
            "$<$<CONFIG:Release>:"
                # add flag
                "/MD"           # Tells the linker to search for unresolved references in a multithreaded, dynamic-link runtime library. ( Release )
            ">"
            # add flag
            "/EHsc"             # Specifies the model of exception handling to be performed.            
            "-fsycl"            # Enables a program to be compiled as a SYCL program rather than as plain C++11 program.
            "-Wall"             # Enables warning and error diagnostics.
        ">"
    )
elseif(UNIX)
    list(APPEND COMPILE_OPTIONS
        "$<$<COMPILE_LANGUAGE:CXX>:"
            "$<$<CONFIG:Debug>:"
                # add flag
            ">"
            "$<$<CONFIG:Release>:"
                # add flag
            ">"
            # add flag
        ">"
    )
endif()

################################################################################
# Link Option
################################################################################
if(WIN32)
    list(APPEND LINK_OPTIONS
        "$<$<COMPILE_LANGUAGE:CXX>:"
            "$<$<CONFIG:Debug>:"
                # add flag
                "/debug:all"    # Generates complete debugging information.
                "/Od"           # Disables all optimizations.
            ">"
            "$<$<CONFIG:Release>:"
                # add flag                
            ">"
            # add flag
            "-fsycl"            # Enables a program to be compiled as a SYCL program rather than as plain C++11 program.
        ">"
    )
elseif(UNIX)
    list(APPEND LINK_OPTIONS
        "$<$<COMPILE_LANGUAGE:CXX>:"
            "$<$<CONFIG:Debug>:"
                # add flag                
            ">"
            "$<$<CONFIG:Release>:"
                # add flag
            ">"
            # add flag
        ">"
    )
endif()

################################################################################
# Sub-projects
################################################################################
add_subdirectory(vector_add_buffer)
add_subdirectory(vector_add_usm)
