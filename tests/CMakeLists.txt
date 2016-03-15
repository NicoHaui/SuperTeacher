enable_testing()

#find_package(GTest REQUIRED)
include( ExternalGoogleTest )
include_directories(${GTEST_INCLUDE_DIRS})

find_package( Threads REQUIRED)

add_executable(runUnitTests main.cpp test_hello.cpp)

target_link_libraries(
  runUnitTests ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT}
)

install(TARGETS runUnitTests RUNTIME DESTINATION ${BIN_DIR})

add_test(
    NAME runUnitTests
    COMMAND runUnitTests
)
