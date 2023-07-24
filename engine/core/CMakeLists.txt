add_library(core STATIC
    test.h
    test.cpp
)

target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
