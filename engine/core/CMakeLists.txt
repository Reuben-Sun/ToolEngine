file(GLOB_RECURSE HEADERS "include/*/*.h")
file(GLOB_RECURSE SOURCES "*src/*/*.cpp")
set(ALL_FILES ${HEADERS} ${SOURCES})

add_library(core STATIC ${ALL_FILES})

target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ALL_FILES})