project(SuperTeacher)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

add_executable(SuperTeacher main.cpp)
target_link_libraries(SuperTeacher ${SDL2_LIBRARY})
install(TARGETS SuperTeacher RUNTIME DESTINATION ${BIN_DIR})
