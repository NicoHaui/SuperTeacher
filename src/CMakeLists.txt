project(SuperTeacher)
add_executable(SuperTeacher main.cpp)
target_link_libraries(SuperTeacher ${SDL2_LIBRARY})
install(TARGETS SuperTeacher RUNTIME DESTINATION ${BIN_DIR})
