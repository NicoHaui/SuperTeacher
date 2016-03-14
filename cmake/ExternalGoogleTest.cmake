# Single download(git clone)
ExternalProject_Add(
    googletest
    URL https://github.com/google/googletest/archive/release-1.7.0.tar.gz
    LOG_DOWNLOAD ON
    INSTALL_COMMAND ""
)

ExternalProject_Get_Property(googletest source_dir)
ExternalProject_Get_Property(googletest binary_dir)

set(GTEST_INCLUDE_DIRS "${source_dir}/include" CACHE STRING "GTEST include")
set(GTEST_BOTH_LIBRARIES "${binary_dir}/libgtest.a;${binary_dir}/libgtest_main.a" CACHE STRING "GTEST Library")

