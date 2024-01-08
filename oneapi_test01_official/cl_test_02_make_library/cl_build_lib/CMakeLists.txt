set(PROJECT_NAME cl_build_lib)
set(ROOT_NAMESPACE cl_build_lib)
message(STATUS "PROJECT_NAME : [${PROJECT_NAME}]")
message(STATUS "ROOT_NAMESPACE : [${ROOT_NAMESPACE}]")

################################################################################
# File list
################################################################################

# [ Type 1 ]
# The GLOB_RECURSE mode will traverse all the subdirectories of the matched directory and match the files.
file(GLOB_RECURSE cpp_file "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
source_group("cpp_file" FILES ${cpp_file})

# The GLOB_RECURSE mode will traverse all the subdirectories of the matched directory and match the files.
file(GLOB_RECURSE hpp_file "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")
source_group("hpp_file" FILES ${hpp_file})

set(all_file ${cpp_file} ${hpp_file})

message(STATUS "${PROJECT_NAME} : all_file set to [${all_file}]")

# [ Type 2 ]
#set(cpp_file
#    "./###.cpp"
#    "./###.hpp"
#)

################################################################################
# Executable or Library
################################################################################
#add_executable(${PROJECT_NAME} ${all_file})
add_library(${PROJECT_NAME} SHARED ${all_file})

################################################################################
# User define flag
################################################################################
list(APPEND USER_DEFINE_FLAG
    # add flag
    "EXPORT_FLAG"
)
target_compile_definitions(${PROJECT_NAME} PRIVATE "${USER_DEFINE_FLAG}")
message(STATUS "${PROJECT_NAME} : USER_DEFINE_FLAG set to [${USER_DEFINE_FLAG}]")

################################################################################
# target_compile_options
################################################################################
if(WIN32)
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
target_compile_options(${PROJECT_NAME} PRIVATE "${COMPILE_OPTIONS}")
message(STATUS "${PROJECT_NAME} : COMPILE_OPTIONS set to [${COMPILE_OPTIONS}]")

################################################################################
# target_link_options
################################################################################
if(WIN32)
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
target_link_options(${PROJECT_NAME} PRIVATE "${LINK_OPTIONS}")
message(STATUS "${PROJECT_NAME} : LINK_OPTIONS set to [${LINK_OPTIONS}]")

################################################################################
# Additional include directories
################################################################################
if(WIN32)
    list(APPEND ADDITIONAL_INCLUDE_DIRECTORIES
        "$<$<COMPILE_LANGUAGE:CXX>:"
            "$<$<CONFIG:Debug>:"
                # add directory path            
            ">"
            "$<$<CONFIG:Release>:"
                # add directory path
            ">"
            # add directory path
            "${CMAKE_CURRENT_SOURCE_DIR}"
        ">"
    )
elseif(UNIX)
    list(APPEND ADDITIONAL_INCLUDE_DIRECTORIES
        "$<$<COMPILE_LANGUAGE:CXX>:"
            "$<$<CONFIG:Debug>:"
                # add directory path            
            ">"
            "$<$<CONFIG:Release>:"
                # add directory path
            ">"
            # add directory path
            "${CMAKE_CURRENT_SOURCE_DIR}"
        ">"
    )
endif()
target_include_directories(${PROJECT_NAME} PUBLIC "${ADDITIONAL_INCLUDE_DIRECTORIES}")
message(STATUS "${PROJECT_NAME} : ADDITIONAL_INCLUDE_DIRECTORIES set to ${ADDITIONAL_INCLUDE_DIRECTORIES}")

################################################################################
# Additional library directories
################################################################################
if(WIN32)
    list(APPEND ADDITIONAL_LIBRARY_DIRECTORIES
        "$<$<COMPILE_LANGUAGE:CXX>:"
            "$<$<CONFIG:Debug>:"
                # add directory path            
            ">"
            "$<$<CONFIG:Release>:"
                # add directory path
            ">"
            # add directory path
        ">"
    )
elseif(UNIX)
    list(APPEND ADDITIONAL_LIBRARY_DIRECTORIES
        "$<$<COMPILE_LANGUAGE:CXX>:"
            "$<$<CONFIG:Debug>:"
                # add directory path            
            ">"
            "$<$<CONFIG:Release>:"
                # add directory path
            ">"
            # add directory path
        ">"
    )
endif()
target_link_directories(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DIRECTORIES}")
message(STATUS "${PROJECT_NAME} : ADDITIONAL_LIBRARY_DIRECTORIES set to ${ADDITIONAL_LIBRARY_DIRECTORIES}")

################################################################################
# Additional library link
################################################################################
if(WIN32)
    list(APPEND ADDITIONAL_LIBRARY_LINK
        "$<$<CONFIG:Debug>:"
            # add library
        ">"
        "$<$<CONFIG:Release>:"
            # add library
        ">"
        # add library
    )
elseif(UNIX)
    list(APPEND ADDITIONAL_LIBRARY_LINK
        "$<$<CONFIG:Debug>:"
            # add library
        ">"
        "$<$<CONFIG:Release>:"
            # add library
        ">"
        # add library
    )
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_LINK}")
message(STATUS "${PROJECT_NAME} : ADDITIONAL_LIBRARY_LINK set to ${ADDITIONAL_LIBRARY_LINK}")

################################################################################
# Additional setting
################################################################################
set(CMAKE_SHARED_LIBRARY_PREFIX "")
