project(superteacher)

find_package(SFML 2.4 COMPONENTS graphics window system audio)
include_directories(${SFML_INCLUDE_DIR})

add_executable(superteacher
        main.cpp
        MainWindow.cpp
        Path.cpp
)

target_link_libraries(superteacher ${SFML_LIBRARIES})
install(TARGETS superteacher RUNTIME DESTINATION bin)
set_property(TARGET superteacher PROPERTY CXX_STANDARD 14)
