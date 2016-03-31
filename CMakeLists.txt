# CMake Main Configuration file
# =============================
#
# This file is the main file used for generating project file that
# build with IDE or makefile.

project(SuperTeacher)

# CMake >3.1 must be used, (for c++14)
cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

# We use optional Cmake functionality:
#   - CTest: Automatically call all unit test binary with a single ctest
#            command
#   - ExternalProject: Automatically download some small dependancie,
#                      like Google Test Framework
include( CTest )
include ( ExternalProject )


# We put custom CMake Module in ./cmake/
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${SuperTeacher_SOURCE_DIR}/cmake")

# Todo: Remove set BIN_DIR
# Binary in ./bin
set(BIN_DIR ${SuperTeacher_SOURCE_DIR}/bin)

# Bump up warning levels appropriately for clang, gcc & msvc
# Also set debug/optimization flags depending on the build type. IDE users choose this when
# selecting the build mode in their IDE
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -g")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -O2")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
endif()

# On Windows, we use static linking to libc++
if(MSVC)
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif()

# Pass some info to our source code, by defining them
add_definitions(-D_INSTALL_PREFIX="${CMAKE_INSTALL_PREFIX}")
add_definitions(-D_SRC_DIR="${CMAKE_SOURCE_DIR}")

if(WIN32)
    add_definitions(-DWIN32)
endif()

# Build program binary
add_subdirectory(src)
add_subdirectory(tests)

# Add static file
add_subdirectory(assets)

# Installer config
include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE  
        "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
include (CPack)
