project(superteacher)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

add_executable(superteacher
        main.c
        MainWindow.c
)

target_link_libraries(superteacher ${SDL2_LIBRARY})
install(TARGETS superteacher RUNTIME DESTINATION bin)
