file(GLOB_RECURSE HEADERS "*.h")
file(GLOB_RECURSE SOURCES "*.cpp")
set(ALL_FILES ${HEADERS} ${SOURCES})

add_library(scene STATIC ${ALL_FILES})

target_include_directories(scene PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
