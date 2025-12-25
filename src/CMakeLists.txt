add_subdirectory(lib)

add_executable(clox main.cpp)

target_link_libraries(clox PRIVATE clox_lib)
