project(SuperTeacher)

# CMake >3.0 must be used
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

include( CTest )
include ( ExternalProject )

# Custom cmake module in ./cmake/
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${SuperTeacher_SOURCE_DIR}/cmake")

if(MSVC)
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
endif()

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

add_definitions(-D_INSTALL_PREFIX="${CMAKE_INSTALL_PREFIX}")
add_definitions(-D_SRC_DIR="${CMAKE_SOURCE_DIR}")

if(WIN32)
    add_definitions(-DWIN32)
endif()

# Build program binary
add_subdirectory(src)

if(WIN32)
else()
  add_subdirectory(tests)
endif()

add_subdirectory(assets)

# Installer config
include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE  
        "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
include (CPack)
