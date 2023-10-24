file(GLOB_RECURSE HEADERS "*.h")
file(GLOB_RECURSE SOURCES "*.cpp")
set(ALL_FILES ${HEADERS} ${SOURCES})

add_library(scene STATIC ${ALL_FILES})
target_link_libraries(scene PRIVATE imgui)
target_link_libraries(scene PUBLIC core)
target_link_libraries(scene PRIVATE tbb)
target_include_directories(scene PRIVATE ${TBB_Headers})
target_include_directories(scene PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


