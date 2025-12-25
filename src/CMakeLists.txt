add_subdirectory(common)

add_executable(clox main.cpp)

target_link_libraries(clox
PRIVATE
    common_lib
)
