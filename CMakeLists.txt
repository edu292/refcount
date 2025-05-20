cmake_minimum_required(VERSION 3.31)
project(RefcountGC_Tests)

set(CMAKE_C_STANDARD 11)

add_library(unity STATIC
        unity/src/unity.c
)

target_include_directories(unity PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/unity/src
)

add_library(gc STATIC
        object.c
)

target_include_directories(gc PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(test_gc
        tester.c
)

target_link_libraries(test_gc
        gc
        unity
)

enable_testing()
add_test(NAME RunRefcountTests COMMAND test_gc)