enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(runUnitTests main.cpp test_hello.cpp)

target_link_libraries(runUnitTests ${GTEST_BOTH_LIBRARIES})
install(TARGETS runUnitTests RUNTIME DESTINATION ${BIN_DIR})

add_test(
    NAME runUnitTests
    COMMAND runUnitTests
)
