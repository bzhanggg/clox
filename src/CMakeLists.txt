add_subdirectory(lib)

add_executable(clox
    scanner.cpp
    compiler.cpp
    vm.cpp
    main.cpp
)

target_link_libraries(clox
PRIVATE
    common_lib
    debug_lib
)
