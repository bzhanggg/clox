add_library(common_lib STATIC
    chunk.cpp
    value.cpp
)

target_include_directories(common_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(debug_lib STATIC
    debug.cpp
)

target_include_directories(debug_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(debug_lib PUBLIC common_lib)