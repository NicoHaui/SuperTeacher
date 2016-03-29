project(superteacher)

find_package(SFML 2.3 REQUIRED COMPONENTS graphics window system audio)
find_package(Boost 1.60 REQUIRED COMPONENTS filesystem)

include_directories(${SFML_INCLUDE_DIR} ${Boost_INCLUDE_DIR})

add_executable(superteacher
        main.cpp
        MainWindow.cpp
        Path.cpp
)

target_link_libraries(superteacher ${SFML_LIBRARIES} ${Boost_LIBRARIES})
install(TARGETS superteacher RUNTIME DESTINATION bin)
set_property(TARGET superteacher PROPERTY CXX_STANDARD 14)
