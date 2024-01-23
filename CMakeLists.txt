################################################################################
# Before project
################################################################################

# VS code
    # .vscode/tasks.json ( create cache )
    # .vscode/launch.json ( build and debug )

# Visual studio 2019
    # CMakeSettings.json ( build )

# Source code character-set
    # Unicode UTF-8 without BOM(Byte Order Mark)

# oneAPI Version
    # Windows10
        # 2023.2.0.49396
            # C:\Program Files (x86)\Intel\oneAPI\setvars.bat
            # C:\Program Files (x86)\Intel\oneAPI\setvars-vcvarsall.bat
            # sycl6
            # pi_opencl
            # pi_win_proxy_loader
        # 2024.0.1.45_offline.exe
            # cmd -> setx SETVARS_CONFIG " "
            # C:\Program Files (x86)\Intel\oneAPI\setvars.bat
            # C:\Program Files (x86)\Intel\oneAPI\setvars-vcvarsall.bat
            # sycl7.dll
            # pi_opencl.dll
            # pi_win_proxy_loader.dll
            # libmmd.dll
    # Ubuntu2204
        # 'intel-i915-dkms'
            # install is not necessary condition.
        # ./opt/intel/oneapi/setvars.sh --force
            # for not confuse, use flag '--force'

# Issue
    # 2024.01.08
        # arcA770 is 16GB, but malloc max is 4GB ( approximately )
        # 'max_mem_alloc_size' is quarter of 'global_mem_size'. ( approximately )
        # reason is openCL ?

################################################################################
# Start project
################################################################################
cmake_minimum_required (VERSION 3.4)

project(project_oneapi VERSION 0.1 DESCRIPTION "project_oneapi" LANGUAGES NONE)

################################################################################
# CMake Directory
################################################################################
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_BINARY_DIR "${CMAKE_SOURCE_DIR}/out/Debug/")
else()
    set(CMAKE_BINARY_DIR "${CMAKE_SOURCE_DIR}/out/Release/")
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

message(STATUS "${PROJECT_NAME} : CMAKE_BUILD_TYPE set to [${CMAKE_BUILD_TYPE}]") # source build type
message(STATUS "${PROJECT_NAME} : CMAKE_SOURCE_DIR set to [${CMAKE_SOURCE_DIR}]") # source directory path
message(STATUS "${PROJECT_NAME} : CMAKE_BINARY_DIR set to [${CMAKE_BINARY_DIR}]") # build output directory path
message(STATUS "${PROJECT_NAME} : CMAKE_ARCHIVE_OUTPUT_DIRECTORY set to [${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}]") # build output directory path
message(STATUS "${PROJECT_NAME} : CMAKE_LIBRARY_OUTPUT_DIRECTORY set to [${CMAKE_LIBRARY_OUTPUT_DIRECTORY}]") # build output directory path
message(STATUS "${PROJECT_NAME} : CMAKE_RUNTIME_OUTPUT_DIRECTORY set to [${CMAKE_RUNTIME_OUTPUT_DIRECTORY}]") # build output directory path

################################################################################
# Copy
################################################################################
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    file(COPY "C:/Program Files (x86)/Intel/oneAPI/compiler/2024.0/bin/OpenCL.dll"                  DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY "C:/Program Files (x86)/Intel/oneAPI/compiler/2024.0/bin/pi_opencl.dll"               DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY "C:/Program Files (x86)/Intel/oneAPI/compiler/2024.0/bin/sycl7d.dll"                  DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY "C:/Program Files (x86)/Intel/oneAPI/compiler/2024.0/bin/pi_win_proxy_loaderd.dll"    DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY "C:/Program Files (x86)/Intel/oneAPI/compiler/2024.0/bin/libmmdd.dll"                 DESTINATION ${CMAKE_BINARY_DIR})    
else()
    file(COPY "C:/Program Files (x86)/Intel/oneAPI/compiler/2024.0/bin/OpenCL.dll"                  DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY "C:/Program Files (x86)/Intel/oneAPI/compiler/2024.0/bin/pi_opencl.dll"               DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY "C:/Program Files (x86)/Intel/oneAPI/compiler/2024.0/bin/sycl7.dll"                   DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY "C:/Program Files (x86)/Intel/oneAPI/compiler/2024.0/bin/pi_win_proxy_loader.dll"     DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY "C:/Program Files (x86)/Intel/oneAPI/compiler/2024.0/bin/libmmd.dll"                  DESTINATION ${CMAKE_BINARY_DIR})
endif()

################################################################################
# Source
################################################################################

add_subdirectory(oneapi_test01_official)
add_subdirectory(oneapi_test02_user)
