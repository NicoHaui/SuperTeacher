project(superteacher)

find_package(SFML 2.1 REQUIRED COMPONENTS graphics window system audio)

set(Boost_USE_STATIC_LIBS       OFF)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
set(BOOST_ALL_DYN_LINK           ON)   # force dynamic linking for all libraries
find_package(Boost 1.54 REQUIRED COMPONENTS system filesystem)

include_directories(${SFML_INCLUDE_DIR} ${Boost_INCLUDE_DIR})

add_executable(superteacher
        main.cpp
        MainWindow.cpp
        Path.cpp
)

target_link_libraries(superteacher ${SFML_LIBRARIES} ${Boost_LIBRARIES})
install(TARGETS superteacher RUNTIME DESTINATION bin)
set_property(TARGET superteacher PROPERTY CXX_STANDARD 14)
