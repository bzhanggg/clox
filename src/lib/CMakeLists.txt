add_library(clox_lib STATIC
    chunk.cpp
)

target_include_directories(clox_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})